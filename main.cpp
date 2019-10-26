#include <iostream>
#include <thread>

#include "pipe.cpp"


void t1(genericPipe* pipe) {
	pipe->acquirePipe();
	pipe->pushQueue(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	pipe->releasePipe();
}

void t2(genericPipe* pipe) {
	pipe->acquirePipe();
	std::cout << pipe->popQueue() << std::endl;
	pipe->releasePipe();
}

int main() {	
	genericPipe* pipe = new genericPipe();
	std::thread thread1(t1, pipe);
	std::thread thread2(t2, pipe);
	thread1.join();
	thread2.join();
}

