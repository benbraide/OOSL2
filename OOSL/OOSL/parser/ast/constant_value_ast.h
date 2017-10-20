#pragma once

#ifndef OOSL_CONSTANT_VALUE_AST_H
#define OOSL_CONSTANT_VALUE_AST_H

#include "../../common/constant_value.h"

#include "ast.h"

OOSL_AST_BEGIN

OOSL_AST_DECLARE_SINGLE_WPOS(constant_value, oosl::common::constant_value)

OOSL_AST_END

OOSL_AST_ADAPT_SINGLE(constant_value)

#endif /* !OOSL_CONSTANT_VALUE_AST_H */
