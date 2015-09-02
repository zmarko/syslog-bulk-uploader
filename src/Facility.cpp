/*
 The MIT License (MIT)

Copyright (c) 2015 Marko Živanović

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the std::string("Software")), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED std::string("AS IS"), WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <boost/algorithm/string.hpp>
#include "Facility.h"

const std::string Facility::readFromStream(std::istream& src) {
    std::string ret;
    while (src) {
        std::istream::char_type c = src.get();
        if (c == '.') {
            break;
        } else {
            if (c != ' ' && c != '\t') {
                ret.push_back(c);
            }
        }
    }
    return ret;
}

const Facility::Value Facility::readFromString(const std::string& src) {
    Facility::Value ret;
    if (boost::iequals(src, std::string("Kern"))) {
        ret = Facility::Value::Kern;
    } else if (boost::iequals(src, std::string("User"))) {
        ret = Facility::Value::User;
    } else if (boost::iequals(src, std::string("Mail"))) {
        ret = Facility::Value::Mail;
    } else if (boost::iequals(src, std::string("Daemon"))) {
        ret = Facility::Value::Daemon;
    } else if (boost::iequals(src, std::string("Auth"))) {
        ret = Facility::Value::Auth;
    } else if (boost::iequals(src, std::string("Syslog"))) {
        ret = Facility::Value::Syslog;
    } else if (boost::iequals(src, std::string("Lpr"))) {
        ret = Facility::Value::Lpr;
    } else if (boost::iequals(src, std::string("News"))) {
        ret = Facility::Value::News;
    } else if (boost::iequals(src, std::string("Uucp"))) {
        ret = Facility::Value::Uucp;
    } else if (boost::iequals(src, std::string("Clock"))) {
        ret = Facility::Value::Clock;
    } else if (boost::iequals(src, std::string("Authpriv"))) {
        ret = Facility::Value::Authpriv;
    } else if (boost::iequals(src, std::string("Ftp"))) {
        ret = Facility::Value::Ftp;
    } else if (boost::iequals(src, std::string("Ntp"))) {
        ret = Facility::Value::Ntp;
    } else if (boost::iequals(src, std::string("LogAudit"))) {
        ret = Facility::Value::LogAudit;
    } else if (boost::iequals(src, std::string("LogAlert"))) {
        ret = Facility::Value::LogAlert;
    } else if (boost::iequals(src, std::string("Cron"))) {
        ret = Facility::Value::Cron;
    } else if (boost::iequals(src, std::string("Local0"))) {
        ret = Facility::Value::Local0;
    } else if (boost::iequals(src, std::string("Local1"))) {
        ret = Facility::Value::Local1;
    } else if (boost::iequals(src, std::string("Local2"))) {
        ret = Facility::Value::Local2;
    } else if (boost::iequals(src, std::string("Local3"))) {
        ret = Facility::Value::Local3;
    } else if (boost::iequals(src, std::string("Local4"))) {
        ret = Facility::Value::Local4;
    } else if (boost::iequals(src, std::string("Local5"))) {
        ret = Facility::Value::Local5;
    } else if (boost::iequals(src, std::string("Local6"))) {
        ret = Facility::Value::Local6;
    } else if (boost::iequals(src, std::string("Local7"))) {
        ret = Facility::Value::Local7;
    } else {
        throw "Illegal facility value: " + src;
    };
    return ret;
}


