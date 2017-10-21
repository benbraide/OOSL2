#pragma once

#ifndef OOSL_WRITER_BASE_H
#define OOSL_WRITER_BASE_H

#include <string>

namespace oosl{
	namespace common{
		class writer_base{
		public:
			virtual ~writer_base() = default;

			virtual writer_base &begin() = 0;

			virtual writer_base &end() = 0;

			virtual writer_base &write(const std::string &value){
				return write(value.c_str());
			}

			virtual writer_base &write(const char *value) = 0;

			virtual writer_base &write(const std::wstring &value){
				return write(value.c_str());
			}

			virtual writer_base &write(const wchar_t *value) = 0;
		};
	}
}

#endif /* !OOSL_WRITER_BASE_H */
