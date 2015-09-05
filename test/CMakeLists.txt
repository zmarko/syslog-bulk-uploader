find_package(Boost COMPONENTS unit_test_framework date_time filesystem system REQUIRED)
find_package(Threads)
include_directories(
    ${TEST_SOURCE_DIR/src}
    ${Boost_INLUDE_DIRS}
)
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(SyslogBulkUploaderTests SyslogBulkUploaderTests.cpp)
target_link_libraries(SyslogBulkUploaderTests
	slbu-lib
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(SyslogMessageTests SyslogMessageTests.cpp)
target_link_libraries(SyslogMessageTests
	slbu-lib
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)

add_executable(RFC3164FormattedSyslogMessageTests RFC3164FormattedSyslogMessageTests.cpp)
target_link_libraries(RFC3164FormattedSyslogMessageTests
	slbu-lib
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)

