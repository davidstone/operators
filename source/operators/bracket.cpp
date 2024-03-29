// Copyright David Stone 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

module;

#include <operators/bracket.hpp>

export module operators.bracket;

import std_module;

// Not proposed for standardization

namespace operators_impl {

template<typename Derived>
struct iterator_bracket {
private:
	constexpr auto self() const & -> Derived const & {
		return static_cast<Derived const &>(*this);
	}
	constexpr auto self() & -> Derived & {
		return static_cast<Derived &>(*this);
	}
public:
	OPERATORS_DETAIL_BRACKET_ITERATOR_DEFINITIONS_IMPL(self())
	friend auto operator<=>(iterator_bracket, iterator_bracket) = default;
};


template<typename Derived>
struct sequence_range_bracket {
private:
	constexpr auto self() const & -> Derived const & {
		return static_cast<Derived const &>(*this);
	}
	constexpr auto self() & -> Derived & {
		return static_cast<Derived &>(*this);
	}
public:
	OPERATORS_DETAIL_BRACKET_SEQUENCE_RANGE_DEFINITIONS_IMPL(self())
	friend auto operator<=>(sequence_range_bracket, sequence_range_bracket) = default;
};

} // namespace operators_impl

namespace operators {

export template<typename Derived>
using iterator_bracket = operators_impl::iterator_bracket<Derived>;

export template<typename Derived>
using sequence_range_bracket = operators_impl::sequence_range_bracket<Derived>;

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


struct macro_iterator {
	constexpr explicit macro_iterator(int value_):
		value(value_)
	{
	}

	constexpr auto operator*() {
		return value;
	}
	friend constexpr auto operator+(macro_iterator const lhs, int const rhs) {
		return macro_iterator(lhs.value + rhs);
	}

	OPERATORS_BRACKET_ITERATOR_DEFINITIONS

private:
	int value;
};

static_assert(as_const_ref(macro_iterator(5))[3] == 8);
static_assert(as_ref(macro_iterator(5))[3] == 8);
static_assert(as_ref_ref(macro_iterator(5))[3] == 8);
static_assert(macro_iterator(5)[3] == 8);


struct crtp_iterator : operators::iterator_bracket<crtp_iterator> {
	constexpr explicit crtp_iterator(int value_):
		value(value_)
	{
	}

	constexpr auto operator*() {
		return value;
	}
	friend constexpr auto operator+(crtp_iterator const lhs, int const rhs) {
		return crtp_iterator(lhs.value + rhs);
	}

private:
	int value;
};

static_assert(as_const_ref(crtp_iterator(5))[3] == 8);
static_assert(as_ref(crtp_iterator(5))[3] == 8);
static_assert(as_ref_ref(crtp_iterator(5))[3] == 8);
static_assert(crtp_iterator(5)[3] == 8);



struct macro_sequence_range {
	constexpr explicit macro_sequence_range(int value_):
		value(value_)
	{
	}

	friend constexpr auto begin(macro_sequence_range const & x) {
		return macro_iterator(x.value);
	}
	friend constexpr auto begin(macro_sequence_range & x) {
		return macro_iterator(x.value + 10);
	}
	friend constexpr auto begin(macro_sequence_range && x) {
		return macro_iterator(x.value + 20);
	}

	OPERATORS_BRACKET_SEQUENCE_RANGE_DEFINITIONS

private:
	int value;
};

static_assert(as_const_ref(macro_sequence_range(5))[3] == 8);
static_assert(as_ref(macro_sequence_range(5))[3] == 18);
static_assert(as_ref_ref(macro_sequence_range(5))[3] == 28);
static_assert(macro_sequence_range(5)[3] == 28);


struct crtp_sequence_range : operators::sequence_range_bracket<crtp_sequence_range> {
	constexpr explicit crtp_sequence_range(int value_):
		value(value_)
	{
	}

	friend constexpr auto begin(crtp_sequence_range const & x) {
		return macro_iterator(x.value);
	}
	friend constexpr auto begin(crtp_sequence_range & x) {
		return macro_iterator(x.value + 10);
	}
	friend constexpr auto begin(crtp_sequence_range && x) {
		return macro_iterator(x.value + 20);
	}

private:
	int value;
};

static_assert(as_const_ref(crtp_sequence_range(5))[3] == 8);
static_assert(as_ref(crtp_sequence_range(5))[3] == 18);
static_assert(as_ref_ref(crtp_sequence_range(5))[3] == 28);
static_assert(crtp_sequence_range(5)[3] == 28);



} // namespace
