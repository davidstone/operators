// Copyright David Stone 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef OPERATORS_COMPOUND_ASSIGNMENT_HPP
#define OPERATORS_COMPOUND_ASSIGNMENT_HPP

import operators.compound_assignment;

#define OPERATORS_IMPORT_COMPOUND_ASSIGNMENT(...) \
	__VA_ARGS__ using ::operators::operator+=; \
	__VA_ARGS__ using ::operators::operator-=; \
	__VA_ARGS__ using ::operators::operator*=; \
	__VA_ARGS__ using ::operators::operator/=; \
	__VA_ARGS__ using ::operators::operator%=; \
	__VA_ARGS__ using ::operators::operator<<=; \
	__VA_ARGS__ using ::operators::operator>>=; \
	__VA_ARGS__ using ::operators::operator&=; \
	__VA_ARGS__ using ::operators::operator|=; \
	__VA_ARGS__ using ::operators::operator^=;

#endif // OPERATORS_COMPOUND_ASSIGNMENT_HPP