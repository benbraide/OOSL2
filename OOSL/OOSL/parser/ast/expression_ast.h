#pragma once

#ifndef OOSL_EXPRESSION_AST_H
#define OOSL_EXPRESSION_AST_H

#include "constant_value_ast.h"
#include "literal_ast.h"
#include "general_ast.h"

#define OOSL_EXPRESSION_AST_DECLARE_CAST(name, type)				\
struct name{														\
	typedef type value_type;										\
	value_type value;												\
	boost::optional<oosl::common::numeric_literal_suffix> suffix;	\
};

#define OOSL_EXPRESSION_AST_ADAPT_CAST(name)						\
BOOST_FUSION_ADAPT_STRUCT(											\
	oosl::parser::ast::name,										\
	(oosl::parser::ast::name::value_type, value)					\
	(boost::optional<oosl::common::numeric_literal_suffix>, suffix)	\
)

OOSL_AST_BEGIN

struct constant_integral_expression;

struct range_expression{
	typedef x3::forward_ast<constant_integral_expression> value_type;
	value_type from;
	value_type to;
};

class expression;

OOSL_AST_DECLARE_SINGLE_WPOS(grouped_expression, x3::forward_ast<expression>)
OOSL_AST_DECLARE_SINGLE_WPOS(static_cast_expression, grouped_expression)
OOSL_AST_DECLARE_SINGLE_WPOS(reinterpret_cast_expression, grouped_expression)

OOSL_AST_END

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::range_expression,
	(oosl::parser::ast::range_expression::value_type, from)
	(oosl::parser::ast::range_expression::value_type, to)
)

#endif /* !OOSL_EXPRESSION_AST_H */
