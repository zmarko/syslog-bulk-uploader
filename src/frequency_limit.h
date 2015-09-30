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

#ifndef FREQUENCY_LIMIT_H
#define	FREQUENCY_LIMIT_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class frequency_limit final {
public:

	frequency_limit(const size_t& limit)
		: target_latency(boost::posix_time::microseconds(1000000 / limit)),
		delay(boost::posix_time::milliseconds(0)) {};

	void operator()() {
		auto now(boost::posix_time::microsec_clock::local_time());
		if (prev_ts == boost::posix_time::not_a_date_time) {
			prev_ts = now;
		} else {
			auto latency = now - prev_ts;
			auto diff = target_latency - latency;
			delay = delay + diff;
			if (diff > boost::posix_time::microseconds(0)) {
				boost::this_thread::sleep(delay);
			}
			prev_ts = now;
		}
	};

private:
	const boost::posix_time::time_duration target_latency;
	boost::posix_time::time_duration delay;
	boost::posix_time::ptime prev_ts;
};

#endif	/* FREQUENCY_LIMIT_H */

