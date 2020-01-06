/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "GenericPipe.h"

void GenericPipe::pushQueue(void* val) {
	_queue.push(val);
}

void* GenericPipe::popQueue() {
	if(_queue.empty()) return nullptr; // no instruction 
	void* val = _queue.front();
	_queue.pop();
	return val;
}

std::vector<float> GenericPipe::getVector() {
	return _vector;
}

void GenericPipe::setVector(std::vector<float> vect) {
	_vector = vect; 
}

void GenericPipe::releasePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	_lockable = true;
	lock.unlock();
	cv.notify_one();
}
	
bool GenericPipe::acquirePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	if (!_lockable) { return _lockable; }
	_lockable = false;
	return true;
}

void GenericPipe::blockingAcquirePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	if (_lockable) { _lockable = false; return; }
	cv.wait(lock);
}
