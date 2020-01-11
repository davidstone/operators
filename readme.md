# Overview

This is a library that implements much of the functionality discussed in [P1046: Automatically Generate More Operators](https://github.com/davidstone/isocpp/blob/master/generate-operators.md). The summary of what is enabled this library is:

* Generate `lhs += rhs` as `lhs = std::move(lhs) + rhs`, but evaluate `lhs` only once
* Generate `lhs -= rhs` as `lhs = std::move(lhs) - rhs`, but evaluate `lhs` only once
* Generate `lhs *= rhs` as `lhs = std::move(lhs) * rhs`, but evaluate `lhs` only once
* Generate `lhs /= rhs` as `lhs = std::move(lhs) / rhs`, but evaluate `lhs` only once
* Generate `lhs %= rhs` as `lhs = std::move(lhs) % rhs`, but evaluate `lhs` only once
* Generate `lhs &= rhs` as `lhs = std::move(lhs) & rhs`, but evaluate `lhs` only once
* Generate `lhs |= rhs` as `lhs = std::move(lhs) | rhs`, but evaluate `lhs` only once
* Generate `lhs ^= rhs` as `lhs = std::move(lhs) ^ rhs`, but evaluate `lhs` only once
* Generate `lhs <<= rhs` as `lhs = std::move(lhs) << rhs`, but evaluate `lhs` only once
* Generate `lhs >>= rhs` as `lhs = std::move(lhs) >> rhs`, but evaluate `lhs` only once
* Generate `++x` as `x += 1`
* Generate `--x` as `x -= 1`
* Generate `x++` as `++x` but return a copy of the original value
* Generate `x--` as `--x` but return a copy of the original value
* Generate `lhs->rhs` as `(*lhs).rhs`
* Generate `lhs->*rhs` as `(*lhs).*rhs`

There are also some extensions described at the end of this document that are not being proposed for standardization at this time.

There is a convenience header `operators/operators.hpp` that includes all other headers.

# Proposed for standardization

## compound assignment operators (`operator+=`, etc.)

The proposal currently suggests that the language provides all of these by default. However, another option is to standardize some subset of the following library features. A third option is something like `auto & operator+=(T &, U const &) = default;`.

Defined in header `operators/compound_assignment.hpp`.

To create a definition of `lhs @= rhs` in terms of `lhs = std::move(lhs) @ rhs`, there are several options:

1) For all types in a namespace, use any of the following in your namespace:
   * `using operators::operator+=;`
   * `using operators::operator-=;`
   * `using operators::operator*=;`
   * `using operators::operator/=;`
   * `using operators::operator%=;`
   * `using operators::operator<<=;`
   * `using operators::operator>>=;`
   * `using operators::operator&=;`
   * `using operators::operator|=;`
   * `using operators::operator^=;`
2) For all of the previous operators and all types in a namespace, type `OPERATORS_IMPORT_COMPOUND_ASSIGNMENT` in your namespace.
3) For a specific type, derive from any of the following under the desired access control:
   * `operators::plus_equal`
   * `operators::minus_equal`
   * `operators::times_equal`
   * `operators::divides_equal`
   * `operators::modulo_equal`
   * `operators::left_shift_equal`
   * `operators::right_shift_equal`
   * `operators::and_equal`
   * `operators::or_equal`
   * `operators::xor_equal`
4) For all of the previous operators and for a specific type, derive from `operators::compound_assignment` under the desired access control.

## `operator++` and `operator--`

Defined in header `operators/increment_decrement.hpp`.

### Prefix `operator++`

To create a definition of `++a` in terms of `a += 1`, there are two options:

1) For all types in a namespace, use `using operators::prefix::operator++;` in your namespace.
2) For a specific type, derive from `operators::prefix::increment` under the desired access control.

### Postfix `operator++`

To create a definition of `a++` in terms of `++a` (but return a copy of the original value for copyable types and return `void` for non-copyable types), there are two options:

1) For all types in a namespace, use `using operators::postfix::operator++;` in your namespace.
2) For a specific type, derive from `operators::postfix::increment` under the desired access control.

### Prefix and postfix `operator++`

To combine the previous two and define `++a` and `a++`, there are two options:

1) For all types in a namespace, use `using operators::operator++;` in your namespace.
2) For a specific type, derive from `operators::increment` under the desired access control.

### Prefix `operator--`

To create a definition of `--a` in terms of `a -= 1`, there are two options:

1) For all types in a namespace, use `using operators::prefix::operator--;` in your namespace.
2) For a specific type, derive from `operators::prefix::decrement` under the desired access control.

### Postfix `operator--`

To create a definition of `a--` in terms of `--a` (but return a copy of the original value for copyable types and return `void` for non-copyable types), there are two options:

1) For all types in a namespace, use `using operators::postfix::operator--;` in your namespace.
2) For a specific type, derive from `operators::postfix::decrement` under the desired access control.

### Prefix and postfix `operator--`

To combine the previous two and define `--a` and `a--`, there are two options:

1) For all types in a namespace, use `using operators::operator--;` in your namespace.
2) For a specific type, derive from `operators::decrement` under the desired access control.

## `operator->`

Defined in header `operators/arrow.hpp`.

There are currently two forms of `operator->` supported by the `operators` library.

To create a definition of `lhs->rhs` defined in terms of `*(lhs).rhs` that does not work for `operator*` that returns by value, there are two options:

1) For a specific type, type the macro `OPERATORS_ARROW_DEFINITIONS` in your class body under the desired access control.
2) For a specific type, derive from `operators::arrow<your_type_name>` under the desired access control.

To create a definition of `lhs->rhs` defined in terms of `*(lhs).rhs` that does work for `operator*` that returns by value, but risks creating a dangling reference with some common refactorings, and can cause a move construction to occur, there are two options:

1) For a specific type, type the macro `OPERATORS_ARROW_PROXY_DEFINITIONS` in your class body under the desired access control.
2) For a specific type, derive from `operators::arrow_proxy<your_type_name>` under the desired access control.

## `operator->*`

Defined in header `operators/arrow_star.hpp`.

To create a definition of `lhs->*rhs` defined in terms of `(*lhs).*rhs`, there are two options:

1) For all types in a namespace, use `using operators::operator->*;` in your namespace.
2) For a specific type, derive from `operators::arrow_star` under the desired access control.

# Extensions

## `operator[]`

Defined in header `operators/bracket.hpp`.

There are currently two forms of `operator[]` supported by the `operators` library.

To create a definition of `lhs[rhs]` defined in terms of `*(lhs + rhs)` (suitable for iterators), there are two options:

1) For a specific type, type the macro `OPERATORS_BRACKET_ITERATOR_DEFINITIONS` in your class body under the desired access control.
2) For a specific type, derive from `operators::bracket::iterator<your_type_name>` under the desired access control.

To create a definition of `lhs[rhs]` defined in terms of `*(begin(lhs) + rhs)` (suitable for range-access sequence ranges), there are two options:

1) For a specific type, type the macro `OPERATORS_BRACKET_SEQUENCE_RANGE_DEFINITIONS` in your class body under the desired access control.
2) For a specific type, derive from `operators::bracket::sequence_range<your_type_name>` under the desired access control.

## binary `operator-`

Defined in header `operators/binary_minus.hpp`.

To create a definition of `lhs - rhs` in terms of `lhs + -rhs`, there are two options:

1) For all types in a namespace, use `using operators::binary::operator-;` in your namespace.
2) For a specific type, derive from `operators::binary::minus` under the desired access control.

Note: do not combine this with unary `operator-`. This will create a (diagnosed at compile time) circular dependency.

## unary `operator-`

Defined in header `operators/unary_minus.hpp`.

To create a definition of `-a` in terms of `0 - a`, there are two options:

1) For all types in a namespace, use `using operators::unary::operator-;` in your namespace.
2) For a specific type, derive from `operators::unary::minus` under the desired access control.

Note: do not combine this with binary `operator-`. This will create a (diagnosed at compile time) circular dependency.

## unary `operator+`

Defined in header `operators/unary_plus.hpp`.

To create a definition of `+a` as returning a copy of `a`, there are two options:

1) For all types in a namespace, use `using operators::unary::operator+;` in your namespace.
2) For a specific type, derive from `operators::unary::plus` under the desired access control.
