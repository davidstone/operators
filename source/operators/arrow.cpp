// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/arrow.hpp>

export module operators.arrow;

import operators.arrow_impl.cast_self;

namespace operators {

export template<typename Derived>
struct arrow {
	OPERATORS_DETAIL_ARROW_DEFINITIONS(::operators::detail::cast_self<Derived>)
	friend auto operator<=>(arrow, arrow) = default;
};

export template<typename Derived>
struct arrow_proxy {
	OPERATORS_DETAIL_ARROW_PROXY_DEFINITIONS(::operators::detail::cast_self<Derived>)
	friend auto operator<=>(arrow_proxy, arrow_proxy) = default;
};

} // namespace operators

namespace {

constexpr auto const & as_const_ref(auto && value) {
	return value;
}
constexpr auto & as_ref(auto && value) {
	return static_cast<std::remove_reference_t<decltype(value)> &>(value);
}
constexpr auto && as_ref_ref(auto && value) {
	return value;
}

template<typename T>
T declval();

template<typename T>
concept has_operator_arrow = requires { declval<T>().operator->(); };

struct wrapper {
	int value;
};


struct macro_ref {
	constexpr explicit macro_ref(int value_):
		value{value_}
	{
	}

	constexpr auto const & operator*() const & {
		return value;
	}
	constexpr auto & operator*() & {
		value = wrapper{value.value + 10};
		return value;
	}
	constexpr auto && operator*() && {
		value = wrapper{value.value + 20};
		return std::move(value);
	}

	OPERATORS_ARROW_DEFINITIONS

private:
	wrapper value;
};

static_assert(has_operator_arrow<macro_ref const &>);

static_assert(as_const_ref(macro_ref(5))->value == 5);
static_assert(as_ref(macro_ref(5))->value == 15);
static_assert(as_ref_ref(macro_ref(5))->value == 25);
static_assert(has_operator_arrow<macro_ref &&>);
static_assert(has_operator_arrow<macro_ref>);


struct macro_ref_proxy {
	constexpr explicit macro_ref_proxy(int value_):
		value{value_}
	{
	}

	constexpr auto const & operator*() const & {
		return value;
	}
	constexpr auto & operator*() & {
		value = wrapper{value.value + 10};
		return value;
	}
	constexpr auto && operator*() && {
		value = wrapper{value.value + 20};
		return std::move(value);
	}

	OPERATORS_ARROW_PROXY_DEFINITIONS

private:
	wrapper value;
};

static_assert(as_const_ref(macro_ref_proxy(5))->value == 5);
static_assert(as_ref(macro_ref_proxy(5))->value == 15);
static_assert(as_ref_ref(macro_ref_proxy(5))->value == 25);
static_assert(macro_ref_proxy(5)->value == 25);


struct macro_value {
	constexpr auto operator*() const & {
		return wrapper{0};
	}
	constexpr auto operator*() & {
		return wrapper{0};
	}
	constexpr auto operator*() && {
		return wrapper{0};
	}

	OPERATORS_ARROW_DEFINITIONS
};

static_assert(!has_operator_arrow<macro_value const &>);
static_assert(!has_operator_arrow<macro_value &>);
static_assert(!has_operator_arrow<macro_value &&>);
static_assert(!has_operator_arrow<macro_value>);


struct macro_value_proxy {
	constexpr explicit macro_value_proxy(int value_):
		value{value_}
	{
	}

	constexpr auto operator*() const & {
		return value;
	}
	constexpr auto operator*() & {
		return wrapper{value.value + 10};
	}
	constexpr auto operator*() && {
		return wrapper{value.value + 20};
	}

	OPERATORS_ARROW_PROXY_DEFINITIONS

private:
	wrapper value;
};

static_assert(as_const_ref(macro_value_proxy(5))->value == 5);
static_assert(as_ref(macro_value_proxy(5))->value == 15);
static_assert(as_ref_ref(macro_value_proxy(5))->value == 25);
static_assert(macro_value_proxy(5)->value == 25);


struct crtp_ref : operators::arrow<crtp_ref> {
	constexpr explicit crtp_ref(int value_):
		value{value_}
	{
	}

	constexpr auto const & operator*() const & {
		return value;
	}
	constexpr auto & operator*() & {
		value = wrapper{value.value + 10};
		return value;
	}
	constexpr auto && operator*() && {
		value = wrapper{value.value + 20};
		return std::move(value);
	}

private:
	wrapper value;
};

static_assert(as_const_ref(crtp_ref(5))->value == 5);
static_assert(as_ref(crtp_ref(5))->value == 15);
static_assert(as_ref_ref(crtp_ref(5))->value == 25);
static_assert(crtp_ref(5)->value == 25);



struct crtp_ref_proxy : operators::arrow_proxy<crtp_ref_proxy> {
	constexpr explicit crtp_ref_proxy(int value_):
		value{value_}
	{
	}

	constexpr auto const & operator*() const & {
		return value;
	}
	constexpr auto & operator*() & {
		value = wrapper{value.value + 10};
		return value;
	}
	constexpr auto && operator*() && {
		value = wrapper{value.value + 20};
		return std::move(value);
	}

private:
	wrapper value;
};

static_assert(as_const_ref(crtp_ref_proxy(5))->value == 5);
static_assert(as_ref(crtp_ref_proxy(5))->value == 15);
static_assert(as_ref_ref(crtp_ref_proxy(5))->value == 25);
static_assert(crtp_ref_proxy(5)->value == 25);



struct crtp_value : operators::arrow<crtp_value> {
	constexpr explicit crtp_value(int value_):
		value{value_}
	{
	}

	constexpr auto operator*() const & {
		return value;
	}
	constexpr auto operator*() & {
		return wrapper{value.value + 10};
	}
	constexpr auto operator*() && {
		return wrapper{value.value + 20};
	}

private:
	wrapper value;
};

static_assert(!has_operator_arrow<crtp_value const &>);
static_assert(!has_operator_arrow<crtp_value &>);
static_assert(!has_operator_arrow<crtp_value &&>);
static_assert(!has_operator_arrow<crtp_value>);


struct crtp_value_proxy : operators::arrow_proxy<crtp_value_proxy> {
	constexpr explicit crtp_value_proxy(int value_):
		value{value_}
	{
	}

	constexpr auto operator*() const & {
		return value;
	}
	constexpr auto operator*() & {
		return wrapper{value.value + 10};
	}
	constexpr auto operator*() && {
		return wrapper{value.value + 20};
	}

private:
	wrapper value;
};

static_assert(as_const_ref(crtp_value_proxy(5))->value == 5);
static_assert(as_ref(crtp_value_proxy(5))->value == 15);
static_assert(as_ref_ref(crtp_value_proxy(5))->value == 25);
static_assert(crtp_value_proxy(5)->value == 25);

} // namespace
