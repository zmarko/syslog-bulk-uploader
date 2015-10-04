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

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

#include "Udp_syslog_server.h"

using boost::asio::ip::udp;
using namespace std;
using namespace boost::asio;
using namespace boost::posix_time;
using namespace boost;

Udp_syslog_server::Udp_syslog_server(io_service& ios, const int port, const int timeout)
	: socket_(ios, udp::endpoint(udp::v4(), port)), dt_(ios), timeout_(timeout) {
	deadline_handler();
	receive();
}

const vector<string>& Udp_syslog_server::messages() const {
	return messages_;
}

void Udp_syslog_server::receive() {
	dt_.expires_from_now(milliseconds(timeout_));
	socket_.async_receive_from(
		buffer(buffer_), peer_,
		bind(&Udp_syslog_server::receive_handler, this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred));
}

void Udp_syslog_server::receive_handler(const system::error_code& error, size_t len) {
	if (!error || error == asio::error::message_size) {
		if (len > 0) {
			string s(buffer_.data(), len);
			messages_.push_back(s);
		}
		receive();
	}
}

void Udp_syslog_server::deadline_handler() {
	auto delta = deadline_timer::traits_type::now() - dt_.expires_at();
	if (delta != not_a_date_time && delta >= milliseconds(0)) {
		socket_.cancel();
		dt_.expires_at(posix_time::pos_infin);
	}

	dt_.async_wait(bind(&Udp_syslog_server::deadline_handler, this));
}
