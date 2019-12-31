/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "pipe.h"

void genericPipe::pushQueue(int val) {
	_queue.push(val);
}

int genericPipe::popQueue() {
	if(_queue.empty()) return 0; // Zero is a reserved instruction, means queue is empty
	int val = _queue.front();
	_queue.pop();
	return val;
}

std::vector<float> genericPipe::getVector() {
	return _vector;
}

void genericPipe::setVector(std::vector<float> vect) {
	_vector = vect; 
}

void genericPipe::releasePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	_lockable = true;
	lock.unlock();
}
	
bool genericPipe::acquirePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	if (!_lockable) { return _lockable; }
	_lockable = false;
	return true; 
}
