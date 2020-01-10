/* Krishna Mani
 * Pipe.h
 */
#ifndef GENERICPIPE_H
#define GENERICPIPE_H

#include <mutex>
#include <stack>
#include <string>

class Message {
	public:
	std::string str;
	float val;
};

class GenericPipe {
	std::mutex _mutex;
	
	std::stack<Message*> _stack;

	public:
	void pushQueue(Message*);
	void* popQueue();
};

#endif
