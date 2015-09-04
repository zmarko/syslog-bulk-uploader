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

#ifndef FACILITY_H
#define	FACILITY_H

#include <istream>

class Facility {
public:

    Facility(const char* src) : Facility(std::string(src)) {
    };

    Facility(const std::string& source) : _value(readFromString(source)) {
    };

    Facility(std::istream& source) : Facility(readFromStream(source)) {
    };

    Facility(const Facility & orig) : _value(orig._value) {
    };

    virtual ~Facility() {
    };

    bool operator!=(const Facility & right) const {
        bool result = !(*this == right); // Reuse equals operator
        return result;
    }

    bool operator==(const Facility & right) const {
        return _value == right._value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Facility& obj) {
        os << obj._value;
        return os;
    }

    uint8_t as_int() const {
        return _value;
    }

private:

    const std::map<std::string, uint8_t> _values{
        {"kern", 0},
        {"user", 1},
        {"mail", 2},
        {"daemon", 3},
        {"auth", 4},
        {"syslog", 5},
        {"lpr", 6},
        {"news", 7},
        {"uucp", 8},
        {"clock", 9},
        {"authpriv", 10},
        {"ftp", 11},
        {"ntp", 12},
        {"logaudit", 13},
        {"logalert", 14},
        {"cron", 15},
        {"local0", 16},
        {"local1", 17},
        {"local2", 18},
        {"local3", 19},
        {"local4", 20},
        {"local5", 21},
        {"local6", 22},
        {"local7", 23}
    };
    const uint8_t _value;
    const std::string readFromStream(std::istream&);
    const uint8_t readFromString(const std::string&);
};

#endif	/* FACILITY_H */