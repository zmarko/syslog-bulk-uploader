cmake_minimum_required(VERSION 2.8)
project(syslog-bulk-uploader)
set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)
add_subdirectory(test)
enable_testing()
add_test(NAME SyslogBulkUploaderTests COMMAND SyslogBulkUploaderTests)

