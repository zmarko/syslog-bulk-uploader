/*
The MIT License (MIT)

Copyright (c) 2015 Marko Živanovi?

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

#include "RFC3164_fmt.h"

using namespace std;

namespace {
	const int MAX_LEN = 1024;
}

const string RFC3164_fmt::operator()() {
	stringstream stream;
	stream.imbue(locale(locale::classic(), new boost::posix_time::time_facet("%b %e %H:%M:%S")));
	stream << "<" << to_string(message_.priority()) << ">"
		<< message_.timestamp() << " "
		<< message_.source() << " "
		<< message_.message();
	string ret = stream.str();
	if (ret.size() > MAX_LEN) {
		ret = ret.substr(0, MAX_LEN);
	}
	return ret;
}
