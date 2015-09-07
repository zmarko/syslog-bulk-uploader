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
#include "SyslogBulkUploader.h"
#include "FileReader.h"
#include "UDPWriter.h"

namespace po = boost::program_options;
using namespace std;

size_t mps;
string dest;
uint16_t port;
vector<string> files;

string version() {
    stringstream ss;
    ss << VER_NAME << " version " << VER_MAJOR << ".";
#ifdef VER_MINOR
    ss << VER_MINOR;
#else
    ss << "0";
#endif
    ss << ".";
#ifdef VER_PATCH
    ss << VER_PATCH;
#else
    ss << "0";
#endif
#ifdef VER_PRERELEASE
    ss << "-" << VER_PRERELEASE;
#endif
#ifdef VER_BUILD
    ss << "+" << VER_BUILD;
#endif

    return ss.str();
}

int main(int argc, char** argv) {
    po::options_description desc("Supported options");
    desc.add_options()
            ("help,h", "display help message")
            ("version,v", "display version information")
            ("mps,m", po::value<size_t>(&mps)->default_value(1000), "try to maintain this rate of messages-per-second")
            ("dest,d", po::value<string>(&dest), "destination host name")
            ("port,p", po::value<uint16_t>(&port)->default_value(514), "destination port")
            ("files,f", po::value<vector < string >> (&files), "input file(s)")
            ;
    po::positional_options_description pos;
    pos.add("files", -1);
    po::variables_map vars;

    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vars);
    } catch (exception& ex) {
        cout << "Error parsing command line: " << ex.what() << endl;
        return -1;
    }
    po::notify(vars);

    if (vars.count("help")) {
        desc.print(std::cout);
        return 0;
    }

    if (vars.count("version")) {
        cout << version() << std::endl;
        return 0;
    }

    if (!vars.count("dest")) {
        cout << "ERROR: You must specify destination hostname" << endl;
        desc.print(cout);
        return -1;
    }

    if (!vars.count("files")) {
        cout << "ERROR: You must specify at least one input file" << endl;
        desc.print(cout);
        return -1;
    }

    UDPWriter w(dest, port);

    for (auto& file : files) {
        try {
            FileReader r(file);
            SyslogBulkUploader uploader(r, w, mps);
            cout << "Sending logs from " << file << " to udp://" << dest << ":" << port << " at a max rate of " <<
                    mps << " messages per second ... " << flush;
            uploader.run();
            cout << "done" << endl;
        } catch (string& ex) {
            cout << ex << endl;
        } catch (exception& ex) {
            cout << ex.what() << endl;
        }
    }
}


