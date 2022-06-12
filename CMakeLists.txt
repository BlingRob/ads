cmake_minimum_required (VERSION 3.8)

project("ads")

set(CMAKE_CXX_STANDARD 17)

#Searching sourse files
file(GLOB_RECURSE SOURCE_FILES
			ads/*.c
			ads/*.cpp)

file(GLOB_RECURSE HEADER_FILES
			ads/*.h
			ads/*.hpp)

add_executable (${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if(NOT WIN32)
	list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -fpermissive ${CMAKE_CXX_FLAGS}")
endif()
