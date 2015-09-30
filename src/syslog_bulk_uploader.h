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

#ifndef SYSLOG_BULK_UPLOADER_H
#define	SYSLOG_BULK_UPLOADER_H

#include <boost/noncopyable.hpp>
#include <boost/signals2.hpp>
#include <memory>

class reader;
class writer;
class syslog_message;

class syslog_bulk_uploader final : boost::noncopyable {
public:
	syslog_bulk_uploader(reader&, writer&, const size_t = 1000);
	void run();

	using callback = boost::signals2::signal<void(const syslog_message&)>;
	void add_before_send_cb(const callback::slot_type&);
	void add_after_send_cb(const callback::slot_type&);

private:
	reader& reader_;
	writer& writer_;
	const size_t mps_;
	callback before_send_cb_;
	callback after_send_cb_;
};

#endif	/* SYSLOG_BULK_UPLOADER_H */

