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

#include "syslog_bulk_uploader.h"
#include "reader.h"
#include "writer.h"
#include "frequency_limit.h"

syslog_bulk_uploader::syslog_bulk_uploader(reader& r, writer& w, const size_t mps)
	: reader_(r), writer_(w), mps_(mps) {};

void syslog_bulk_uploader::run() {
	frequency_limit freq_limit(mps_);

	while (auto msg = reader_.next_message()) {
		freq_limit();
		before_send_cb_(*msg);
		writer_.send(*msg);
		after_send_cb_(*msg);
	}
}

void syslog_bulk_uploader::add_before_send_cb(const callback::slot_type& cb) {
	before_send_cb_.connect(cb);
}

void syslog_bulk_uploader::add_after_send_cb(const callback::slot_type& cb) {
	after_send_cb_.connect(cb);
}
