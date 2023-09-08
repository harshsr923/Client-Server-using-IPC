# Client-Server-using-IPC
Client-Server Based Application Utilizing IPC for Seamless Communication

##Project Workflow Overview
1. Client-Server Architecture: Your project follows a client-server architecture where the client sends requests to the server.

2. Client Request Variety: There are four types of clients, each requesting different operations: addition (+), subtraction (-), multiplication (*), and division (/), The client sends requests to the server using FIFOs (named pipes), and the server receives these requests.

3. Multithreaded Server: The server is a multithreaded application, which allows it to handle multiple client connections concurrently. Each thread can independently process client requests assigned to it.

4. Server Vendor Assignment: Upon receiving a client request through a FIFO (named pipe), the server evaluates the requested operation and assigns the task to one of the four vendors specialized in handling addition, subtraction, multiplication, and division.

5. Server-Child Process Communication using Pipes: After forking and executing the vendor process, the server creates a pipe to send data to the child (vendor) process. It writes the necessary data, such as the request details, to the pipe for the child process to read.

6. Vendor Calculation: The vendor process, after reading the request details from the pipe, extracts the operands and operator, performs the calculation, generates the result and then vendor process writes the result to a shared memory segment.

7. Server Reads from Shared Memory: The server reads the result from the shared memory segment to obtain the vendor's calculation result.

8. Server Sends Response: The server, after obtaining the result from shared memory, sends the calculation result back to the client using Message Queues.