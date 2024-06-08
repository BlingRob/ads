project(ads)

set(CMAKE_CXX_STANDARD 20)

#Searching sourse files
file(GLOB_RECURSE SOURCE_FILES
			source/*.c
			source/*.cpp)

file(GLOB_RECURSE HEADER_FILES
			headers/*.h
			headers/*.hpp)

#TODO while it is not library
set(ADS_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers CACHE STRING "ADS headers")	
include_directories(${ADS_HEADER_DIR})

#add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

#TODO while it is not library
if(NOT WIN32)
	#list(APPEND CMAKE_CXX_FLAGS "-std=c++17 -fpermissive ${CMAKE_CXX_FLAGS}")
endif()
