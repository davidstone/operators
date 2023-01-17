// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/returns.hpp>

export module operators.increment_decrement;

import std_module;

#define OPERATORS_PREFIX_INCREMENT_DEFINITION \
	constexpr auto operator++(auto & value) OPERATORS_RETURNS( \
		value += 1 \
	)

#define OPERATORS_PREFIX_DECREMENT_DEFINITION \
	constexpr auto operator--(auto & value) OPERATORS_RETURNS( \
		value -= 1 \
	)

namespace operators {

template<typename T>
concept prefix_incrementable = requires(T value) { ++value; };

template<typename T>
concept prefix_decrementable = requires(T value) { --value; };

template<typename T>
constexpr auto postfix_increment_impl(T & value) {
	if constexpr (std::is_copy_constructible_v<T>) {
		auto previous = value;
		++value;
		return previous;
	} else {
		++value;
	}
}

template<typename T>
constexpr auto postfix_decrement_impl(T & value) {
	if constexpr (std::is_copy_constructible_v<T>) {
		auto previous = value;
		--value;
		return previous;
	} else {
		--value;
	}
}

} // namespace operators

#define OPERATORS_POSTFIX_INCREMENT_DEFINITION \
	constexpr auto operator++(operators::prefix_incrementable auto & value, int) { \
		return ::operators::postfix_increment_impl(value); \
	}

#define OPERATORS_POSTFIX_DECREMENT_DEFINITION \
	constexpr auto operator--(operators::prefix_decrementable auto & value, int) { \
		return ::operators::postfix_decrement_impl(value); \
	}

namespace operators_impl {

namespace prefix_increment {
struct impl {
	friend OPERATORS_PREFIX_INCREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace prefix_decrement {
struct impl {
	friend OPERATORS_PREFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace postfix_increment {
struct impl {
	friend OPERATORS_POSTFIX_INCREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace postfix_decrement {
struct impl {
	friend OPERATORS_POSTFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace increment {
struct impl {
	friend OPERATORS_PREFIX_INCREMENT_DEFINITION
	friend OPERATORS_POSTFIX_INCREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace decrement {
struct impl {
	friend OPERATORS_PREFIX_DECREMENT_DEFINITION
	friend OPERATORS_POSTFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace prefix {
struct impl {
	friend OPERATORS_PREFIX_INCREMENT_DEFINITION
	friend OPERATORS_PREFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace postfix {
struct impl {
	friend OPERATORS_POSTFIX_INCREMENT_DEFINITION
	friend OPERATORS_POSTFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};

}
namespace all {
struct impl {
	friend OPERATORS_PREFIX_INCREMENT_DEFINITION
	friend OPERATORS_PREFIX_DECREMENT_DEFINITION
	friend OPERATORS_POSTFIX_INCREMENT_DEFINITION
	friend OPERATORS_POSTFIX_DECREMENT_DEFINITION
	friend auto operator<=>(impl, impl) = default;
};
}

} // namespace operators_impl

namespace operators {
namespace prefix {

export OPERATORS_PREFIX_INCREMENT_DEFINITION
export OPERATORS_PREFIX_DECREMENT_DEFINITION
export using increment = operators_impl::prefix_increment::impl;
export using decrement = operators_impl::prefix_decrement::impl;
export using increment_decrement = operators_impl::prefix::impl;

} // namespace prefix
namespace postfix {

export OPERATORS_POSTFIX_INCREMENT_DEFINITION
export OPERATORS_POSTFIX_DECREMENT_DEFINITION
export using increment = operators_impl::postfix_increment::impl;
export using decrement = operators_impl::postfix_decrement::impl;
export using increment_decrement = operators_impl::postfix::impl;

} // namespace postfix

export using operators::prefix::operator++;
export using operators::prefix::operator--;
export using operators::postfix::operator++;
export using operators::postfix::operator--;
export using increment = operators_impl::increment::impl;
export using decrement = operators_impl::decrement::impl;
export using increment_decrement = operators_impl::all::impl;

} // namespace operators

namespace {

template<typename T>
concept has_prefix_increment = requires(T value) { ++value; };

template<typename T>
concept has_postfix_increment = requires(T value) { value++; };

template<typename T>
concept has_prefix_decrement = requires(T value) { --value; };

template<typename T>
concept has_postfix_decrement = requires(T value) { value--; };

template<typename T>
concept has_increment = has_prefix_increment<T> and has_postfix_increment<T>;

template<typename T>
concept has_decrement = has_prefix_decrement<T> and has_postfix_decrement<T>;

constexpr auto prefix_increment = [](auto & value) { return ++value; };
constexpr auto postfix_increment = [](auto & value) { return value++; };
constexpr auto prefix_decrement = [](auto & value) { return --value; };
constexpr auto postfix_decrement = [](auto & value) { return value--; };

constexpr auto test_increment_decrement(auto value, auto const expected_value, auto const expected_result, auto const function) {
	auto const result = function(value);
	return result == expected_result and value == expected_value;
}

namespace base_all {

struct s : private operators::increment_decrement {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace base_all

namespace base_increment {

struct s : private operators::increment {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace base_increment

namespace base_decrement {

struct s : private operators::decrement {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace base_decrement

namespace base_prefix_increment {

struct s : private operators::prefix::increment {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(!has_postfix_increment<s>);
static_assert(!has_decrement<s>);

} // namespace base_prefix_increment

namespace bad_base_postfix_increment {

struct s : private operators::postfix::increment {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(!has_decrement<s>);

} // namespace bad_base_postfix_increment

namespace base_postfix_increment {

struct s : private operators::postfix::increment {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator++(auto & x) {
		++x.value;
		return x;
	}
	friend constexpr auto & operator--(auto & x) {
		--x.value;
		return x;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace base_postfix_increment

namespace base_prefix_decrement {

struct s : private operators::prefix::decrement {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(!has_postfix_decrement<s>);

} // namespace base_prefix_decrement

namespace base_base_postfix_decrement {

struct s : private operators::postfix::decrement {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_decrement<s>);
static_assert(!has_decrement<s>);

} // namespace base_base_postfix_decrement

namespace base_postfix_decrement {

struct s : private operators::postfix::decrement {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator++(auto & x) {
		++x.value;
		return x;
	}
	friend constexpr auto & operator--(auto & x) {
		--x.value;
		return x;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace base_postfix_decrement

namespace declarations_all {

using operators::operator++;
using operators::operator--;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace declarations_all

static_assert(test_increment_decrement(declarations_all::s(5), declarations_all::s(6), declarations_all::s(6), prefix_increment));
static_assert(test_increment_decrement(declarations_all::s(5), declarations_all::s(6), declarations_all::s(5), postfix_increment));
static_assert(test_increment_decrement(declarations_all::s(5), declarations_all::s(4), declarations_all::s(4), prefix_decrement));
static_assert(test_increment_decrement(declarations_all::s(5), declarations_all::s(4), declarations_all::s(5), postfix_decrement));


namespace declarations_increment {

using operators::operator++;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace declarations_increment

static_assert(test_increment_decrement(declarations_increment::s(5), declarations_increment::s(6), declarations_increment::s(6), prefix_increment));
static_assert(test_increment_decrement(declarations_increment::s(5), declarations_increment::s(6), declarations_increment::s(5), postfix_increment));
static_assert(!has_decrement<declarations_increment::s>);


namespace declarations_decrement {

using operators::operator--;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace declarations_decrement

static_assert(!has_increment<declarations_decrement::s>);
static_assert(test_increment_decrement(declarations_decrement::s(5), declarations_decrement::s(4), declarations_decrement::s(4), prefix_decrement));
static_assert(test_increment_decrement(declarations_decrement::s(5), declarations_decrement::s(4), declarations_decrement::s(5), postfix_decrement));


namespace declarations_prefix_increment {

using operators::prefix::operator++;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(!has_postfix_increment<s>);
static_assert(!has_decrement<s>);

} // namespace declarations_prefix_increment

static_assert(test_increment_decrement(declarations_prefix_increment::s(5), declarations_prefix_increment::s(6), declarations_prefix_increment::s(6), prefix_increment));
static_assert(!has_postfix_increment<declarations_prefix_increment::s>);
static_assert(!has_decrement<declarations_prefix_increment::s>);


namespace declarations_bad_postfix_increment {

using operators::postfix::operator++;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(!has_decrement<s>);

} // namespace declarations_bad_postfix_increment

static_assert(!has_increment<declarations_bad_postfix_increment::s>);
static_assert(!has_decrement<declarations_bad_postfix_increment::s>);


namespace declarations_postfix_increment {

using operators::postfix::operator++;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator++(auto & x) {
		++x.value;
		return x;
	}
	friend constexpr auto & operator--(auto & x) {
		--x.value;
		return x;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace declarations_postfix_increment

static_assert(test_increment_decrement(declarations_postfix_increment::s(5), declarations_postfix_increment::s(6), declarations_postfix_increment::s(6), prefix_increment));
static_assert(test_increment_decrement(declarations_postfix_increment::s(5), declarations_postfix_increment::s(6), declarations_postfix_increment::s(5), postfix_increment));
static_assert(!has_decrement<declarations_postfix_increment::s>);


namespace declarations_prefix_decrement {

using operators::prefix::operator--;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(!has_postfix_decrement<s>);

} // namespace declarations_prefix_decrement

static_assert(!has_increment<declarations_prefix_decrement::s>);
static_assert(test_increment_decrement(declarations_prefix_decrement::s(5), declarations_prefix_decrement::s(4), declarations_prefix_decrement::s(4), prefix_decrement));
static_assert(!has_postfix_decrement<declarations_prefix_decrement::s>);


namespace declarations_bad_postfix_decrement {

using operators::postfix::operator--;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator+=(auto & lhs, int rhs) {
		lhs.value += rhs;
		return lhs;
	}
	friend constexpr auto & operator-=(auto & lhs, int rhs) {
		lhs.value -= rhs;
		return lhs;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_decrement<s>);
static_assert(!has_decrement<s>);

} // namespace declarations_bad_postfix_decrement

static_assert(!has_decrement<declarations_bad_postfix_decrement::s>);
static_assert(!has_decrement<declarations_bad_postfix_decrement::s>);


namespace declarations_postfix_decrement {

using operators::postfix::operator--;

struct s {
	constexpr explicit s(int value_):
		value(value_)
	{
	}

	friend constexpr auto & operator++(auto & x) {
		++x.value;
		return x;
	}
	friend constexpr auto & operator--(auto & x) {
		--x.value;
		return x;
	}

	friend auto operator==(s, s) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace declarations_postfix_decrement

static_assert(!has_increment<declarations_postfix_decrement::s>);
static_assert(test_increment_decrement(declarations_postfix_decrement::s(5), declarations_postfix_decrement::s(4), declarations_postfix_decrement::s(4), prefix_decrement));
static_assert(test_increment_decrement(declarations_postfix_decrement::s(5), declarations_postfix_decrement::s(4), declarations_postfix_decrement::s(5), postfix_decrement));

} // namespace