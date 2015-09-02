add_library(slbu-lib 
    SyslogBulkUploader.cpp
)
add_executable(syslog-bulk-uploader main.cpp)
target_link_libraries(syslog-bulk-uploader slbu-lib)
