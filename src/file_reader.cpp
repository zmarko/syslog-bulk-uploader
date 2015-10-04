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

#include "File_reader.h"
#include "Syslog_message.h"

using namespace std;

File_reader::File_reader(const string& filename) : stream_(filename) {
	if (!stream_.is_open()) {
		throw "error opening file: " + filename;
	}
}

unique_ptr<const Syslog_message> File_reader::next_message() {
	unique_ptr<const Syslog_message> ret;
	if (stream_.is_open() && !stream_.eof() && !stream_.fail()) {
		ret = make_unique<Syslog_message>(stream_);
		for (auto c = stream_.peek(); c == '\n' || c == '\r'; stream_.get(), c = stream_.peek());
	}
	return ret;
}
