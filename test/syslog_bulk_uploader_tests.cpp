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

#define BOOST_TEST_MODULE syslog_bulk_uploader_tests
#include <boost/test/unit_test.hpp>
#include <memory>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "../src/Syslog_bulk_uploader.h"
#include "../src/Syslog_message.h"
#include "../src/Reader.h"
#include "../src/Writer.h"
#include "../src/File_reader.h"
#include "../src/Udp_writer.h"
#include "Udp_syslog_server.h"
#include "../src/RFC3164_fmt.h"

using namespace std;

class Mock_reader : public Reader {
public:
	virtual unique_ptr<const Syslog_message> next_message() override {
		if (pos_ >= messages_.size()) {
			return unique_ptr<Syslog_message>();
		} else {
			stringstream ss(messages_[pos_++]);
			return unique_ptr<Syslog_message>(new Syslog_message(dynamic_cast<istream&> (ss)));
		}
	}
private:
	vector<string> messages_{
		"2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query",
		"2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query",
		"2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query"
	};
	size_t pos_{};
};

class Mock_writer : public Writer {
public:
	virtual void write(const Syslog_message& msg) override {
		messages.push_back(&msg);
		cout << msg << endl;
	};
	vector<const Syslog_message*> messages;
};

BOOST_AUTO_TEST_CASE(test_run) {
	Mock_reader r;
	Mock_writer w;
	Syslog_bulk_uploader ul(r, w);
	ul.run();
	BOOST_CHECK_EQUAL(w.messages.size(), 3);
}

BOOST_AUTO_TEST_CASE(test_file_reader) {
	cout << "Running in " << boost::filesystem::initial_path() << endl;
	File_reader r("../test/sample1");
	Mock_writer w;
	Syslog_bulk_uploader ul(r, w);
	ul.run();
	BOOST_CHECK_EQUAL(w.messages.size(), 3);
}

BOOST_AUTO_TEST_CASE(test_udp_writer) {
	using namespace boost::posix_time;

	ptime start(second_clock::local_time());
	boost::asio::io_service ios;
	File_reader r("../test/sample1");
	Udp_writer w("127.0.0.1", 51514);
	Syslog_bulk_uploader ul(r, w);
	Udp_syslog_server server(ios, 51514, 2000);
	ul.run();

	while (second_clock::local_time() - start < seconds(2)) {
		ios.run_one();
	}

	BOOST_CHECK_EQUAL(server.messages().size(), 3);

	auto it = server.messages().begin();
	File_reader r2("../test/sample1");
	while (auto msg = r2.next_message()) {
		RFC3164_fmt fmt(*msg);
		BOOST_CHECK_EQUAL(*it, fmt());
		it++;
	}

}