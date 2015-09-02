find_package(Boost COMPONENTS unit_test_framework date_time REQUIRED)
include_directories(
    ${TEST_SOURCE_DIR/src}
    ${Boost_INLUDE_DIRS}
)
add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(SyslogBulkUploaderTests SyslogBulkUploaderTests.cpp)
target_link_libraries(SyslogBulkUploaderTests
	slbu-lib
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_executable(SyslogMessageTests SyslogMessageTests.cpp)
target_link_libraries(SyslogMessageTests
	slbu-lib
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY}
)

