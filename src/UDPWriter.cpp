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

#include <string>
#include "UDPWriter.h"
#include "RFC3164FormattedSyslogMessage.h"

using boost::asio::ip::udp;
using namespace boost::asio;

UDPWriter::UDPWriter(const std::string& destination, const int port) {
    udp::resolver resolver(_ios);
    udp::resolver::query query(destination, std::to_string(port));
    udp::resolver::iterator it = resolver.resolve(query);
    if (it != udp::resolver::iterator()) {
        auto endpoint = *it;
        _socket.connect(endpoint);
    } else {
        throw "Destination not found: " + destination;
    }
};

void UDPWriter::sendMessage(std::shared_ptr<const SyslogMessage> message) {
    if (_socket.is_open()) {
        auto fmtMsg = RFC3164FormattedSyslogMessage{*message};
        auto fmtStr = fmtMsg();
        auto buff = buffer(fmtStr);
        _socket.send(buff);
    }
}
