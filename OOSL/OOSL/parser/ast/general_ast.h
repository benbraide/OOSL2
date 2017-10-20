#pragma once

#ifndef OOSL_GENERAL_AST_H
#define OOSL_GENERAL_AST_H

#include "../../common/keyword_type.h"

#include "ast.h"

OOSL_AST_BEGIN

OOSL_AST_DECLARE_SINGLE_WPOS(keyword, oosl::common::keyword_type)

OOSL_AST_DECLARE_SINGLE_WPOS(identifier, std::string)

struct expression;

OOSL_AST_DECLARE_SINGLE_WPOS(placeholder, x3::forward_ast<expression>)

OOSL_AST_DECLARE_SINGLE_WPOS(absolute_scoped, std::string)

struct relative_scoped_right : x3::position_tagged{
	typedef boost::variant<identifier, x3::forward_ast<relative_scoped_right>> right_value_type;
	identifier left;
	right_value_type right;
};

struct relative_scoped{
	typedef boost::variant<identifier, absolute_scoped> left_value_type;
	typedef boost::variant<identifier, relative_scoped_right> right_value_type;
	left_value_type left;
	right_value_type right;
};

OOSL_AST_DECLARE_SINGLE_VARIANT(scoped, absolute_scoped, relative_scoped)

OOSL_AST_DECLARE_SINGLE_VARIANT(identifier_compatible, identifier, scoped)

struct expression_list;

struct call : x3::position_tagged{
	typedef x3::forward_ast<expression_list> args_type;
	unsigned int index;
	args_type args;
};

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(keyword)

OOSL_AST_ADAPT_SINGLE(identifier)

OOSL_AST_ADAPT_SINGLE(placeholder)

OOSL_AST_ADAPT_SINGLE(absolute_scoped)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::relative_scoped_right,
	(oosl::parser::ast::identifier, left)
	(oosl::parser::ast::relative_scoped_right::right_value_type, right)
)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::relative_scoped,
	(oosl::parser::ast::relative_scoped::left_value_type, left)
	(oosl::parser::ast::relative_scoped::right_value_type, right)
)

OOSL_AST_ADAPT_SINGLE(scoped)

OOSL_AST_ADAPT_SINGLE(identifier_compatible)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::call,
	(unsigned int, index)
	(oosl::parser::ast::call::args_type, args)
)

#endif /* !OOSL_GENERAL_AST_H */
