# Copyright David Stone 2019.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
cmake_policy(VERSION 3.27...3.28)

project(operators LANGUAGES CXX)

enable_testing()

get_directory_property(has_parent PARENT_DIRECTORY)
if (NOT has_parent)
	set(CMAKE_CXX_STANDARD 26)
	set(CMAKE_CXX_STANDARD_REQUIRED On)
	set(CMAKE_CXX_EXTENSIONS Off)

	if(${CMAKE_VERSION} VERSION_LESS "3.28")
		set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
	endif()
	
	add_subdirectory(dependencies/cmake_strict_defaults)
	add_subdirectory(dependencies/std_module)
endif()

add_library(operators STATIC)

target_include_directories(operators PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(operators
	PUBLIC strict_defaults_interface std_module
	PRIVATE strict_defaults
)

target_sources(operators PRIVATE
	source/operators/forward.cpp
	source/operators/returns.cpp
)

target_sources(operators PUBLIC
	FILE_SET CXX_MODULES
	BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES
		source/operators/arrow_impl/addressof_wrapper.cpp
		source/operators/arrow_impl/arrow_impl.cpp
		source/operators/arrow_impl/arrow_proxy_value.cpp
		source/operators/arrow_impl/cast_self.cpp
		source/operators/arrow_impl/indirect.cpp
		source/operators/arrow.cpp
		source/operators/arrow_star.cpp
		source/operators/binary_minus.cpp
		source/operators/bracket.cpp
		source/operators/bracket_impl.cpp
		source/operators/compound_assignment.cpp
		source/operators/compound_assignment_test.cpp
		source/operators/increment_decrement.cpp
		source/operators/operators.cpp
		source/operators/unary_minus.cpp
		source/operators/unary_plus.cpp
)

# Until resolution of https://github.com/llvm/llvm-project/issues/60089
set_source_files_properties(source/operators/compound_assignment.cpp
	PROPERTIES COMPILE_FLAGS "-Wno-implicit-int-conversion -Wno-shorten-64-to-32"
)
