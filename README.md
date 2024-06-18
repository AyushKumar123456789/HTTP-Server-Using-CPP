# Web Server Using CPP

## Overview

The server can handle basic HTTP GET and POST requests. It serves files from a specified directory, echoes back messages, and handles user-agent requests.

Go and Put your index.html file in files folder and go to your browser and search for `http://localhost:4221/files/index.html` You will able to see your web site rendering.

## Features

1. **GET Requests:**

   - Serve the root directory (`/`).
   - Echo back a message (`/echo/{message}`).
   - Return the user-agent string (`/user-agent`).
   - Serve files from the `files` directory (`/files/{filename}`).

2. **POST Requests:**

   - Save files to the `files` directory (`/files/{filename}`).

3. **Multi-threaded Server**

   - The server handles multiple client connections concurrently using threads. Each incoming connection is handled in a separate thread, allowing the server to process multiple requests simultaneously.

4. **Error Handling:**
   - Responds with `404 Not Found` for invalid paths.
   - Responds with `405 Method Not Allowed` for unsupported HTTP methods.

## Project Structure

```
SimpleHTTPServer/
├── src/
|   ├── Makefile
│   ├── httprequesthandler.cpp
│   ├── HttpRequestHandler.h
│   └── server.cpp
├── files/
│   └── [your files here]
└── README.md
```

### Source Files

- `src/httprequesthandler.cpp`: Handles the processing of HTTP requests.
- `src/HttpRequestHandler.h`: Header file for the `HttpRequestHandler` class.
- `src/server.cpp`: Main server application that listens for incoming connections and delegates request handling to `HttpRequestHandler`.

### Files Directory

- `files/`: Directory where files are served from and saved to.

### Makefile

- The `Makefile` is used to compile the project.

## Requirements

- C++ compiler (e.g., `g++`)
- `make` utility

  - ### For Windows : Use [WSL(Windows Subsystem for Linux)](<https://code.visualstudio.com/learn/develop-cloud/wsl#:~:text=The%20Windows%20Subsystem%20for%20Linux%20(WSL)%20lets%20you%20run%20a,machine%20or%20dual%20boot%20setup.>)

    The Windows Subsystem for Linux (WSL) lets you run a Linux environment, including command-line tools and applications, directly on Windows, without the overhead of a traditional virtual machine or dual boot setup.

    WSL especially helps web developers and those working with Bash and Linux-first tools (for example, Ruby and Python) to use their tools on Windows and ensure consistency between development and production environments.

## How to Build and Run

1. **Clone the Repository**

   ```sh
   git clone https://github.com/AyushKumar123456789/HTTP-Server-Using-CPP.git
   cd HTTP-Server-Using-CPP
   ```

2. **Build the Project**

   ```sh
   make
   ```

   This will compile the source files and produce an executable named `server`.

3. **Run the Server**

   ```sh
   ./server
   ```

   The server will start and listen for incoming connections on port `4221`.

## Usage

Once the server is running, you can test it using a web browser or tools like `curl`.

### GET Requests

- **Root Directory**

  ```sh
  curl http://localhost:4221/
  ```

- **Echo Message**

  ```sh
  curl http://localhost:4221/echo/hello
  ```

- **User-Agent**

  ```sh
  curl http://localhost:4221/user-agent
  ```

- **Serve File**

  Ensure there is a file named `example.txt` in the `files` directory.

  ```sh
  curl http://localhost:4221/files/example.txt
  ```

### POST Requests

- **Save File**

  ```sh
  curl -X POST -d "File content" http://localhost:4221/files/newfile.txt
  ```

## Error Handling

- **404 Not Found**

  Accessing a non-existent path:

  ```sh
  curl http://localhost:4221/nonexistent
  ```

- **405 Method Not Allowed**

  Using an unsupported HTTP method:

  ```sh
  curl -X PUT http://localhost:4221/
  ```

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

---

# This README provides a comprehensive overview of the Simple HTTP Server project, including its features, structure, and usage instructions. Feel free to modify it to suit the specific details of your project.

[HTTP](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) is the
protocol that powers the web. In this challenge, you'll build a HTTP/1.1 server
that is capable of serving multiple clients.

Along the way you'll learn about TCP servers,
[HTTP request syntax](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html),
and more.
