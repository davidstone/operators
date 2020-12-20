// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <operators/returns.hpp>

#include <compare>
#include <type_traits>

// cannot use inline namespaces because that causes unintended ADL
namespace operators {
namespace detail {

template<typename T>
concept prefix_incrementable = requires(T value) { ++value; };

template<typename T>
concept prefix_decrementable = requires(T value) { --value; };

} // namespace detail


namespace prefix_increment {

constexpr auto operator++(auto & value) OPERATORS_RETURNS(
	value += 1
)

struct prefix_increment_tag {
	friend auto operator<=>(prefix_increment_tag, prefix_increment_tag) = default;
};

} // namespace prefix_increment;

using namespace prefix_increment;


namespace prefix_decrement {

constexpr auto operator--(auto & value) OPERATORS_RETURNS(
	value -= 1
)

struct prefix_decrement_tag {
	friend auto operator<=>(prefix_decrement_tag, prefix_decrement_tag) = default;
};

} // namespace prefix_decrement

using namespace prefix_decrement;


namespace prefix {
using namespace prefix_increment;
using increment = prefix_increment_tag;
using namespace prefix_decrement;
using decrement = prefix_decrement_tag;
} // namespace prefix


namespace postfix_increment {

template<detail::prefix_incrementable T>
constexpr auto operator++(T & value, int) {
	if constexpr (std::is_copy_constructible_v<T>) {
		auto previous = value;
		++value;
		return previous;
	} else {
		++value;
	}
}

struct postfix_increment_tag {
	friend auto operator<=>(postfix_increment_tag, postfix_increment_tag) = default;
};

} // namespace postfix_increment

using namespace postfix_increment;


namespace postfix_decrement {

template<detail::prefix_decrementable T>
constexpr auto operator--(T & value, int) {
	if constexpr (std::is_copy_constructible_v<T>) {
		auto previous = value;
		--value;
		return previous;
	} else {
		--value;
	}
}

struct postfix_decrement_tag {
	friend auto operator<=>(postfix_decrement_tag, postfix_decrement_tag) = default;
};

} // namespace postfix_decrement

using namespace postfix_decrement;


namespace postfix {

using namespace postfix_increment;
using increment = postfix_increment_tag;
using namespace postfix_decrement;
using decrement = postfix_decrement_tag;

} // namespace postfix


namespace all_increment {

using prefix::operator++;
using postfix::operator++;

struct increment {
	friend auto operator<=>(increment, increment) = default;
};

} // namespace all_increment
using namespace all_increment;

namespace all_decrement {

using prefix::operator--;
using postfix::operator--;

struct decrement {
	friend auto operator<=>(decrement, decrement) = default;
};

} // namespace all_decrement
using namespace all_decrement;

} // namespace operators
