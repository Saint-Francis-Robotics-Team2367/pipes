/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "GenericPipe.h"

void GenericPipe::pushQueue(Message* msg) {
	_mutex.lock();
	_deque.push_back(msg);	
	_mutex.unlock();
}

Message* GenericPipe::popQueue() {
	_mutex.lock();
	static Message ret;

	if (!_deque.empty()) {
		Message* msg = _deque.front();

		_deque.pop_front();
		ret.val = msg->val;
		ret.str = msg->str;

		_mutex.unlock();	

		delete msg; // This may be too slow
		return &ret;
	}

	_mutex.unlock();
	return nullptr; 
}
