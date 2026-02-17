# HTTP-Server-in-C
# Simple HTTP Server in C (Winsock)

This is a raw HTTP server implementation written in C using the Winsock2 API on Windows.

## Why did I build this?
It is very easy to create a web server using high-level languages like Python or Node.js today. However, I wanted to understand how computers actually communicate over the network without relying on heavy frameworks.

I built this project to learn:
- How the HTTP protocol works at the byte level.
- What a "Socket" really is and how to manipulate it.
- How to manage memory and connections manually in C.

## How it Works
1. Initializes the Windows Socket (WSA) library.
2. Creates a socket and binds it to port 1453.
3. Listens for incoming connections from a web browser.
4. Accepts the connection and reads the raw HTTP request.
5. Sends back a custom HTML response constructed manually.

## How to Compile & Run

If you are using Visual Studio:
Just open the project and run it. The code includes the necessary linker pragma for ws2_32.lib.

If you are using GCC (MinGW) via command line:
gcc main.c -o server -lws2_32
./server

After running the server, open your browser and go to:
http://localhost:1453

## Future Improvements
- Implement multi-threading to handle multiple requests simultaneously.
- Parse HTTP requests to serve different files (HTML, CSS, Images).
- Add a basic logging system.

## License
This project is for educational purposes. Feel free to use it to learn socket programming.
