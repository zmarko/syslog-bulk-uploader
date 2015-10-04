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

#ifndef SYSLOG_MESSAGE_H
#define	SYSLOG_MESSAGE_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <iosfwd>
#include <string>

#include "Facility.h"
#include "Severity.h"

class Syslog_message final {
public:
	explicit Syslog_message(std::istream&);

	Syslog_message() = delete;
	Syslog_message(const Syslog_message&) = default;
	Syslog_message(Syslog_message&&) = default;
	Syslog_message& operator=(const Syslog_message&) = default;
	Syslog_message& operator=(Syslog_message&&) = default;
	~Syslog_message() = default;

	const boost::posix_time::ptime timestamp() const;
	const Facility fac() const;
	const Severity sev() const;
	const std::string source() const;
	const std::string message() const;
	uint8_t priority() const;

private:
	const boost::posix_time::ptime timestamp_;
	const Facility facility_;
	const Severity severity_;
	const std::string source_;
	const std::string message_;
};

std::ostream& operator<<(std::ostream& os, const Syslog_message& obj);


#endif	/* SYSLOG_MESSAGE_H */
