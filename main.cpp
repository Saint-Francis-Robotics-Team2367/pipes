#include <iostream>
#include <thread>
#include <vector>

#include "pipe.cpp"


void t1(genericPipe<int, int>* pipe) {
	pipe->acquirePipe();
	pipe->pushQueue(1);
	pipe->setVector(std::vector<int> {1, 10, 50});
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	pipe->releasePipe();
}

void t2(genericPipe<int, int>* pipe) {
	pipe->acquirePipe();
	std::cout << pipe->popQueue() << std::endl;
	std::vector<int> vect = pipe->getVector();
	for (int x : vect) std::cout << x << " ";
	pipe->releasePipe();
}

int main() {	
	genericPipe<int, int>* pipe = new genericPipe<int, int>();
	std::thread thread1(t1, pipe);
	std::thread thread2(t2, pipe);
	thread1.join();
	thread2.join();
}

