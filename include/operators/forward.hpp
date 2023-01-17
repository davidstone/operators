// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef OPERATORS_FORWARD_HPP
#define OPERATORS_FORWARD_HPP

// This must use a variadic macro in case the argument has a comma
#define OPERATORS_FORWARD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

#endif // OPERATORS_FORWARD_HPP