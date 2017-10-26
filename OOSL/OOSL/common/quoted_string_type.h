#pragma once

#ifndef OOSL_QUOTED_STRING_TYPE_H
#define OOSL_QUOTED_STRING_TYPE_H

namespace oosl{
	namespace common{
		enum class quoted_string_type{
			narrow,
			escaped_narrow,
			wide,
			escaped_wide,
		};
	}
}

#endif /* !OOSL_QUOTED_STRING_TYPE_H */
