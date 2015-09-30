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
#include <map>
#include "facility.h"

using namespace std;
using namespace boost;

namespace {
	const map<string, uint8_t> facility_strings{
		{ "kern", 0 },
		{ "user", 1 },
		{ "mail", 2 },
		{ "daemon", 3 },
		{ "auth", 4 },
		{ "syslog", 5 },
		{ "lpr", 6 },
		{ "news", 7 },
		{ "uucp", 8 },
		{ "clock", 9 },
		{ "authpriv", 10 },
		{ "ftp", 11 },
		{ "ntp", 12 },
		{ "logaudit", 13 },
		{ "logalert", 14 },
		{ "cron", 15 },
		{ "local0", 16 },
		{ "local1", 17 },
		{ "local2", 18 },
		{ "local3", 19 },
		{ "local4", 20 },
		{ "local5", 21 },
		{ "local6", 22 },
		{ "local7", 23 }
	};

	string read_from_stream(istream& src) {
		string ret;
		while (src) {
			auto c = src.get();
			if (c == '.') {
				break;
			} else {
				ret.push_back(c);
			}
		}
		return ret;
	}

	uint8_t read_from_string(const string& src) {
		const auto& value = facility_strings.find(to_lower_copy(src));
		if (value != facility_strings.end()) {
			return value->second;
		} else {
			throw "illegal facility value: " + src;
		}
	}
}

facility::facility(const char* src) : facility(string(src)) {};
facility::facility(const string& source) : value_(read_from_string(source)) {};
facility::facility(istream& source) : facility(read_from_stream(source)) {};

bool facility::operator!=(const facility& right) const {
	return !(*this == right);
}

bool facility::operator==(const facility& right) const {
	return value_ == right.value_;
}

std::ostream& operator<<(std::ostream& os, const facility& obj) {
	os << to_string(obj.value_);
	return os;
}


