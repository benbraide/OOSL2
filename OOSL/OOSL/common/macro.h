#pragma once

#ifndef OOSL_MACRO_H
#define OOSL_MACRO_H

#define OOSL_MAKE_OPERATORS_(x, t)\
	inline constexpr x operator |(x l, x r){\
		return (x)((t)(l) | (t)(r));\
	}\
\
	inline constexpr x operator &(x l, x r){\
		return (x)((t)(l) & (t)(r));\
	}\
\
	inline constexpr x operator ~(x r){\
		return (x)(~(t)(r));\
	}\
\
	inline x operator |=(x &l, x r){\
		return (l = (x)((t)(l) | (t)(r)));\
	}\
\
	inline x operator &=(x &l, x r){\
		return (l = (x)((t)(l) & (t)(r)));\
	}\
\
	inline x operator <<(x &l, t r){\
		return (x)((t)(l) << (r));\
	}\
\
	inline x operator >>(x &l, t r){\
		return (x)((t)(l) >> (r));\
	}

#define OOSL_MAKE_OPERATORS(x) OOSL_MAKE_OPERATORS_(x, unsigned int)

#define OOSL_MAKE_OPERATORS_LL(x) OOSL_MAKE_OPERATORS_(x, unsigned long long)

#define OOSL_SET(source, target) ((source) |= (target))
#define OOSL_REMOVE(source, target) ((source) &= ~(target))
#define OOSL_FILTER(source, target) ((source) &= (target))

#define OOSL_SET_V(source, target) ((source) | (target))
#define OOSL_REMOVE_V(source, target) ((source) & ~(target))
#define OOSL_FILTER_V(source, target) ((source) & (target))

#define OOSL_IS(source, target) (((source) & (target)) == (target))
#define OOSL_IS_ANY(source, target) (((source) & (target)) != static_cast<decltype(target)>(0))

#endif /* !OOSL_MACRO_H */
