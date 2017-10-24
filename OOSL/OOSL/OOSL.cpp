#include "memory/memory_collection.h"
#include "memory/memory_register.h"

#include "parser/ast/literal_ast.h"
#include "parser/ast/constant_value_ast.h"

#include "parser/assembler_parser.h"

int main(){
	oosl::parser::ast::asm_instruction_set op;
	std::string gram = "section .text mov eax, ebi push rip mov [eax + 4], rax";

	auto r = boost::spirit::x3::phrase_parse(gram.data(), gram.data() + gram.size(), oosl::parser::assembler::asm_instruction_set, oosl::parser::assembler::asm_skip, op);
	if (r){
		for (auto &ins : op.value)
			oosl::parser::ast::asm_traverser::get(ins)->create_or_add_to_section();

		oosl::assembler::vm::bundle();
		//oosl::assembler::vm::execute();
	}

	return 0;
}
