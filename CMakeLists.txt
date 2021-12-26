# Copyright David Stone 2019.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(operators LANGUAGES CXX)

enable_testing()

get_directory_property(has_parent PARENT_DIRECTORY)
if (NOT has_parent)
	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_STANDARD_REQUIRED On)
	set(CMAKE_CXX_EXTENSIONS Off)

	add_subdirectory(dependencies/cmake_strict_defaults)
endif()

add_library(operators INTERFACE)

target_include_directories(operators INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(operators INTERFACE strict_defaults_interface)

add_executable(operators_test
	source/operators/arrow.cpp
	source/operators/arrow_star.cpp
	source/operators/binary_minus.cpp
	source/operators/bracket.cpp
	source/operators/compound_assignment.cpp
	source/operators/forward.cpp
	source/operators/increment_decrement.cpp
	source/operators/operators.cpp
	source/operators/returns.cpp
	source/operators/unary_minus.cpp
	source/operators/unary_plus.cpp
)

target_link_libraries(operators_test PUBLIC operators strict_defaults)

add_test(operators_test operators_test)
