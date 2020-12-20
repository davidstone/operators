// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <operators/compound_assignment.hpp>

namespace {

#define OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(type) \
	friend constexpr auto operator+(type const lhs, type const rhs) { \
		return type(lhs.value + rhs.value); \
	} \
	friend constexpr auto operator-(type const lhs, type const rhs) { \
		return type(lhs.value - rhs.value); \
	} \
	friend constexpr auto operator*(type const lhs, type const rhs) { \
		return type(lhs.value * rhs.value); \
	} \
	friend constexpr auto operator/(type const lhs, type const rhs) { \
		return type(lhs.value / rhs.value); \
	} \
	friend constexpr auto operator%(type const lhs, type const rhs) { \
		return type(lhs.value % rhs.value); \
	} \
	friend constexpr auto operator<<(type const lhs, type const rhs) { \
		return type(lhs.value << rhs.value); \
	} \
	friend constexpr auto operator>>(type const lhs, type const rhs) { \
		return type(lhs.value >> rhs.value); \
	} \
	friend constexpr auto operator&(type const lhs, type const rhs) { \
		return type(lhs.value & rhs.value); \
	} \
	friend constexpr auto operator|(type const lhs, type const rhs) { \
		return type(lhs.value | rhs.value); \
	} \
	friend constexpr auto operator^(type const lhs, type const rhs) { \
		return type(lhs.value ^ rhs.value); \
	} \
	friend constexpr auto operator==(type, type) -> bool = default;

constexpr auto plus_equal = [](auto & lhs, auto rhs) { return lhs += rhs; };
constexpr auto minus_equal = [](auto & lhs, auto rhs) { return lhs -= rhs; };
constexpr auto times_equal = [](auto & lhs, auto rhs) { return lhs *= rhs; };
constexpr auto divides_equal = [](auto & lhs, auto rhs) { return lhs /= rhs; };
constexpr auto modulo_equal = [](auto & lhs, auto rhs) { return lhs %= rhs; };
constexpr auto left_shift_equal = [](auto & lhs, auto rhs) { return lhs <<= rhs; };
constexpr auto right_shift_equal = [](auto & lhs, auto rhs) { return lhs >>= rhs; };
constexpr auto and_equal = [](auto & lhs, auto rhs) { return lhs &= rhs; };
constexpr auto or_equal = [](auto & lhs, auto rhs) { return lhs |= rhs; };
constexpr auto xor_equal = [](auto & lhs, auto rhs) { return lhs ^= rhs; };

constexpr bool check_compound_assignment(auto lhs, auto const rhs, auto expected, auto function) {
	auto const returned_correct = function(lhs, rhs) == expected;
	return lhs == expected and returned_correct;
}

struct adl : operators::compound_assignment {
	constexpr explicit adl(int value_):
		value(value_)
	{
	}

	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(adl)
private:
	int value;
};

static_assert(check_compound_assignment(adl(5), adl(3), adl(8), plus_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(2), minus_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(15), times_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(1), divides_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(2), modulo_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(40), left_shift_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(0), right_shift_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(1), and_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(7), or_equal));
static_assert(check_compound_assignment(adl(5), adl(3), adl(6), xor_equal));

namespace macro {

OPERATORS_IMPORT_COMPOUND_ASSIGNMENT;

struct implicit {
	constexpr explicit implicit(int value_):
		value(value_)
	{
	}

	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(implicit)
private:
	int value;
};

static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(8), plus_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(2), minus_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(15), times_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(1), divides_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(2), modulo_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(40), left_shift_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(0), right_shift_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(1), and_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(7), or_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(6), xor_equal));

} // namespace macro

static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(8), plus_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(2), minus_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(15), times_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(1), divides_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(2), modulo_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(40), left_shift_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(0), right_shift_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(1), and_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(7), or_equal));
static_assert(check_compound_assignment(macro::implicit(5), macro::implicit(3), macro::implicit(6), xor_equal));

namespace declarations {

using ::operators::operator+=;
using ::operators::operator-=;
using ::operators::operator*=;
using ::operators::operator/=;
using ::operators::operator%=;
using ::operators::operator<<=;
using ::operators::operator>>=;
using ::operators::operator&=;
using ::operators::operator|=;
using ::operators::operator^=;

struct implicit {
	constexpr explicit implicit(int value_):
		value(value_)
	{
	}

	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(implicit)
private:
	int value;
};

static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(8), plus_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(2), minus_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(15), times_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(1), divides_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(2), modulo_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(40), left_shift_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(0), right_shift_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(1), and_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(7), or_equal));
static_assert(check_compound_assignment(implicit(5), implicit(3), implicit(6), xor_equal));

} // namespace macro

static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(8), plus_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(2), minus_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(15), times_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(1), divides_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(2), modulo_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(40), left_shift_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(0), right_shift_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(1), and_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(7), or_equal));
static_assert(check_compound_assignment(declarations::implicit(5), declarations::implicit(3), declarations::implicit(6), xor_equal));

template<typename T>
concept has_plus_equal = requires(T value) { value += value; };

template<typename T>
concept has_minus_equal = requires(T value) { value -= value; };

template<typename T>
concept has_times_equal = requires(T value) { value *= value; };

template<typename T>
concept has_divides_equal = requires(T value) { value /= value; };

template<typename T>
concept has_modulo_equal = requires(T value) { value %= value; };

template<typename T>
concept has_left_shift_equal = requires(T value) { value <<= value; };

template<typename T>
concept has_right_shift_equal = requires(T value) { value >>= value; };

template<typename T>
concept has_and_equal = requires(T value) { value &= value; };

template<typename T>
concept has_or_equal = requires(T value) { value |= value; };

template<typename T>
concept has_xor_equal = requires(T value) { value ^= value; };

struct plus_only : operators::plus_equal {
	constexpr explicit plus_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(plus_only)

private:
	int value;
};

static_assert(has_plus_equal<plus_only>);
static_assert(!has_minus_equal<plus_only>);
static_assert(!has_times_equal<plus_only>);
static_assert(!has_divides_equal<plus_only>);
static_assert(!has_modulo_equal<plus_only>);
static_assert(!has_left_shift_equal<plus_only>);
static_assert(!has_right_shift_equal<plus_only>);
static_assert(!has_and_equal<plus_only>);
static_assert(!has_or_equal<plus_only>);
static_assert(!has_xor_equal<plus_only>);

struct minus_only : operators::minus_equal {
	constexpr explicit minus_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(minus_only)

private:
	int value;
};

static_assert(!has_plus_equal<minus_only>);
static_assert(has_minus_equal<minus_only>);
static_assert(!has_times_equal<minus_only>);
static_assert(!has_divides_equal<minus_only>);
static_assert(!has_modulo_equal<minus_only>);
static_assert(!has_left_shift_equal<minus_only>);
static_assert(!has_right_shift_equal<minus_only>);
static_assert(!has_and_equal<minus_only>);
static_assert(!has_or_equal<minus_only>);
static_assert(!has_xor_equal<minus_only>);

struct times_only : operators::times_equal {
	constexpr explicit times_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(times_only)

private:
	int value;
};

static_assert(!has_plus_equal<times_only>);
static_assert(!has_minus_equal<times_only>);
static_assert(has_times_equal<times_only>);
static_assert(!has_divides_equal<times_only>);
static_assert(!has_modulo_equal<times_only>);
static_assert(!has_left_shift_equal<times_only>);
static_assert(!has_right_shift_equal<times_only>);
static_assert(!has_and_equal<times_only>);
static_assert(!has_or_equal<times_only>);
static_assert(!has_xor_equal<times_only>);

struct divides_only : operators::divides_equal {
	constexpr explicit divides_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(divides_only)

private:
	int value;
};

static_assert(!has_plus_equal<divides_only>);
static_assert(!has_minus_equal<divides_only>);
static_assert(!has_times_equal<divides_only>);
static_assert(has_divides_equal<divides_only>);
static_assert(!has_modulo_equal<divides_only>);
static_assert(!has_left_shift_equal<divides_only>);
static_assert(!has_right_shift_equal<divides_only>);
static_assert(!has_and_equal<divides_only>);
static_assert(!has_or_equal<divides_only>);
static_assert(!has_xor_equal<divides_only>);

struct modulo_only : operators::modulo_equal {
	constexpr explicit modulo_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(modulo_only)

private:
	int value;
};

static_assert(!has_plus_equal<modulo_only>);
static_assert(!has_minus_equal<modulo_only>);
static_assert(!has_times_equal<modulo_only>);
static_assert(!has_divides_equal<modulo_only>);
static_assert(has_modulo_equal<modulo_only>);
static_assert(!has_left_shift_equal<modulo_only>);
static_assert(!has_right_shift_equal<modulo_only>);
static_assert(!has_and_equal<modulo_only>);
static_assert(!has_or_equal<modulo_only>);
static_assert(!has_xor_equal<modulo_only>);

struct left_shift_only : operators::left_shift_equal {
	constexpr explicit left_shift_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(left_shift_only)

private:
	int value;
};

static_assert(!has_plus_equal<left_shift_only>);
static_assert(!has_minus_equal<left_shift_only>);
static_assert(!has_times_equal<left_shift_only>);
static_assert(!has_divides_equal<left_shift_only>);
static_assert(!has_modulo_equal<left_shift_only>);
static_assert(has_left_shift_equal<left_shift_only>);
static_assert(!has_right_shift_equal<left_shift_only>);
static_assert(!has_and_equal<left_shift_only>);
static_assert(!has_or_equal<left_shift_only>);
static_assert(!has_xor_equal<left_shift_only>);

struct right_shift_only : operators::right_shift_equal {
	constexpr explicit right_shift_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(right_shift_only)

private:
	int value;
};

static_assert(!has_plus_equal<right_shift_only>);
static_assert(!has_minus_equal<right_shift_only>);
static_assert(!has_times_equal<right_shift_only>);
static_assert(!has_divides_equal<right_shift_only>);
static_assert(!has_modulo_equal<right_shift_only>);
static_assert(!has_left_shift_equal<right_shift_only>);
static_assert(has_right_shift_equal<right_shift_only>);
static_assert(!has_and_equal<right_shift_only>);
static_assert(!has_or_equal<right_shift_only>);
static_assert(!has_xor_equal<right_shift_only>);

struct and_only : operators::and_equal {
	constexpr explicit and_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(and_only)

private:
	int value;
};

static_assert(!has_plus_equal<and_only>);
static_assert(!has_minus_equal<and_only>);
static_assert(!has_times_equal<and_only>);
static_assert(!has_divides_equal<and_only>);
static_assert(!has_modulo_equal<and_only>);
static_assert(!has_left_shift_equal<and_only>);
static_assert(!has_right_shift_equal<and_only>);
static_assert(has_and_equal<and_only>);
static_assert(!has_or_equal<and_only>);
static_assert(!has_xor_equal<and_only>);

struct or_only : operators::or_equal {
	constexpr explicit or_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(or_only)

private:
	int value;
};

static_assert(!has_plus_equal<or_only>);
static_assert(!has_minus_equal<or_only>);
static_assert(!has_times_equal<or_only>);
static_assert(!has_divides_equal<or_only>);
static_assert(!has_modulo_equal<or_only>);
static_assert(!has_left_shift_equal<or_only>);
static_assert(!has_right_shift_equal<or_only>);
static_assert(!has_and_equal<or_only>);
static_assert(has_or_equal<or_only>);
static_assert(!has_xor_equal<or_only>);

struct xor_only : operators::xor_equal {
	constexpr explicit xor_only(int value_):
		value(value_)
	{
	}
	OPERATORS_ARITHMETIC_OPERATORS_FRIENDS(xor_only)

private:
	int value;
};

static_assert(!has_plus_equal<xor_only>);
static_assert(!has_minus_equal<xor_only>);
static_assert(!has_times_equal<xor_only>);
static_assert(!has_divides_equal<xor_only>);
static_assert(!has_modulo_equal<xor_only>);
static_assert(!has_left_shift_equal<xor_only>);
static_assert(!has_right_shift_equal<xor_only>);
static_assert(!has_and_equal<xor_only>);
static_assert(!has_or_equal<xor_only>);
static_assert(has_xor_equal<xor_only>);

} // namespace
