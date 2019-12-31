# Pipes
Pipes are the lowest level in a multithreaded system. They implement communcation between modules contained in their own threads.

Pipes provide:
- Thread-safety through C++11 mutexes
- Nonblocking access to ensure one unintended exception does not affect other threads 
- A protected queue of ints, intended to store instructions
- A protected queue of floats, intended to store sensor data, motor setpoints, etc.

To access data from a pipe, one must: 
1. Acquire the pipe using  `GenericPipe::acquirePipe()`/`GenericPipe::blockingAcquirePipe()`
2. Access whatever data is needed using the relevant functions
3. Release the pipe using `GenericPipe::releasePipe()`

`GenericPipe::acquirePipe()` returns true if the pipe was acquired, and false when it is being used. This way, code can still be run if it is not dependent on the data from the pipe. 

For cases where an efficient method of blocking for a pipe acquire, `GenericPipe::blockingAcquirePipe()` puts the thread to sleep using C++11 condition variables until the pipe has been released.
See `example.cpp` for a reference use case.
