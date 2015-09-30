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

#ifndef SEVERITY_H
#define	SEVERITY_H

class facility;

class severity final {
public:
	explicit severity(const std::string&);
	explicit severity(const char*);
	explicit severity(std::istream&);

	severity() = delete;
	~severity() = default;
	severity(const severity&) = default;
	severity(severity&&) = default;
	severity& operator=(const severity&) = default;
	severity& operator=(severity&&) = default;

	bool operator!=(const severity&) const;
	bool operator==(const severity&) const;

	friend uint8_t operator+(const facility&, const severity&);
	friend std::ostream& operator<<(std::ostream&, const severity&);

private:
	const uint8_t _value;
};

#endif	/* SEVERITY_H */
