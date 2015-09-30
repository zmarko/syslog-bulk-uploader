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

#include "../src/syslog_message.h"
#define BOOST_TEST_MODULE syslog_message_tests
#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

BOOST_AUTO_TEST_CASE(parsing) {
    std::stringstream source("2015-09-02 13:33:11     Local4.Critical 192.168.0.1     Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query");
    boost::posix_time::ptime timestamp_(boost::posix_time::time_from_string("2015-09-02 13:33:11"));
    syslog_message m(source);
    BOOST_CHECK_EQUAL(m.timestamp(), timestamp_);
    BOOST_CHECK_EQUAL(m.fac(), facility("Local4"));
    BOOST_CHECK_EQUAL(m.sev(), severity("Critical"));
    BOOST_CHECK_EQUAL(m.source(), "192.168.0.1");
    BOOST_CHECK_EQUAL(m.message(), "Kiwi_Syslog_Server %ASA-2-106007: Deny inbound UDP from 1.2.3.4/22084 to 4.3.2.1/53 due to DNS Query");
}

BOOST_AUTO_TEST_CASE(invalid_params) {
    BOOST_CHECK_THROW(facility("invalid"), std::string);
    BOOST_CHECK_THROW(severity("invalid"), std::string);
    BOOST_CHECK_NO_THROW(facility("Local0"));
    BOOST_CHECK_NO_THROW(severity("Critical"));
}