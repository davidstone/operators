// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/returns.hpp>

#include <type_traits>

namespace {

struct move_only {
    move_only() = default;
    move_only(move_only const &) = delete;
    move_only(move_only &&) = default;
};

auto parameter(auto x) OPERATORS_RETURNS(
    x
)

static_assert(std::is_same_v<decltype(parameter(5)), int>);
static_assert(std::is_same_v<decltype(parameter(move_only())), move_only>);

auto prvalue() OPERATORS_RETURNS(
    move_only()
)

static_assert(std::is_same_v<decltype(prvalue()), move_only>);

auto ref(auto && r) OPERATORS_RETURNS(
    r
)

static_assert(std::is_same_v<decltype(ref(move_only())), move_only &&>);

} // namespace