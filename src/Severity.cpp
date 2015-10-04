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
#include "Severity.h"

using namespace std;

namespace {
	const map<string, uint8_t> severity_strings{
		{ "emergency", 0 },
		{ "alert", 1 },
		{ "critical", 2 },
		{ "error", 3 },
		{ "warning", 4 },
		{ "notice", 5 },
		{ "informational", 6 },
		{ "debug", 7 }
	};

	string read_from_stream(istream& src) {
		string ret;
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

	uint8_t read_from_string(const string& src) {
		const auto& value = severity_strings.find(boost::algorithm::to_lower_copy(src));
		if (value != severity_strings.end()) {
			return value->second;
		} else {
			throw "illegal severity: " + src;
		}
	}
}

Severity::Severity(const string& src) : value_(read_from_string(src)) {};
Severity::Severity(const char* src) : Severity(string(src)) {};
Severity::Severity(istream& source) : Severity(read_from_stream(source)) {};

bool Severity::operator!=(const Severity& right) const {
	return !(*this == right);
}

bool Severity::operator==(const Severity& right) const {
	return value_ == right.value_;
}

std::ostream& operator<<(std::ostream& os, const Severity& obj) {
	os << to_string(obj.value_);
	return os;
}
