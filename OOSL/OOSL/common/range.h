#pragma once

#ifndef OOSL_RANGE_H
#define OOSL_RANGE_H

namespace oosl{
	namespace common{
		template <class value_type>
		class range{
		public:
			typedef value_type value_type;

			range() = default;

			range(value_type from, value_type to)
				: from_(from), to_(to){}

			bool operator <(const range &rhs) const{
				return ((from_ == rhs.from_) ? (to_ < rhs.to_) : (from_ < rhs.from_));
			}

			bool operator <=(const range &rhs) const{
				return (*this < rhs || *this == rhs);
			}

			bool operator ==(const range &rhs) const{
				return (from_ == rhs.from_ && to_ == rhs.to_);
			}

			bool operator !=(const range &rhs) const{
				return (*this == rhs);
			}

			bool operator >=(const range &rhs) const{
				return !(*this < rhs);
			}

			bool operator >(const range &rhs) const{
				return !(*this < rhs || *this == rhs);
			}

			bool contains(const range &target) const{
				return contains(target.from_, target.to_);
			}

			bool contains(value_type from, value_type to) const{
				return (contains(from) | contains(to));
			}

			bool contains(value_type value) const{
				return (from_ <= value && value <= to_);
			}

			value_type from() const{
				return from_;
			}

			value_type to() const{
				return to_;
			}

		private:
			value_type from_;
			value_type to_;
		};
	}
}

#endif /* !OOSL_RANGE_H */
