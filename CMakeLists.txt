cmake_minimum_required(VERSION 2.8)
project(syslog-bulk-uploader)
set(SLBU_DESC "Syslog Bulk Uploader")
set(SLBU_VER "1.0.0-alpha.1")

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	add_definitions(-std=c++11)
endif()

if(WIN32)
	add_definitions(-DWINVER=0x0601)
	add_definitions(-D_WIN32_WINNT=0x0601)
endif()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME SyslogBulkUploaderTests COMMAND SyslogBulkUploaderTests)
add_test(NAME SyslogMessageTests COMMAND SyslogMessageTests)
add_test(NAME RFC3164FormattedSyslogMessageTests COMMAND RFC3164FormattedSyslogMessageTests)
add_test(NAME FrequencyLimitTests COMMAND FrequencyLimitTests)

