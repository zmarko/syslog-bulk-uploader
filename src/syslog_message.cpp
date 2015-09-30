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

#include "syslog_message.h"

using namespace std;
using namespace boost;

namespace {

	void skip_whitespace(istream& src) {
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

	const posix_time::ptime read_timestamp(istream& src) {
		int ws = 0;
		string ts;
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
		return posix_time::time_from_string(ts);
	}

	const facility read_facility(istream& src) {
		skip_whitespace(src);
		return facility(src);
	}

	const severity read_severity(istream& src) {
		return severity(src);
	}

	const string read_source(istream& src) {
		string ret;
		skip_whitespace(src);
		while (src) {
			auto c = src.get();
			if (c == ' ' || c == '\t') {
				break;
			} else {
				ret.push_back(c);
			}
		}
		return ret;
	}

	const string read_message(istream& src) {
		string ret;
		skip_whitespace(src);
		getline(src, ret);
		return ret;
	}
}

syslog_message::syslog_message(istream& src)
	: timestamp_(read_timestamp(src)),
	facility_(read_facility(src)),
	severity_(read_severity(src)),
	source_(read_source(src)),
	message_(read_message(src)) {};

const posix_time::ptime syslog_message::timestamp() const {
	return timestamp_;
}

const facility syslog_message::fac() const {
	return facility_;
}

const severity syslog_message::sev() const {
	return severity_;
}

const std::string syslog_message::source() const {
	return source_;
}

const std::string syslog_message::message() const {
	return message_;
}

const uint8_t syslog_message::priority() const {
	return facility_ + severity_;
};

uint8_t operator+(const facility& f, const severity& s) {
	return f._value * 8 + s._value;
}

ostream& operator<<(std::ostream& os, const syslog_message& obj) {
	os << "syslog_message{timestamp_:" << obj.timestamp() << ", facility:" << obj.fac()
		<< ", severity:" << obj.sev() << ", source:" << obj.source() << ", message:" << obj.message() << "}";
	return os;
}
