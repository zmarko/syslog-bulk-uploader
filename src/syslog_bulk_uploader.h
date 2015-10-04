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

class Reader;
class Writer;
class Syslog_message;

class Syslog_bulk_uploader final : boost::noncopyable {
public:
	using Callback = boost::signals2::signal<void(const Syslog_message&)>;

	Syslog_bulk_uploader(Reader&, Writer&, const size_t = 1000);

	void run();
	void add_before_send_cb(const Callback::slot_type&);
	void add_after_send_cb(const Callback::slot_type&);

private:
	Reader& reader_;
	Writer& writer_;
	const size_t mps_;
	Callback before_send_cb_;
	Callback after_send_cb_;
};

#endif	/* SYSLOG_BULK_UPLOADER_H */

