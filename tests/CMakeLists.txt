project(tests)

set(CMAKE_CXX_STANDARD 17)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GTestsPrepare.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/TestSuits.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exe CACHE PATH "" FORCE)

enable_testing()

add_executable(
  ${PROJECT_NAME}
  entry.cpp
#  ${CPP_FILES}
#  ${H_FILES}
)
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
#  ads
)

include_directories(${ADS_HEADER_DIR})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

