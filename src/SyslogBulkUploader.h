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

#ifndef SYSLOGBULKUPLOADER_H
#define	SYSLOGBULKUPLOADER_H

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>

class Reader;
class Writer;
class SyslogMessage;

class SyslogBulkUploader : boost::noncopyable {
public:

    typedef std::function<void(std::shared_ptr<const SyslogMessage>)> Callback;

    SyslogBulkUploader(Reader& reader, Writer& writer, const size_t& mps = DEFAULT_MPS) : _reader(reader),
    _writer(writer), _mps(mps) {
    };
    void run();

    void setPreSendCallback(Callback cb) {
        _preSendCallback = cb;
    }

    void setPostSendCallback(Callback cb) {
        _postSendCallback = cb;
    }

private:
    const static size_t DEFAULT_MPS = 1000;
    Reader& _reader;
    Writer& _writer;
    const size_t _mps;
    Callback _preSendCallback;
    Callback _postSendCallback;
};

#endif	/* SYSLOGBULKUPLOADER_H */

