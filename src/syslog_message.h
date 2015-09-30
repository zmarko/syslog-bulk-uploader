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

#include "facility.h"
#include "severity.h"

class syslog_message final {
public:

	explicit syslog_message(std::istream&);

	syslog_message() = delete;
	syslog_message(const syslog_message&) = default;
	syslog_message(syslog_message&&) = default;
	syslog_message& operator=(const syslog_message&) = default;
	syslog_message& operator=(syslog_message&&) = default;
	~syslog_message() = default;

	const boost::posix_time::ptime timestamp() const;
	const facility fac() const;
	const severity sev() const;
	const std::string source() const;
	const std::string message() const;
	const uint8_t priority() const;

private:
	const boost::posix_time::ptime timestamp_;
	const facility facility_;
	const severity severity_;
	const std::string source_;
	const std::string message_;
};

std::ostream& operator<<(std::ostream& os, const syslog_message& obj);


#endif	/* SYSLOG_MESSAGE_H */

