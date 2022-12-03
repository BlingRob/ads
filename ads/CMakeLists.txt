project(ads)

set(CMAKE_CXX_STANDARD 17)

#Searching sourse files
file(GLOB_RECURSE SOURCE_FILES
			source/*.c
			source/*.cpp)

file(GLOB_RECURSE HEADER_FILES
			headers/*.h
			headers/*.hpp)

#TODO while it is not library			
#add_library(${PROJECT_NAME} STATIC SOURCE_FILES)

set(ADS_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers PARENT_SCOPE)
include_directories(ADS_HEADER_DIR)

if(NOT WIN32)
	list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -fpermissive ${CMAKE_CXX_FLAGS}")
endif()
