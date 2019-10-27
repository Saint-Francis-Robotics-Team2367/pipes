/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */

#include "pipe.h"

// Templates make it easier to tailor the pipe to the specific module, but add extra complexity 

void genericPipe::pushQueue(int val) {
	std::unique_lock<std::mutex> lock(_mutex);
	_queue.push(val);
}

int genericPipe::popQueue() {
	std::unique_lock<std::mutex> lock(_mutex);
	int val = _queue.front();
	_queue.pop();
	return val;
}

std::vector<float> genericPipe::getVector() {
	std::unique_lock<std::mutex> lock(_mutex);
	return _vector;
}

void genericPipe::setVector(std::vector<float> vect) {
	std::unique_lock<std::mutex> lock(_mutex);
	_vector = vect; 
}

void genericPipe::releasePipe() {
	std::unique_lock<std::mutex> lock(_mutex);
	_state = true;
	lock.unlock();
	cv.notify_one();
}
	
void genericPipe::acquirePipe() { // returns false if pipe is in use, true if pipe has been acquired
	std::unique_lock<std::mutex> lock(_mutex);
	if (_state) { _state = false; return; }
	cv.wait(lock);
}
