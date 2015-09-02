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

#include "../src/SyslogBulkUploader.h"
#include "../src/Reader.h"
#include "../src/Writer.h"
#define BOOST_TEST_MODULE SyslogBulkUploaderTests
#include <boost/test/unit_test.hpp>
#include <memory>

class MockReader : public Reader {
public:

    virtual std::shared_ptr<SyslogMessage> nextMessage() {
        if (_pos >= _messages.size()) {
            return std::shared_ptr<SyslogMessage>();
        } else {
            std::stringstream ss(_messages[_pos++]);
            return std::shared_ptr<SyslogMessage>(new SyslogMessage(dynamic_cast<std::istream&> (ss)));
        }
    }
private:
    std::vector<std::string> _messages = {
        "2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query",
        "2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query",
        "2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query"
    };
    size_t _pos;
};

class MockWriter : public Writer {
public:

    virtual void sendMessage(std::shared_ptr<SyslogMessage> msg) {
        _messages.push_back(msg);
    };
    std::vector<std::shared_ptr<SyslogMessage>> _messages;
};

BOOST_AUTO_TEST_CASE(test_run) {
    MockReader r;
    MockWriter w;
    SyslogBulkUploader ul(r, w);
    ul.run();
    BOOST_CHECK_EQUAL(w._messages.size(), 3);
    for (size_t i = 0; i < w._messages.size(); i++) {
        std::cout << *(w._messages[i].get()) << std::endl;
    }
}
