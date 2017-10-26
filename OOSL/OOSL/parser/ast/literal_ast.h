#pragma once

#ifndef OOSL_LITERAL_AST_H
#define OOSL_LITERAL_AST_H

#include "../../common/numeric_literal_suffix.h"
#include "../../common/quoted_string_type.h"

#include "../parser_utils.h"

#define OOSL_NUMERIC_LITERAL_AST_DECLARE(name, type)				\
struct name : x3::position_tagged{									\
	typedef type value_type;										\
	value_type value;												\
	boost::optional<oosl::common::numeric_literal_suffix> suffix;	\
};

#define OOSL_NUMERIC_LITERAL_AST_ADAPT(name)						\
BOOST_FUSION_ADAPT_STRUCT(											\
	oosl::parser::ast::name,										\
	(oosl::parser::ast::name::value_type, value)					\
	(boost::optional<oosl::common::numeric_literal_suffix>, suffix)	\
)

OOSL_AST_BEGIN

OOSL_NUMERIC_LITERAL_AST_DECLARE(int8_literal, __int8)
OOSL_NUMERIC_LITERAL_AST_DECLARE(int16_literal, __int16)
OOSL_NUMERIC_LITERAL_AST_DECLARE(int32_literal, __int32)
OOSL_NUMERIC_LITERAL_AST_DECLARE(int64_literal, __int64)

OOSL_NUMERIC_LITERAL_AST_DECLARE(float_literal, float)
OOSL_NUMERIC_LITERAL_AST_DECLARE(double_literal, double)
OOSL_NUMERIC_LITERAL_AST_DECLARE(long_double_literal, long double)

OOSL_AST_DECLARE_SINGLE_VARIANT(integral_literal, int8_literal, int16_literal, int32_literal, int64_literal)
OOSL_AST_DECLARE_SINGLE_VARIANT(real_literal, float_literal, double_literal, long_double_literal)
OOSL_AST_DECLARE_SINGLE_VARIANT(numeric_literal, integral_literal, real_literal)

struct string_literal{
	oosl::common::quoted_string_type type;
	std::vector<char> value;
};

OOSL_AST_DECLARE_SINGLE_VARIANT(literal_, numeric_literal, string_literal)

OOSL_AST_END

OOSL_NUMERIC_LITERAL_AST_ADAPT(int8_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(int16_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(int32_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(int64_literal)

OOSL_NUMERIC_LITERAL_AST_ADAPT(float_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(double_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(long_double_literal)

OOSL_AST_ADAPT_SINGLE(integral_literal)
OOSL_AST_ADAPT_SINGLE(real_literal)
OOSL_AST_ADAPT_SINGLE(numeric_literal)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::string_literal,
	(oosl::common::quoted_string_type, type)
	(std::vector<char>, value)
)

OOSL_AST_ADAPT_SINGLE(literal_)

#endif /* !OOSL_LITERAL_AST_H */
