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

#include "SyslogMessage.h"

void skipWhitespace(std::istream& src) {
    while (src) {
        auto c = src.peek();
        if (c == ' ' || c == '\t') {
            src.get();
            continue;
        } else {
            break;
        }
    }
}

const boost::posix_time::ptime SyslogMessage::readTimestamp(std::istream& src) {
    int ws = 0;
    std::string ts;
    while (src) {
        auto c = src.get();
        if (c == ' ' || c == '\t') {
            ws++;
        }
        if (ws == 2) {
            break;
        } else {
            ts.push_back(c);
        }
    }
    return boost::posix_time::time_from_string(ts);
};

const Facility SyslogMessage::readFacility(std::istream& src) {
    skipWhitespace(src);
    return Facility(src);
};

const Severity SyslogMessage::readSeverity(std::istream& src) {
    return Severity(src);
};

const std::string SyslogMessage::readSource(std::istream& src) {
    std::string ret;
    skipWhitespace(src);
    while (src) {
        auto c = src.get();
        if (c == ' ' || c == '\t') {
            break;
        } else {
            ret.push_back(c);
        }
    }
    return ret;
};

const std::string SyslogMessage::readMessage(std::istream & src) {
    std::string ret;
    skipWhitespace(src);
    while (src) {
        auto c = src.get();
        if (!src.eof()) {
            ret.push_back(c);
        }
    }
    return ret;
};

