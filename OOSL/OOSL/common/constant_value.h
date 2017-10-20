#pragma once

#ifndef OOSL_CONSTANT_VALUE_H
#define OOSL_CONSTANT_VALUE_H

namespace oosl{
	namespace common{
		enum class constant_value{
			nil,
			false_,
			true_,
			indeterminate,
			nullptr_,
			nan_,
			undefined,
		};
	}
}

#endif /* !OOSL_CONSTANT_VALUE_H */
