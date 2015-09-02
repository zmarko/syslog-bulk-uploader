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

    virtual ~Facility() {
    };
private:

    enum Value {
        Kern = 0, User = 1, Mail = 2, Daemon = 3, Auth = 4, Syslog = 5, Lpr = 6, News = 7, Uucp = 8, Clock = 9,
        Authpriv = 10, Ftp = 11, Ntp = 12, LogAudit = 13, LogAlert = 14, Cron = 15, Local0 = 16, Local1 = 17,
        Local2 = 18, Local3 = 19, Local4 = 20, Local5 = 21, Local6 = 22, Local7 = 23
    };
    const Value _value;
    const std::string readFromStream(std::istream&);
    const Value readFromString(const std::string&);
};

#endif	/* FACILITY_H */