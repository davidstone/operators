// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

// It does not appear to be possible to write a version of this that propagates
// noexcept because of implicit moves of function parameters in return
// statements.
#define OPERATORS_RETURNS(...) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }