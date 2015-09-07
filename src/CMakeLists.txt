find_package(Boost COMPONENTS date_time filesystem system thread program_options REQUIRED)
find_package(Threads)
include_directories(
    ${Boost_INLUDE_DIRS}
)

add_library(slbu-lib 
    Facility.cpp
    Severity.cpp
    SyslogBulkUploader.cpp
    SyslogMessage.cpp
    UDPWriter.cpp
)
target_link_libraries(slbu-lib 
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_THREAD_LIBRARY}
)

add_executable(syslog-bulk-uploader main.cpp)
target_link_libraries(syslog-bulk-uploader
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    slbu-lib
)
