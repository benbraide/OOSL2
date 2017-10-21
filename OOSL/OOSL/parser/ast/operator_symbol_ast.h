#pragma once

#ifndef OOSL_OPERATOR_SYMBOL_AST_H
#define OOSL_OPERATOR_SYMBOL_AST_H

#include "../../common/operator_id.h"

#include "ast.h"

OOSL_AST_BEGIN

OOSL_AST_DECLARE_SINGLE_WPOS(member_access_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(factor_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(addition_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(shift_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(relation_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(equality_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(bitwise_and_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(bitwise_xor_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(bitwise_or_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(logical_and_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(logical_or_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(assignment_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(ternary_operator_symbol, oosl::common::operator_id)
OOSL_AST_DECLARE_SINGLE_WPOS(known_operator_symbol, oosl::common::operator_id)

struct unknown_operator_symbol : x3::position_tagged{
	oosl::common::operator_id id;
	std::string value;
};

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(member_access_operator_symbol)
OOSL_AST_ADAPT_SINGLE(member_access_operator_symbol)
OOSL_AST_ADAPT_SINGLE(factor_operator_symbol)
OOSL_AST_ADAPT_SINGLE(addition_operator_symbol)
OOSL_AST_ADAPT_SINGLE(shift_operator_symbol)
OOSL_AST_ADAPT_SINGLE(relation_operator_symbol)
OOSL_AST_ADAPT_SINGLE(equality_operator_symbol)
OOSL_AST_ADAPT_SINGLE(bitwise_and_operator_symbol)
OOSL_AST_ADAPT_SINGLE(bitwise_xor_operator_symbol)
OOSL_AST_ADAPT_SINGLE(bitwise_or_operator_symbol)
OOSL_AST_ADAPT_SINGLE(logical_and_operator_symbol)
OOSL_AST_ADAPT_SINGLE(logical_or_operator_symbol)
OOSL_AST_ADAPT_SINGLE(assignment_operator_symbol)
OOSL_AST_ADAPT_SINGLE(ternary_operator_symbol)
OOSL_AST_ADAPT_SINGLE(known_operator_symbol)

BOOST_FUSION_ADAPT_STRUCT(
	oosl::parser::ast::unknown_operator_symbol,
	(oosl::common::operator_id, id)
	(std::string, value)
)

#endif /* !OOSL_OPERATOR_SYMBOL_AST_H */
