#pragma once

#ifndef OOSL_INSTRUCTION_ID_H
#define OOSL_INSTRUCTION_ID_H

namespace oosl{
	namespace assembler{
		namespace instruction{
			enum class id{
				nop,
				push,
				pop,
				mov,
				int_,
				call,
				ret,
				jmp,
				jz,
				jnz,
				je,
				jne,
				jl,
				jnl,
				jle,
				jnle,
				jg,
				jng,
				jge,
				jnge,
				loop,
				inc,
				dec,
				add,
				sub,
				mult,
				div,
				mod,
				and_,
				xor_,
				or_,
				lshift,
				rshift,
				test,
				not,
				cmp,
			};
		}
	}
}

#endif /* !OOSL_INSTRUCTION_ID_H */
