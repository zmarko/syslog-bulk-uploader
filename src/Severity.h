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

class Facility;

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

    virtual ~Severity() {
    };

    bool operator!=(const Severity& right) const {
        bool result = !(*this == right); // Reuse equals operator
        return result;
    }

    bool operator==(const Severity& right) const {
        return _value == right._value;
    }

    friend const uint8_t operator+(const Facility& f, const Severity& s);

    friend std::ostream& operator<<(std::ostream& os, const Severity& obj) {
        os << std::to_string(obj._value);
        return os;
    }

private:

    const std::map<std::string, uint8_t> VALUES{
        {"emergency", 0},
        {"alert", 1},
        {"critical", 2},
        {"error", 3},
        {"warning", 4},
        {"notice", 5},
        {"informational", 6},
        {"debug", 7}
    };

    const uint8_t _value;
    const std::string readFromStream(std::istream& source);
    const uint8_t readFromString(const std::string& src);
};

#endif	/* SEVERITY_H */