cmake_minimum_required(VERSION 2.8)
project(syslog_-bulk_-uploader)
set(SLBU_DESC "syslog_ bulk_ uploader")
set(SLBU_VER "1.1.0-alpha.1")

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
	add_definitions(-std=c++14)
endif()

if(WIN32)
	add_definitions(-DWINVER=0x0601)
	add_definitions(-D_WIN32_WINNT=0x0601)
endif()

if(MSVC)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME syslog_bulk_uploader_tests COMMAND syslog_bulk_uploader_tests)
add_test(NAME syslog_message_tests COMMAND syslog_message_tests)
add_test(NAME RFC3164_fmt_tests COMMAND RFC3164_fmt_tests)
add_test(NAME frequency_limit_tests COMMAND frequency_limit_tests)

