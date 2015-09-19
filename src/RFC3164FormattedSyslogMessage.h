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

#ifndef RFC3164FORMATTEDSYSLOGMESSAGE_H
#define	RFC3164FORMATTEDSYSLOGMESSAGE_H

#include "SyslogMessage.h"

class RFC3164FormattedSyslogMessage final {
public:

    RFC3164FormattedSyslogMessage(const SyslogMessage& msg) : _message(msg) {
    };

    const std::string operator()() {
        std::stringstream stream;
        stream.imbue(std::locale(std::locale::classic(), new boost::posix_time::time_facet("%b %e %H:%M:%S")));
        stream.str("");
        stream << "<" << std::to_string(_message.priority()) << ">";
        stream << _message.timestamp() << " ";
        stream << _message.source() << " ";
        stream << _message.message();
        std::string ret = stream.str();
        if (ret.size() > MAX_LEN) {
            ret = ret.substr(0, MAX_LEN);
        }
        return ret;
    };

private:
    static const size_t MAX_LEN = 1024;
    const SyslogMessage& _message;
};

#endif	/* RFC3164FORMATTEDSYSLOGMESSAGE_H */

