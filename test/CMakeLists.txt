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

add_executable(SyslogBulkUploaderTests SyslogBulkUploaderTests.cpp)
target_link_libraries(SyslogBulkUploaderTests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_THREAD_LIBRARY}
)
if(WIN32)
    target_link_libraries(SyslogBulkUploaderTests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(SyslogMessageTests SyslogMessageTests.cpp)
target_link_libraries(SyslogMessageTests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)
if(WIN32)
    target_link_libraries(SyslogMessageTests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(RFC3164FormattedSyslogMessageTests RFC3164FormattedSyslogMessageTests.cpp)
target_link_libraries(RFC3164FormattedSyslogMessageTests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)
if(WIN32)
    target_link_libraries(RFC3164FormattedSyslogMessageTests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

add_executable(FrequencyLimitTests FrequencyLimitTests.cpp)
target_link_libraries(FrequencyLimitTests
        slbu-lib
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
)
if(WIN32)
    target_link_libraries(FrequencyLimitTests
        ${Boost_REGEX_LIBRARY}
        ${Boost_CHRONO_LIBRARY}
    )
endif()

