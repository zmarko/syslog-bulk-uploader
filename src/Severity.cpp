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

#include <boost/algorithm/string.hpp>
#include "Severity.h"

const std::string Severity::readFromStream(std::istream& src) {
    std::string ret;
    while (src) {
        std::istream::char_type c = src.get();
        if (c == ' ' || c == '\t') {
            break;
        } else {
            ret.push_back(c);
        }
    }
    return ret;
}

const Severity::Value Severity::readFromString(const std::string& src) {
    Severity::Value ret;
    if (boost::iequals(src, std::string("Emergency"))) {
        ret = Severity::Value::Emergency;
    } else if (boost::iequals(src, std::string("Alert"))) {
        ret = Severity::Value::Alert;
    } else if (boost::iequals(src, std::string("Critical"))) {
        ret = Severity::Value::Critical;
    } else if (boost::iequals(src, std::string("Error"))) {
        ret = Severity::Value::Error;
    } else if (boost::iequals(src, std::string("Warning"))) {
        ret = Severity::Value::Warning;
    } else if (boost::iequals(src, std::string("Notice"))) {
        ret = Severity::Value::Notice;
    } else if (boost::iequals(src, std::string("Informational"))) {
        ret = Severity::Value::Informational;
    } else if (boost::iequals(src, std::string("Debug"))) {
        ret = Severity::Value::Debug;
    } else {
        throw "Illegal severity value: " + src;
    };
    return ret;
}


