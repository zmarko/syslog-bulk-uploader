/*
 The MIT License (MIT)

Copyright (c) 2015 Marko Živanović

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include "src/config.h"
#include "syslog_bulk_uploader.h"
#include "file_reader.h"
#include "udp_writer.h"

namespace po = boost::program_options;
using namespace std;
using namespace boost::posix_time;

po::options_description desc("Supported options");
size_t mps;
string dest;
uint16_t port;
vector<string> files;
ptime start;
ptime last_print;
time_duration print_interval = seconds(1);

string version() {
	stringstream ss;
	ss << SLBU_DESC << " version " << SLBU_VER;
	return ss.str();
}

void help() {
	desc.print(cout);
}

void after_send_cb(const syslog_message&) {
	ptime now = second_clock::local_time();
	if (now - last_print > print_interval) {
		cout << "." << flush;
		last_print = now;
	}
}

int main(int argc, char** argv) {
	desc.add_options()
		("help,h", "display help message")
		("version,v", "display version information")
		("mps,m", po::value<size_t>(&mps)->default_value(1000), "send messages at specified rate per second")
		("dest,d", po::value<string>(&dest), "destination host name")
		("port,p", po::value<uint16_t>(&port)->default_value(514), "destination port")
		("file,f", po::value<vector < string >>(&files), "input file(s)")
		;
	po::positional_options_description pos;
	pos.add("file", -1);
	po::variables_map vars;

	try {
		po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vars);
	} catch (exception& ex) {
		cout << "Error parsing command line: " << ex.what() << endl;
		return -1;
	}
	po::notify(vars);

	if (vars.count("help")) {
		help();
		return 0;
	}

	if (vars.count("version")) {
		cout << version() << std::endl;
		return 0;
	}

	if (!vars.count("dest")) {
		cout << "ERROR: You must specify destination hostname" << endl;
		help();
		return -1;
	}

	if (!vars.count("file")) {
		cout << "ERROR: You must specify at least one input file" << endl;
		help();
		return -1;
	}

	udp_writer w(dest, port);

	last_print = start = second_clock::local_time();
	for (const auto& file : files) {
		try {
			file_reader r(file);
			syslog_bulk_uploader uploader(r, w, mps);
			uploader.add_after_send_cb(bind(after_send_cb, placeholders::_1));
			cout << "Sending logs from " << file << " to udp://" << dest << ":" << port
				<< " at a max rate of " << mps << " messages per second " << flush;
			uploader.run();
			cout << " - DONE" << endl;
		} catch (string& ex) {
			cout << ex << endl;
		} catch (exception& ex) {
			cout << ex.what() << endl;
		}
	}
}


