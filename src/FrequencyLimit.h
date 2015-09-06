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

#ifndef FREQUENCYLIMIT_H
#define	FREQUENCYLIMIT_H

#include <boost/noncopyable.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class FrequencyLimit {
public:

    FrequencyLimit(const size_t& limit) : _target(boost::posix_time::microseconds(1000000 / limit)),
    _delay(boost::posix_time::milliseconds(0)) {
    };

    void tick() {
        auto now(boost::posix_time::microsec_clock::local_time());
        if (_prev == boost::posix_time::not_a_date_time) {
            _prev = now;
        } else {
            auto latency = now - _prev;
            auto diff = _target - latency;
            _delay = _delay + diff;
            if (diff > boost::posix_time::microseconds(0)) {
                boost::this_thread::sleep(_delay);
            }
            _prev = now;
        }
    };

private:
    const boost::posix_time::time_duration _target;
    boost::posix_time::time_duration _delay;
    boost::posix_time::ptime _prev;
};

#endif	/* FREQUENCYLIMIT_H */

