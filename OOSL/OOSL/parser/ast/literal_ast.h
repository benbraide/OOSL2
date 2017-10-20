#pragma once

#ifndef OOSL_LITERAL_AST_H
#define OOSL_LITERAL_AST_H

#include "../../common/numeric_literal_suffix.h"

#include "ast.h"

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
OOSL_NUMERIC_LITERAL_AST_DECLARE(uint8_literal, unsigned __int8)

OOSL_NUMERIC_LITERAL_AST_DECLARE(int16_literal, __int16)
OOSL_NUMERIC_LITERAL_AST_DECLARE(uint16_literal, unsigned __int16)

OOSL_NUMERIC_LITERAL_AST_DECLARE(int32_literal, __int32)
OOSL_NUMERIC_LITERAL_AST_DECLARE(uint32_literal, unsigned __int32)

OOSL_NUMERIC_LITERAL_AST_DECLARE(int64_literal, __int64)
OOSL_NUMERIC_LITERAL_AST_DECLARE(uint64_literal, unsigned __int64)

OOSL_NUMERIC_LITERAL_AST_DECLARE(float32_literal, float)
OOSL_NUMERIC_LITERAL_AST_DECLARE(float64_literal, double)
OOSL_NUMERIC_LITERAL_AST_DECLARE(float128_literal, long double)

OOSL_AST_DECLARE_SINGLE_VARIANT(signed_integral_literal, int8_literal, int16_literal, int32_literal, int64_literal)
OOSL_AST_DECLARE_SINGLE_VARIANT(unsigned_integral_literal, uint8_literal, uint16_literal, uint32_literal, uint64_literal)

OOSL_AST_DECLARE_SINGLE_VARIANT(integral_literal, signed_integral_literal, unsigned_integral_literal)
OOSL_AST_DECLARE_SINGLE_VARIANT(real_literal, float32_literal, float64_literal, float128_literal)
OOSL_AST_DECLARE_SINGLE_VARIANT(numeric_literal, integral_literal, real_literal)

OOSL_AST_DECLARE_SINGLE_WPOS(char_literal, char)
OOSL_AST_DECLARE_SINGLE_WPOS(wchar_literal, wchar_t)

OOSL_AST_DECLARE_SINGLE_WPOS(string_literal, std::string)
OOSL_AST_DECLARE_SINGLE_WPOS(wstring_literal, std::wstring)

OOSL_AST_DECLARE_SINGLE_VARIANT(literal_, numeric_literal, char_literal, wchar_literal, string_literal, wstring_literal)

struct expression;

OOSL_AST_DECLARE_SINGLE_WPOS(raw_literal, x3::forward_ast<expression>)

OOSL_AST_END

OOSL_NUMERIC_LITERAL_AST_ADAPT(int8_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(uint8_literal)

OOSL_NUMERIC_LITERAL_AST_ADAPT(int16_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(uint16_literal)

OOSL_NUMERIC_LITERAL_AST_ADAPT(int32_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(uint32_literal)

OOSL_NUMERIC_LITERAL_AST_ADAPT(int64_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(uint64_literal)

OOSL_NUMERIC_LITERAL_AST_ADAPT(float32_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(float64_literal)
OOSL_NUMERIC_LITERAL_AST_ADAPT(float128_literal)

OOSL_AST_ADAPT_SINGLE(signed_integral_literal)
OOSL_AST_ADAPT_SINGLE(unsigned_integral_literal)

OOSL_AST_ADAPT_SINGLE(integral_literal)
OOSL_AST_ADAPT_SINGLE(real_literal)
OOSL_AST_ADAPT_SINGLE(numeric_literal)

OOSL_AST_ADAPT_SINGLE(char_literal)
OOSL_AST_ADAPT_SINGLE(wchar_literal)

OOSL_AST_ADAPT_SINGLE(string_literal)
OOSL_AST_ADAPT_SINGLE(wstring_literal)

OOSL_AST_ADAPT_SINGLE(raw_literal)
OOSL_AST_ADAPT_SINGLE(literal_)

#endif /* !OOSL_LITERAL_AST_H */
