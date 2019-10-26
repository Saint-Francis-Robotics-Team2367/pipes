/* Krishna Mani
 * Pipe.h
 */
#ifndef PIPE_H
#define PIPE_H

#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>

class genericPipe {
	std::mutex _mutex;
	
	std::queue<int> _queue; // Intended use is to store an instruction queue to talk to modules
	std::vector<float> _vector;	// For use in motor setpoint control, sensor values, etc.
	
	public:
	
	bool _state = true; // Manages pipe state, readable/writable or in use
	std::condition_variable cv; // Makes the thread sleep if the pipe is in use

	void pushQueue(int);
	int popQueue();

	std::vector<float> getVector();
	void setVector(std::vector<float>);

	void releasePipe();
	void acquirePipe();
};

#endif
