# Pipes
Pipes are the lowest level in a multithreaded system. They implement communcation between modules contained in their own threads.

Pipes provide:
- Thread-safety through C++11 mutexes
- Nonblocking access to ensure one unintended exception does not affect other threads 
- A protected queue of Messages
Pipes are accessed through calls to either `void pushQueue(Message\*)` or `Message* popQueue()`, which access the internal stack of Messages. `nullptr` is returned if the stack is empty; you must handle this case.
