# Copyright David Stone 2019.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(operators LANGUAGES CXX)

enable_testing()

add_library(operators INTERFACE)

target_sources(operators INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/arrow.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/arrow_star.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/binary_minus.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/bracket.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/compound_assignment.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/forward.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/increment_decrement.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/operators.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/unary_minus.hpp
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include/operators/unary_plus.hpp
)

target_include_directories(operators INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

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

target_link_libraries(operators_test PUBLIC operators)

set(COMMON_CLANG_COMPILE_OPTIONS
	"-Xclang"
	"-fconcepts-ts"
	"-Weverything"
	"-Werror"
	"-Wno-c++98-compat"
	"-Wno-c++98-compat-pedantic"
	"-Wno-newline-eof"
	"-Wno-unused-function"
	"-Wno-unused-member-function"
	"-Wno-unused-template"
)

if(MSVC)
	target_compile_options(operators INTERFACE
		"/std:c++latest"
		"/MP"
	)
	target_link_options(operators INTERFACE
		"/WX"
	)

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_options(operators INTERFACE
			${COMMON_CLANG_COMPILE_OPTIONS}
		)
	else()
		target_compile_options(operators INTERFACE
			"/FI ciso646"
		)
	endif()

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	target_compile_options(operators INTERFACE
		"-std=c++2a"
	)
	target_compile_options(operators INTERFACE
		${COMMON_CLANG_COMPILE_OPTIONS}
		"-g"
		"-stdlib=libc++"
		"-march=native"
		$<$<CONFIG:Release>:-flto=thin>
	)
	target_link_options(operators INTERFACE
		"-Wl,--fatal-warnings"
		"-stdlib=libc++"
		"-fuse-ld=lld"
		# TODO: Figure out how to make this work on Visual Studio
		"-Wl,--thinlto-cache-dir=${CMAKE_BINARY_DIR}/lto-cache"
	)

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(operators INTERFACE
		"-std=c++2a"
	)
	target_compile_options(operators INTERFACE
		"-g"
		"-march=native"
		"-fconcepts"
		$<$<CONFIG:Release>:-flto=4 -flto-odr-type-merging -fuse-linker-plugin>
		"-Wall"
		"-Wextra"
		"-Wpedantic"
		# Do not care about ABI differences
		# "-Wabi"
		"-Wcast-align"
		"-Wcast-qual"
		# It seems impossible to initialize bit fields with this warning on
		#"-Wconversion"
		"-Wctor-dtor-privacy"
		"-Wdisabled-optimization"
		"-Wdouble-promotion"
		# -Weffc++ includes a warning if all data members are not explicitly
		# initialized in the initializer list. I intentionally do not do this in
		# many cases. This would be more useful as a collection of warnings
		# like -Wall instead of a single warning on its own.
		# "-Weffc++"
		"-Wfloat-equal"
		"-Wformat=2"
		"-Winit-self"
		"-Winvalid-pch"
		# -Wlogical-op warns for expressions that happen to be equal in a
		# template instantiation
		# "-Wlogical-op"
		"-Wmissing-declarations"
		# -Wmissing-format-attribute is not used because I do not use GNU
		# extensions. Same for -Wsuggest-attribute and several others.
		"-Wmissing-include-dirs"
		#"-Wnoexcept"
		"-Wno-non-template-friend"
		"-Wold-style-cast"
		"-Woverloaded-virtual"
		"-Wredundant-decls"
		"-Wshadow"
		"-Wsign-conversion"
		"-Wsign-promo"
		"-Wsuggest-final-methods"
		"-Wsuggest-final-types"
		"-Wstrict-null-sentinel"
		# -Wstrict-overflow=2 warns about comparing two pointers
		"-Wstrict-overflow=1"
		"-Wswitch-default"
		"-Wswitch-enum"
		"-Wtrampolines"
		"-Wundef"
		# -Wunsafe-loop-optimizations causes too many spurious warnings. It may
		# be useful to apply this one periodically and manually verify the
		# results. It generated this warning in my code when I looped over all
		# elements in a vector to apply a set of functions to them (using the
		# range-based for loop).  It is also warning for the constructor of a
		# const array of const std::string where there is no loop in user code.
		# "-Wunsafe-loop-optimizations"
		# -Wunused-but-set-parameter does not properly account for
		# `if constexpr` branches.
		"-Wno-unused-but-set-parameter"
		# -Wunused-but-set-variable does not properly account for
		# `if constexpr` branches.
		"-Wno-unused-but-set-variable"
		"-Wuseless-cast"
		"-Wvector-operation-performance"
		"-Werror"
	)
endif()

set(all_targets operators_test)

add_test(operators_test operators_test)
