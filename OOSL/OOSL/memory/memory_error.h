#pragma once

#ifndef OOSL_MEMORY_ERROR_H
#define OOSL_MEMORY_ERROR_H

namespace oosl{
	namespace memory{
		enum class error_code{
			nil,
			out_of_memory,
			invalid_address,
			protected_address,
		};
	}
}

#endif /* !OOSL_MEMORY_ERROR_H */
