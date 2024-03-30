### A simple multithreaded server in C that accesses some .txt files, reads and outputs them.

`server.c` : core of the server. Uses sockets to create connection and utilizes POSIX threads to handle multiple 'sessions' concurrently. Enqueues every request to the server and uses mutex and condition variable to properly handle the connections.

`queue.c` : implements a queue data structure with enqueue() and dequeue() functions.

`client.c` : represents a client application that connects to the server and requests a random .txt file.

`clients.bash` : generates a bunch of client connections.

### Usage:

First terminal: `./server`

Second terminal: `./clients.bash`
