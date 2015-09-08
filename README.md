# syslog-bulk-uploader
Syslog-bulk-uploader is non-interactive utility designed to read syslog records from one or more files and send them
to remote syslog server. The format of syslog records in input files is:

    <timestamp> <facility.severity> <source> <message>

Field separator is one or more space (ASCII 32) or tab (ASCII 9) characters.
All whitespace characters in the _message_ field will be interpreted as part of the message, not as separators.

Fields of the syslog record are:
<dl>
    <dt><strong>timestamp</strong></dt>
    <dd>in format YYYY-MM-DD HH:MM:SS</dd>
    <dt><strong>facility</strong></dt>
    <dd>one of syslog facility strings: *kern, user, mail, daemon, auth, syslog, lpr, news, uucp, clock, authpriv, ftp, ntp, logaudit, logalert, cron, local0, local1, local2, local3, local4, local5, local6, local7*</dd>
    <dt><strong>severity</strong></dt>
    <dd>one of syslog severity strings: *emergency, alert, critical, error, warning, notice, informational, debug*</dd>
    <dt><strong>source</strong></dt>
    <dd>IP address or host name of message source</dd>
    <dt><strong>message</strong></dt>
    <dd>the text of the message itself</dd>
</dl>

## Command line

General invocation is:

    syslog-bulk-uploader [option]... [file]...

Option is one of the following:

<dl>
    <dt><strong>-h --help</strong></dt>
    <dd>display help message, then exit</dd>
    <dt><strong>-v --version</strong></dt>
    <dd>display version information, then exit</dd>
    <dt><strong>-m --mps</strong> num</dt>
    <dd>send messages at specified rate per second; default, if not specified, is 1000</dd>
    <dt><strong>-d --dest</strong> dest</dt>
    <dd>destination host name</dd>
    <dt><strong>-p --port</strong> arg</dt>
    <dd>destination port; default, if not specified, is 514</dd>
    <dt><strong>[-f --files]</strong> filename</dt>
    <dd>one or more input files; option name (-f or --file) is optional, i.e. all non-named arguments will be interpreted as filenames</dd>
</dl>

If more than one input file is specified on the command line, syslog-bulk-uploader will send contents of each one in the order specified.

## Building from source

### Dependencies
In order to build syslog-bulk-uploader from source, you will need to have a couple of dependencies pre-installed on your system:

* [CMake](http://www.cmake.org) as the build system
* Any recent C++ compiler supported by CMake on your platform (GCC, Clang, Visual C++, etc)
* boost-date-time library
* boost-filesystem library
* boost-system library
* boost-thread library
* boost-program-options library
* `a2x` executable (part of [AsciiDoc](http://www.methods.co.nz/asciidoc), required to build man page)

### Building
Once you have all the pre-requisites:

    git clone git@github.com:zmarko/syslog-bulk-uploader.git
    cd syslog-bulk-uploader/build
    cmake ..
    make && make install

### Installers
During the build it is also possible to build installer packages. Supported installers at this time are:
**RPM**, **DEB** and plain **.tar.gz** archive.
