#pragma once

#ifndef OOSL_TYPE_AST_H
#define OOSL_TYPE_AST_H

#include "../../common/type_id.h"
#include "../../common/type_specifier.h"

#include "ast.h"

OOSL_AST_BEGIN

OOSL_AST_DECLARE_SINGLE_WPOS(type_specifier, oosl::common::type_specifier)
OOSL_AST_DECLARE_SINGLE_WPOS(primitive_type, oosl::common::type_id)
OOSL_AST_DECLARE_SINGLE_WPOS(auto_type, oosl::common::type_id)
OOSL_AST_DECLARE_SINGLE_WPOS(void_type, oosl::common::type_id)

struct grouped_expression;

OOSL_AST_DECLARE_SINGLE_WPOS(decltype_, x3::forward_ast<grouped_expression>)

struct simple_type;

OOSL_AST_DECLARE_SINGLE_VARIANT(pointer_type, x3::forward_ast<simple_type>, x3::forward_ast<pointer_type>)
OOSL_AST_DECLARE_SINGLE_VARIANT(ref_type, x3::forward_ast<simple_type>, pointer_type)
OOSL_AST_DECLARE_SINGLE_VARIANT(rval_ref_type, x3::forward_ast<simple_type>, pointer_type)

OOSL_AST_DECLARE_SINGLE_VARIANT(auto_pointer_type, auto_type, x3::forward_ast<auto_pointer_type>)
OOSL_AST_DECLARE_SINGLE_VARIANT(auto_ref_type, auto_type, auto_pointer_type)
OOSL_AST_DECLARE_SINGLE_VARIANT(auto_rval_ref_type, auto_type, auto_pointer_type)

OOSL_AST_DECLARE_SINGLE_VARIANT(void_pointer_type, void_type, x3::forward_ast<void_pointer_type>)
OOSL_AST_DECLARE_SINGLE_VARIANT(void_ref_type, void_type, void_pointer_type)
OOSL_AST_DECLARE_SINGLE_VARIANT(void_rval_ref_type, void_type, void_pointer_type)

OOSL_AST_DECLARE_SINGLE_VARIANT(
	non_void_type,
	auto_pointer_type,
	auto_ref_type,
	void_pointer_type,
	void_ref_type,
	pointer_type,
	ref_type,
	auto_type,
	void_type,
	x3::forward_ast<simple_type>
)

OOSL_AST_DECLARE_SINGLE_VARIANT(
	common_type,
	auto_pointer_type,
	auto_ref_type,
	void_pointer_type,
	void_ref_type,
	pointer_type,
	ref_type,
	x3::forward_ast<simple_type>
)

OOSL_AST_DECLARE_SINGLE_VARIANT(
	return_type,
	auto_pointer_type,
	auto_ref_type,
	void_pointer_type,
	void_ref_type,
	pointer_type,
	ref_type,
	auto_type,
	void_type,
	x3::forward_ast<simple_type>
)

OOSL_AST_DECLARE_SINGLE_VARIANT(
	parameter_type,
	auto_pointer_type,
	auto_ref_type,
	auto_rval_ref_type,
	void_pointer_type,
	void_ref_type,
	void_rval_ref_type,
	pointer_type,
	ref_type,
	rval_ref_type,
	auto_type,
	x3::forward_ast<simple_type>
)

OOSL_AST_DECLARE_SINGLE_VARIANT(
	variadic_type,
	parameter_type,
)

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(type_specifier)
OOSL_AST_ADAPT_SINGLE(primitive_type)
OOSL_AST_ADAPT_SINGLE(auto_type)
OOSL_AST_ADAPT_SINGLE(void_type)

OOSL_AST_ADAPT_SINGLE(decltype_)

OOSL_AST_ADAPT_SINGLE(pointer_type)
OOSL_AST_ADAPT_SINGLE(ref_type)
OOSL_AST_ADAPT_SINGLE(rval_ref_type)

OOSL_AST_ADAPT_SINGLE(auto_pointer_type)
OOSL_AST_ADAPT_SINGLE(auto_ref_type)
OOSL_AST_ADAPT_SINGLE(auto_rval_ref_type)

OOSL_AST_ADAPT_SINGLE(void_pointer_type)
OOSL_AST_ADAPT_SINGLE(void_ref_type)
OOSL_AST_ADAPT_SINGLE(void_rval_ref_type)

OOSL_AST_ADAPT_SINGLE(return_type)
OOSL_AST_ADAPT_SINGLE(parameter_type)
OOSL_AST_ADAPT_SINGLE(variadic_type)

#endif /* !OOSL_TYPE_AST_H */
