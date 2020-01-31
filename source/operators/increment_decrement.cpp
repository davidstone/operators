// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/increment_decrement.hpp>

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

struct s : operators::increment, operators::decrement {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace base_all

namespace base_increment {

struct s : operators::increment {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace base_increment

namespace base_decrement {

struct s : operators::decrement {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(test_increment_decrement(s(5), s(4), s(5), postfix_decrement));

} // namespace base_decrement

namespace base_prefix_increment {

struct s : operators::prefix::increment {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(!has_postfix_increment<s>);
static_assert(!has_decrement<s>);

} // namespace base_prefix_increment

namespace bad_base_postfix_increment {

struct s : operators::postfix::increment {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(!has_decrement<s>);

} // namespace bad_base_postfix_increment

namespace base_postfix_increment {

struct s : operators::postfix::increment {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(test_increment_decrement(s(5), s(6), s(6), prefix_increment));
static_assert(test_increment_decrement(s(5), s(6), s(5), postfix_increment));
static_assert(!has_decrement<s>);

} // namespace base_postfix_increment

namespace base_prefix_decrement {

struct s : operators::prefix::decrement {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(!has_increment<s>);
static_assert(test_increment_decrement(s(5), s(4), s(4), prefix_decrement));
static_assert(!has_postfix_decrement<s>);

} // namespace base_prefix_decrement

namespace base_base_postfix_decrement {

struct s : operators::postfix::decrement {
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

	friend auto operator==(s const &, s const &) -> bool = default;
private:
	int value;
};

static_assert(!has_decrement<s>);
static_assert(!has_decrement<s>);

} // namespace base_base_postfix_decrement

namespace base_postfix_decrement {

struct s : operators::postfix::decrement {
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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

	friend auto operator==(s const &, s const &) -> bool = default;
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