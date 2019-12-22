# Copyright David Stone 2019.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(operators LANGUAGES CXX)

enable_testing()

# For options that are not necessary to use the library, but are how I want to
# compile tests
add_library(strict_defaults INTERFACE)

add_library(operators INTERFACE)

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

target_link_libraries(operators_test PUBLIC operators strict_defaults)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	if(MSVC)
		# Sanitizers currently do not work very well on Windows
		set(USE_SANITIZERS OFF)

		target_compile_options(operators INTERFACE
			"/std:c++latest"
		)
		target_compile_options(strict_defaults INTERFACE
			"/MP"
		)
		target_link_options(strict_defaults INTERFACE
			"/WX"
		)
	else()
		target_compile_options(operators INTERFACE
			"-Xclang"
			"-fconcepts-ts"
			"-std=c++2a"
			"-stdlib=libc++"
		)
		target_link_options(operators INTERFACE
			"-stdlib=libc++"
			"-fuse-ld=lld"
		)
		target_link_options(strict_defaults INTERFACE
			"-Wl,--fatal-warnings"
			# TODO: Figure out how to make this work on Visual Studio
			"-Wl,--thinlto-cache-dir=${CMAKE_BINARY_DIR}/lto-cache"
		)
	endif()

	target_compile_options(strict_defaults INTERFACE
		"-Weverything"
		"-Werror"
		# Don't need compatibility with older standards
		"-Wno-c++98-compat"
		# Don't need compatibility with older standards
		"-Wno-c++98-compat-pedantic"
		# This warning tries to enforce a particular coding standard
		"-Wno-ctad-maybe-unsupported"
		# Complains about comments like "//<N3757>" referring to an ISO paper number
		"-Wno-documentation"
		# There are too many cases of correct exact comparisons
		"-Wno-float-equal"
		# -Wmissing-braces wants two sets of braces for std::array
		"-Wno-missing-braces"
		"-Wno-newline-eof"
		# https://bugs.llvm.org/show_bug.cgi?id=22442#c5
		"-Wno-padded"
		# Warns about intentional copies in range-based for loops
		"-Wno-range-loop-analysis"
		# Don't need compatibility with older standards
		"-Wno-return-std-move-in-c++11"
		# -Wswitch-enum warns even if you have default
		"-Wno-switch-enum"
		# https://llvm.org/bugs/show_bug.cgi?id=25084
		"-Wno-unneeded-member-function"
		"-Wno-unused-function"
		"-Wno-unused-member-function"
		"-Wno-unused-template"
		# -Wweak-vtables is incompatible with header-only libraries. It also
		# becomes irrelevant after modules.
		"-Wno-weak-vtables"
		# https://bugs.llvm.org/show_bug.cgi?id=44325
		"-Wno-zero-as-null-pointer-constant"

		"-g"
		"-march=native"
		$<$<CONFIG:Release>:-flto=thin>
	)

elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(operators INTERFACE
		"-std=c++2a"
		"-fconcepts"
	)
	target_compile_options(strict_defaults INTERFACE
		# We have to start by turning off all warnings just so we can disable a
		# warning about an inaccessible base class. Then we turn on all
		# possible warnings. This means that some on-by-default warnings are
		# disabled with no way to re-enable. See
		# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=90449.
		"-w"
		"-Waggressive-loop-optimizations"
		"-Wattribute-alias=2"
		"-Wattributes"
		"-Wattribute-warning"
		"-Wbuiltin-declaration-mismatch"
		"-Wbuiltin-macro-redefined"
		"-Wconversion-null"
		"-Wcoverage-mismatch"
		"-Wcpp"
		"-Wdeprecated"
		"-Wdeprecated-declarations"
		"-Wdiv-by-zero"
		"-Wendif-labels"
		"-Wfree-nonheap-object"
		"-Winherited-variadic-ctor"
		"-Wint-to-pointer-cast"
		"-Winvalid-offsetof"
		"-Wmultichar"
		"-Wodr"
		"-Woverflow"
		"-Wpragmas"
		"-Wprio-ctor-dtor"
		"-Wrestrict"
		"-Wreturn-local-addr"
		"-Wscalar-storage-order"
		"-Wunused-result"
		"-Wvariadic-macros"
		"-Wvirtual-move-assign"

		"-Wall"
		"-Wextra"
		"-Wpedantic"
		# Do not care about ABI differences
		# "-Wabi"
		"-Wcast-align"
		"-Wcast-qual"
		# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=39170
		#"-Wconversion"
		"-Wctor-dtor-privacy"
		"-Wdisabled-optimization"
		"-Wdouble-promotion"
		# -Weffc++ includes a warning if all data members are not explicitly
		# initialized in the initializer list. I intentionally do not do this in
		# many cases. This would be more useful as a collection of warnings
		# like -Wall instead of a single warning on its own.
		# "-Weffc++"
		# There are too many cases of correct exact comparisons
		"-Wno-float-equal"
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
		# https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52981#c5
		"-Wno-padded"
		"-Wredundant-decls"
		"-Wshadow"
		"-Wsign-conversion"
		"-Wsign-promo"
		# -Wsuggest-final-methods and -Wsuggest-final-types is a linker warning,
		# so it is not possible to disable it for boost and other third-party
		# libraries by saying they are system headers.
		# "-Wsuggest-final-methods"
		# "-Wsuggest-final-types"
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
		# range-based for loop). It is also warning for the constructor of a
		# const array of const std::string where there is no loop in user code.
		# "-Wunsafe-loop-optimizations"
		# -Wunused-but-set-parameter does not properly account for
		# `if constexpr` branches.
		"-Wno-unused-but-set-parameter"
		# -Wunused-but-set-variable does not properly account for
		# `if constexpr` branches.
		"-Wno-unused-but-set-variable"
		# Incompatible with operator?: macro
		# "-Wuseless-cast"
		"-Wvector-operation-performance"
		# -Wzero-as-null-pointer-constant does not work with the `operator<=>`
		# emulation
		# "-Wzero-as-null-pointer-constant"
		"-Werror"

		"-g"
		"-march=native"
		$<$<CONFIG:Release>:-flto=4 -flto-odr-type-merging -fuse-linker-plugin>
	)
else()
	message(FATAL_ERROR "Unknown compiler " "${CMAKE_CXX_COMPILER_ID}")
endif()

if(DEFINED USE_SANITIZERS)
	if(${USE_SANITIZERS})
		target_compile_options(strict_defaults PUBLIC ${sanitizers})
		target_link_options(strict_defaults PUBLIC ${sanitizers})
	endif()
else()
	target_compile_options(strict_defaults INTERFACE
		$<$<CONFIG:Debug>:${sanitizers}>
	)
	target_link_options(strict_defaults INTERFACE
		$<$<CONFIG:Debug>:${sanitizers}>
	)
endif()

add_test(operators_test operators_test)
