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

#ifndef UDPSYSLOGSERVER_H
#define	UDPSYSLOGSERVER_H

#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::udp;
using namespace boost::asio;
using namespace boost::posix_time;

class UdpSyslogServer {
public:

    UdpSyslogServer(boost::asio::io_service& ios, const int port, const int timeout)
    : _socket(ios, udp::endpoint(udp::v4(), port)), _dt(ios), _timeout(timeout) {
        deadlineHandler();
        receive();
    }

    const std::vector<std::string>& messages() const {
        return _messages;
    }

private:

    void receive() {
        _dt.expires_from_now(milliseconds(_timeout));
        _socket.async_receive_from(
                boost::asio::buffer(_buffer), _peer,
                boost::bind(&UdpSyslogServer::receiveHandler, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void receiveHandler(const boost::system::error_code& error, std::size_t len) {
        if (!error || error == boost::asio::error::message_size) {
            if (len > 0) {
                std::string s(_buffer.data(), len);
                _messages.push_back(s);
            }
            receive();
        }
    }

    void deadlineHandler() {
        auto delta = deadline_timer::traits_type::now() - _dt.expires_at();
        if (delta != not_a_date_time && delta >= milliseconds(0)) {
            _socket.cancel();
            _dt.expires_at(boost::posix_time::pos_infin);
        }

        _dt.async_wait(boost::bind(&UdpSyslogServer::deadlineHandler, this));
    }


    udp::socket _socket;
    udp::endpoint _peer;
    boost::array<char, 1024> _buffer;
    std::vector<std::string> _messages;
    deadline_timer _dt;
    const int _timeout;
};

#endif	/* UDPSYSLOGSERVER_H */

