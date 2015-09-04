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

#ifndef SYSLOGMESSAGE_H
#define	SYSLOGMESSAGE_H

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Facility.h"
#include "Severity.h"

class SyslogMessage {
public:

    SyslogMessage(std::istream& src) : _timestamp(readTimestamp(src)), _facility(readFacility(src)),
    _severity(readSeverity(src)), _source(readSource(src)), _message(readMessage(src)) {
    };

    SyslogMessage(const SyslogMessage& orig) : _timestamp(orig._timestamp), _facility(orig._facility),
    _severity(orig._severity), _source(orig._source), _message(orig._message) {
    };

    virtual ~SyslogMessage() {
    };

    const Facility facility() const {
        return _facility;
    }

    const std::string message() const {
        return _message;
    }

    const Severity severity() const {
        return _severity;
    }

    const std::string source() const {
        return _source;
    }

    const boost::posix_time::ptime timestamp() const {
        return _timestamp;
    }

    const uint8_t priority() const {
        return (_facility.as_int() * 8) +_severity.as_int();
    };

    friend std::ostream& operator<<(std::ostream& os, const SyslogMessage& obj) {
        os << "SyslogMessage{timestamp:" << obj._timestamp << ", facility:" << obj._facility <<
                ", severity:" << obj._severity << ",source:" << obj._source << ",message:" << obj._message << "}";
        return os;
    }

private:

    const boost::posix_time::ptime _timestamp;
    const Facility _facility;
    const Severity _severity;
    const std::string _source;
    const std::string _message;

    const boost::posix_time::ptime readTimestamp(std::istream&);
    const Facility readFacility(std::istream&);
    const Severity readSeverity(std::istream&);
    const std::string readSource(std::istream&);
    const std::string readMessage(std::istream&);
};

#endif	/* SYSLOGMESSAGE_H */

