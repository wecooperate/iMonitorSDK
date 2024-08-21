cmake_minimum_required(VERSION 3.10)

if(NOT SDK_INTERNAL)
	project(sample)

	option(GROUP_BY_EXPLORER ON)
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER cmake)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/../bin")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/../bin")
	set(EXECUTABLE_OUTPUT_PATH_DEBUG "${PROJECT_SOURCE_DIR}/../bin")
	set(EXECUTABLE_OUTPUT_PATH_RELEASE "${PROJECT_SOURCE_DIR}/../bin")
	set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../lib")

	add_definitions(-DUNICODE)
	add_definitions(-D_UNICODE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)

	macro(string_append target str)
		set(${target} "${${target}} ${str}")
	endmacro()

	if (MSVC)
		set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /MP")
		set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS})
		set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS})

		string_append(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG /D_DEBUG /Zi /MTd /Od")
		string_append(CMAKE_CXX_FLAGS_RELEASE "/DNODEBUG /D_NODEBUG /Zi /MT /Ob2")
	endif()

	include_directories(. ../inc)
endif()

file(GLOB SOURCE_FILES "*.cpp")

foreach(FILE_PATH IN ITEMS ${SOURCE_FILES})
	STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
	add_executable(${FILE_NAME} ${FILE_PATH})
	SET_TARGET_PROPERTIES(${FILE_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
endforeach()

add_subdirectory(http_access_control)
