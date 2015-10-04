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

#ifndef UDP_SYSLOG_SERVER_H
#define	UDP_SYSLOG_SERVER_H

#include <boost/array.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/ip/udp.hpp>
#include <string>
#include <vector>

class Udp_syslog_server {
public:
	Udp_syslog_server(boost::asio::io_service&, const int, const int);
	const std::vector<std::string>& messages() const;

private:
	void receive();
	void receive_handler(const boost::system::error_code&, std::size_t);
	void deadline_handler();

	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint peer_;
	boost::array<char, 1024> buffer_;
	std::vector<std::string> messages_;
	boost::asio::deadline_timer dt_;
	const int timeout_;
};

#endif	/* UDP_SYSLOG_SERVER_H */

