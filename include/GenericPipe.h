/* Krishna Mani
 * Pipe.h
 */
#ifndef GENERICPIPE_H
#define GENERICPIPE_H

#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>

class GenericPipe {
	std::mutex _mutex;
	
	std::queue<int> _queue; // Intended use is to store an instruction queue to talk to modules
	std::vector<float> _vector;	// For use in motor setpoint control, sensor values, etc.
	
	public:
	
	bool _lockable = true; // Manages pipe state, readable/writable or in use
	std::condition_variable cv; // For blockingAcquirePipe()
	void pushQueue(int);
	int popQueue();

	std::vector<float> getVector();
	void setVector(std::vector<float>);
	
	void* object = nullptr; // Can be used for anything

	void releasePipe();
	bool acquirePipe();
	void blockingAcquirePipe();
};

#endif