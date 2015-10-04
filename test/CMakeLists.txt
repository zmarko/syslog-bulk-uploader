set(BOOST_LIBS unit_test_framework date_time filesystem system thread)
if(WIN32)
    list(APPEND BOOST_LIBS regex chrono)
endif()

find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
find_package(Threads)
include_directories(
    ${TEST_SOURCE_DIR/src}
    ${Boost_INCLUDE_DIRS}
)
#add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(syslog_bulk_uploader_tests syslog_bulk_uploader_tests.cpp Udp_syslog_server.cpp)
target_link_libraries(syslog_bulk_uploader_tests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_THREAD_LIBRARY}
)
if(WIN32)
    target_link_libraries(syslog_bulk_uploader_tests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(syslog_message_tests syslog_message_tests.cpp)
target_link_libraries(syslog_message_tests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)
if(WIN32)
    target_link_libraries(syslog_message_tests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(RFC3164_fmt_tests RFC3164_fmt_tests.cpp)
target_link_libraries(RFC3164_fmt_tests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)
if(WIN32)
    target_link_libraries(RFC3164_fmt_tests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(frequency_limit_tests frequency_limit_tests.cpp)
target_link_libraries(frequency_limit_tests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
		${CMAKE_THREAD_LIBS_INIT}
)
if(WIN32)
    target_link_libraries(frequency_limit_tests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

