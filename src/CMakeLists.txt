find_package(Boost COMPONENTS date_time REQUIRED)
include_directories(
    ${Boost_INLUDE_DIRS}
)

add_library(slbu-lib 
    SyslogBulkUploader.cpp
    Facility.cpp
    Severity.cpp
    SyslogMessage.cpp
)

add_executable(syslog-bulk-uploader main.cpp)
target_link_libraries(syslog-bulk-uploader
    slbu-lib
    ${Boost_DATE_TIME_LIBRARY}
)
