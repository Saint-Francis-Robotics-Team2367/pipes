/* Krishna Mani 2019
 * Pipes provide a way to communicate between threads safely and with minimal overhead
 */
#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>
// Templates make it easier to tailor the pipe to the specific module, but add extra complexity TODO
template <typename Q, typename V>
class genericPipe {
	std::mutex _mutex;
	
	std::queue<Q> _queue; // Intended use is to store an instruction queue to talk to modules
	std::vector<V> _vector;	// For use in motor setpoint control, sensor values, etc.
	
	public:
	
	bool _state = true; // Manages pipe state, readable/writable or in use
	std::condition_variable cv; // Makes the thread sleep if the pipe is in use

	void pushQueue(Q val) {
		std::unique_lock<std::mutex> lock(_mutex);
		_queue.push(val);
	}

	Q popQueue() {
		std::unique_lock<std::mutex> lock(_mutex);
		Q val = _queue.front();
		_queue.pop();
		return val;
	}
	
	std::vector<V> getVector() {
		std::unique_lock<std::mutex> lock(_mutex);
		return _vector;
	}
	
	void setVector(std::vector<V> vect) {
		std::unique_lock<std::mutex> lock(_mutex);
		_vector = vect; 
	}

	void releasePipe() {
		std::unique_lock<std::mutex> lock(_mutex);
		_state = true;
		cv.notify_all();
	}
	
	void acquirePipe() { // Returns false if pipe is in use, true if pipe has been acquired
		std::unique_lock<std::mutex> lock(_mutex);
		if (_state) { _state = false; return; }
		cv.wait(lock);
	}
};
