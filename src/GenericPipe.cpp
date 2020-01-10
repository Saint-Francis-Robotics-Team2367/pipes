/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "GenericPipe.h"

void GenericPipe::pushQueue(Message* msg) {
	_mutex.lock();
	_stack.push(msg);	
	_mutex.unlock();
}

void* GenericPipe::popQueue() {
	Message* msg = nullptr;
	static Message ret;

	_mutex.lock();
	if(!_stack.empty()) { msg = _stack.top(); } // pop doesn't return the value
	_stack.pop();
	_mutex.unlock();
	
	// Make deep copy
	ret.str = msg->str;
	ret.val = msg->val;
	delete msg; // If this is too slow, remove and use global delete

	return &ret;
}
