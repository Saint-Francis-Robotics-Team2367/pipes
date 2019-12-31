#include "GenericPipe.h"
#include <thread>
#include <iostream>
#include <chrono>

void f1(GenericPipe* pipe) {
	while(true) {
		if(!pipe->acquirePipe()) continue;
		std::cout << "f1 got the pipe" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5)); // To simulate some work being done
		pipe->pushQueue(50);
		pipe->releasePipe(); // The other thread can now get it
		return;
	}
}

void f2(GenericPipe* pipe) {
	while(true) { // This is called spinning, on the actual robot threads are scheduled
		if(!pipe->acquirePipe()) continue; // Spin until pipe is ready
		std::cout << "f2 got the pipe" << std::endl;
		std::cout << "Value from queue: " << pipe->popQueue() << std::endl; // If this function happens before the first one, this would throw an error
		pipe->releasePipe();
		return;
	}
}

int main() {
	GenericPipe *pipe = new GenericPipe();
	std::thread t1(f1, pipe);
	std::thread t2(f2, pipe);
	t1.join();
	t2.join();
}
