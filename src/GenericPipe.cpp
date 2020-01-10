/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "GenericPipe.h"

Message::Message(std::string _str, float _val) : str(_str), val(_val) {}

void GenericPipe::pushQueue(Message* msg) {
	_mutex.lock();
	_stack.push(msg);	
	_mutex.unlock();
}

void* GenericPipe::popQueue() {
	Message* msg = nullptr;

	_mutex.lock();
	if(!_stack.empty()) { msg = _stack.top(); } // pop doesn't return the value
	_stack.pop();
	_mutex.unlock();
	
	// Make deep copy
	static Message ret(msg->str, msg->val);

	delete msg; // If this is too slow, remove and use global delete

	return &ret;
}