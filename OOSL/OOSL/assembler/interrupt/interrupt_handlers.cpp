#include "interrupt_handlers.h"

oosl::assembler::interrupt::handlers::handlers(){
	map_[handler_id::sys_call] = std::make_shared<sys_call>();
}

void oosl::assembler::interrupt::handlers::handle(unsigned int id){
	auto handler = map_.find(static_cast<handler_id>(id));
	if (handler == map_.end())
		throw error::not_found;
	else//Handle interrupt
		handler->second->handle();
}
