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

#ifndef SEVERITY_H
#define	SEVERITY_H

#include <istream>

class Severity {
public:

    Severity(const std::string& src) : _value(readFromString(src)) {
    };

    Severity(const char* src) : Severity(std::string(src)) {
    };

    Severity(std::istream& source) : Severity(readFromStream(source)) {
    };

    Severity(const Severity& orig) : _value(orig._value) {
    };

    bool operator!=(const Severity& right) const {
        bool result = !(*this == right); // Reuse equals operator
        return result;
    }

    bool operator==(const Severity& right) const {
        return _value == right._value;
    }

    virtual ~Severity() {
    };

    friend std::ostream& operator<<(std::ostream& os, const Severity& obj) {
        os << obj._value;
        return os;
    }

private:

    enum Value {
        Emergency = 0, Alert = 1, Critical = 2, Error = 3, Warning = 4, Notice = 5, Informational = 6, Debug = 7
    };

    const Value _value;
    const std::string readFromStream(std::istream& source);
    const Value readFromString(const std::string& src);
};

#endif	/* SEVERITY_H */