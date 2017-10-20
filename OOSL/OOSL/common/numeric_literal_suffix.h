#pragma once

#ifndef OOSL_NUMERIC_LITERAL_SUFFIX_H
#define OOSL_NUMERIC_LITERAL_SUFFIX_H

namespace oosl{
	namespace common{
		enum class numeric_literal_suffix{
			int8,
			uint8,
			int16,
			uint16,
			int32,
			uint32,
			int64,
			uint64,
			float32,
			float64,
			float128,
		};
	}
}

#endif /* !OOSL_NUMERIC_LITERAL_SUFFIX_H */
