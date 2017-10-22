#pragma once

#ifndef OOSL_MEMORY_STACK_H
#define OOSL_MEMORY_STACK_H

#include <memory>

namespace oosl{
	namespace memory{
		enum class stack_error{
			nil,
			overflow,
			underflow,
		};

		class stack{
		public:
			typedef unsigned __int64 uint64_type;
			typedef std::size_t size_type;

			explicit stack(size_type data_size = 0u);

			void create(size_type data_size = 0u);

			char *begin() const;

			template <typename value_type>
			char *push(char *current, value_type value){
				current += sizeof(value_type);
				if (current > max_)//Overflow
					throw stack_error::overflow;

				memcpy(current, &value, sizeof(value_type));
				return current;
			}

			template <typename value_type>
			value_type pop(char *&current){
				auto value = value_type();
				memcpy(&value, current, sizeof(value_type));

				current -= sizeof(value_type);
				if (current < data_)//Underflow
					throw stack_error::underflow;

				return value;
			}

		private:
			uint64_type address_;
			char *data_;
			char *max_;
		};
	}
}

#endif /* !OOSL_MEMORY_STACK_H */
