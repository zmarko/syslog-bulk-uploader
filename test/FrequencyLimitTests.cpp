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

#define BOOST_TEST_MODULE FrequencyLimitTests
#include <boost/test/unit_test.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../src/FrequencyLimit.h"

using namespace boost::posix_time;

size_t countInLoop(size_t freq, time_duration duration) {
    FrequencyLimit f(freq);
    ptime start(second_clock::local_time());
    int c = 0;
    while (second_clock::local_time() - start < duration) {
        f.tick();
        c++;
    }
    return c;
}

BOOST_AUTO_TEST_CASE(test_slow) {
    size_t c = countInLoop(5, seconds(5));
    BOOST_WARN_CLOSE((float) c, 25, 10);
}

BOOST_AUTO_TEST_CASE(test_fast) {
    size_t c = countInLoop(100, seconds(5));
    BOOST_WARN_CLOSE((float) c, 500, 10);
}
