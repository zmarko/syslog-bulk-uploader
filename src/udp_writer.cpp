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

#include "Syslog_message.h"
#include "Udp_writer.h"
#include "RFC3164_fmt.h"

using boost::asio::ip::udp;
using namespace boost::asio;

Udp_writer::Udp_writer(const std::string& destination, const uint16_t port) {
    udp::resolver resolver(ios_);
    udp::resolver::query query(destination, std::to_string(port));
    udp::resolver::iterator it = resolver.resolve(query);
    if (it != udp::resolver::iterator()) {
        auto endpoint = *it;
        socket_.connect(endpoint);
    } else {
        throw "destination not found: " + destination;
    }
}

void Udp_writer::write(const Syslog_message& message) {
    if (socket_.is_open()) {
        auto fmt_msg = RFC3164_fmt{message};
        auto fmt_str = fmt_msg();
        auto buff = buffer(fmt_str);
        socket_.send(buff);
    }
}
