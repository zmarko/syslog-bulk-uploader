set(BOOST_LIBS date_time filesystem system thread program_options)
if(WIN32)
	list(APPEND BOOST_LIBS regex chrono)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Statically link C++ library for better compatibility on different Linux distributions
    SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
find_package(Threads)

configure_file("config.h.in" "config.h")

include_directories(
    ${PROJECT_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
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

if(WIN32)
	target_link_libraries(syslog-bulk-uploader
		${Boost_REGEX_LIBRARY}
		${Boost_CHRONO_LIBRARY}
	)
endif()

install(TARGETS syslog-bulk-uploader DESTINATION bin)

##
## Installers configuration
##
include(InstallRequiredSystemLibraries)
if(WIN32)
	set(CPACK_GENERATOR "ZIP")
else()
	set(CPACK_GENERATOR "RPM;DEB;TGZ")
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${VER_NAME}")
set(CPACK_PACKAGE_VENDOR "Marko Zivanovic <marko@zivanovic.in.rs>")
set(CPACK_PACKAGE_CONTACT "${CPACK_PACKAGE_VENDOR}")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/PackageDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Utility to send messages from file to remote syslog server")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE")
set(CPACK_PACKAGE_VERSION "${SLBU_VER}")
set(CPACK_SOURCE_STRIP_FILES TRUE)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
set(CPACK_DEBIAN_PACKAGE_SECTION "net")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/zmarko/syslog-bulk-uploader")
include(CPack)

##
## Generate documentation
##
if(UNIX)
	find_program(A2X_EXECUTABLE NAMES a2x)
	set(A2X_OPTS --doctype manpage --format manpage -D ${CMAKE_CURRENT_BINARY_DIR})

	set(MAN_NAMES syslog-bulk-uploader.1)
	set(MAN_FILES)
	foreach(m IN LISTS MAN_NAMES)
	    set(mf ${CMAKE_CURRENT_BINARY_DIR}/${m})
	    set(ms ${CMAKE_CURRENT_SOURCE_DIR}/${m}.txt)
	    add_custom_command(OUTPUT ${mf}
	        COMMAND ${A2X_EXECUTABLE} ${A2X_OPTS} ${ms}
	        DEPENDS ${ms}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	        COMMENT "Building manpage ${mf}"
	        VERBATIM)
	    list(APPEND MAN_FILES ${mf})
	endforeach()

	add_custom_target(man ALL DEPENDS ${MAN_FILES})
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/syslog-bulk-uploader.1 DESTINATION man/man1/)
endif()