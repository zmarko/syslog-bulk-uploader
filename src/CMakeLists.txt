find_package(Boost COMPONENTS date_time filesystem system thread program_options REQUIRED)
find_package(Threads)

configure_file("config.h.in" "config.h")

include_directories(
    ${PROJECT_BINARY_DIR}
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

install(TARGETS syslog-bulk-uploader DESTINATION bin )

##
## Installers configuration
##
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "RPM;DEB")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${VER_NAME}")
set(CPACK_PACKAGE_VENDOR "Marko Zivanovic <marko@zivanovic.in.rs>")
set(CPACK_PACKAGE_CONTACT "${CPACK_PACKAGE_VENDOR}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Utility to send messages from file to remote syslog server")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")
set(CPACK_PACKAGE_VERSION "${SLBU_VER}")
set(CPACK_SOURCE_STRIP_FILES TRUE)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
include(CPack)
