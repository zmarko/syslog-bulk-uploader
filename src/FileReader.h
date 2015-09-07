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

#ifndef FILEREADER_H
#define	FILEREADER_H

#include <fstream>
#include "Reader.h"
#include "SyslogMessage.h"

class FileReader : public Reader {
public:

    FileReader(const std::string& filename) : _stream(filename) {
        if (!_stream.is_open()) {
            throw "File not found: " + filename;
        }
    }

    virtual std::shared_ptr<const SyslogMessage> nextMessage() {
        std::shared_ptr<const SyslogMessage> ret;
        if (_stream.is_open() && !_stream.eof() && !_stream.fail()) {
            ret.reset(new SyslogMessage(_stream));
            for (auto c = _stream.peek(); c == '\n' || c == '\r'; _stream.get(), c = _stream.peek());
        }
        return ret;
    }

private:
    std::ifstream _stream;
};

#endif	/* FILEREADER_H */

