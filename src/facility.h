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

#ifndef FACILITY_H
#define	FACILITY_H

#include <iosfwd>
#include <string>

class Severity;

class Facility final {
public:
	explicit Facility(const char*);
	explicit Facility(const std::string&);
	explicit Facility(std::istream&);

	Facility() = delete;
	~Facility() = default;
	Facility(const Facility&) = default;
	Facility(Facility&&) = default;
	Facility& operator=(const Facility&) = default;
	Facility& operator=(Facility&&) = default;

	bool operator!=(const Facility&) const;
	bool operator==(const Facility&) const;

private:
	const uint8_t value_;

	friend std::ostream& operator<<(std::ostream&, const Facility&);
	friend uint8_t operator+(const Facility& f, const Severity& s);
};

#endif	/* FACILITY_H */
