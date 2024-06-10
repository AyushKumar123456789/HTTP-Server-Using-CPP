# [HTTP](https://www.rfc-editor.org/rfc/rfc9110#name-introduction)

`ssize_t` is a data type used in C and C++ programming, particularly in Unix-like operating systems. It is used to represent the sizes of blocks that can be read or written in a single operation. It is essentially the signed counterpart to `size_t`.

### Key Points about `ssize_t`

1. **Signed Type**: size_t is an unsigned integer data type that is defined in various header files such as: `<stddef.h>, <stdio.h>, <stdlib.h>, <string.h>, <time.h>, <wchar.h>` It’s a type which is used to represent the size of objects in bytes and is therefore used as the return type by the sizeof operator. It is guaranteed to be big enough to contain the size of the biggest object the host system can handle.
2. **Return Type for System Calls**: `ssize_t` is commonly used as the return type for functions that perform I/O operations, such as `read`, `write`, and `recv`.
   - These functions return the number of bytes read or written.
   - A negative return value indicates an error (e.g., `-1`).
3. **Size Representation**: The type `ssize_t` is typically the same size as `size_t`, but signed. This means it can represent values in the range from `-1` to `SSIZE_MAX` (where `SSIZE_MAX` is typically equal to `SIZE_MAX / 2`).

### Example Usage in Network Programming

When you use functions like `recv`, the return type is `ssize_t` because it needs to indicate both the number of bytes received and potential error conditions.

```cpp
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

int main() {
    int sockfd;
    char buffer[1024];
    ssize_t bytes_received;

    // Assume sockfd is a valid socket descriptor
    bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);

    if (bytes_received < 0) {
        std::cerr << "Error receiving data\n";
    } else {
        std::cout << "Received " << bytes_received << " bytes\n";
    }

    return 0;
}
```

# CRLF

### In the example provided:

```
HTTP/1.1 200 OK\r\n
Content-Type: text/html\r\n
Content-Length: 23\r\n
\r\n
<html>\r\n
<body>\r\n
Hello, World!\r\n
</body>\r\n
</html>\r\n
```

The headers are:

1. `HTTP/1.1 200 OK`
2. `Content-Type: text/html`
3. `Content-Length: 23`

The body starts after the blank line (`\r\n\r\n`). So, the body in this example is:

```
<html>\r\n
<body>\r\n
Hello, World!\r\n
</body>\r\n
</html>\r\n
```

Headers and body are separated by the double `\r\n`, which indicates the end of the headers and the beginning of the body.

# User Agent header

- [Read Here..](https://developer.mozilla.org/en-US/docs/Glossary/User_agent)
- The User-Agent request header is a characteristic string that lets servers and network peers identify the application, operating system, vendor, and/or version of the requesting user agent.
  Example :

```http
User-Agent: <product> / <product-version> <comment>

User-Agent: Mozilla/5.0 (<system-information>) <platform> (<platform-details>) <extensions>

```

- `<product>` A product identifier — its name or development codename `<product-version>`
  Version number of the product.`<comment>`
  Zero or more comments containing more details. For example, sub-product information.

# Make File

A Makefile is a script that automates the compilation and linking process of software projects. It's particularly useful for managing projects with multiple source files or complex dependencies. Below are some key points about Makefiles along with an example:

### Key Points about Makefiles:

1. **Target-Dependency-Command Structure**:

   - Makefiles consist of rules with a target, dependencies, and commands.
   - Targets are the files or actions to be created.
   - Dependencies are the files required by the target.
   - Commands are the actions to be executed to produce the target.

2. **Automatic Dependency Tracking**:

   - Makefile allows automatic tracking of dependencies. If a source file changes, only the necessary components are recompiled.

3. **Efficiency**:

   - Makefile ensures that only the modified files are recompiled, which speeds up the compilation process.

4. **Flexibility**:

   - Makefiles support variables, conditionals, loops, and functions, making them flexible and adaptable to various project requirements.

5. **Portability**:
   - Makefiles are portable across different platforms and compilers, making them ideal for cross-platform development.

### Example Makefile:

```make
# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -Wextra -std=c++11

# Source files
SRCS := main.cpp server.cpp HttpRequestHandler.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
EXEC := server

# Main target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
    $(CC) $(OBJS) -o $(EXEC)

# Rule to compile source files
%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
    rm -f $(OBJS) $(EXEC)
```

### Explanation:

- **CC**: Compiler to be used (here, `g++`).
- **CFLAGS**: Compiler flags, including warnings and C++ version.
- **SRCS**: List of source files.
- **OBJS**: List of object files derived from source files.
- **EXEC**: Name of the executable to be generated.
- **all**: Main target, builds the executable.
- **$(EXEC)**: Rule to build the executable, depends on object files.
- **$(OBJS)**: Rule to compile source files into object files.
- **clean**: Rule to remove generated object files and the executable.

### Usage:

1. Save the Makefile in the project directory.
2. Run `make` command in the terminal to compile the project.
3. Run `make clean` to remove generated files.

# Thread & MultiThreading

## Multithreading is a feature that allows concurrent or simultaneous execution of two or more parts of a program for maximum utilization of the CPU. Each part of such a program is called a thread. So, `Threads are lightweight processes within a process`.

## C++ 11 Provide std::thread and define in <thread> .

```cpp
    std::thread thread_object (pointer of function);
```

- std::thread is the thread class that represents a single thread in C++. To start a thread we simply need to create a new thread object and pass the executing code to be called (i.e, a callable object) into the constructor of the object. Once the object is created a new thread is launched which will execute the code specified in callable. A callable can be `Pointer of function` and other things.

### Examples :

```cpp
void foo(param)
{
  Statements;
}
// The parameters to the function are put after the comma
std::thread thread_obj(foo, params);
```

### Every Thread object must go through detach and join if not lead to error.

- ### Join

  - It waits or hault the program until that thread on which join function is called will complete it execution and then goes to next thread or if there is no other thread goes to main function thread.

  Example :

```cpp

    void foo(int Z)
    {
        for (int i = 0; i < Z; i++) {
            cout << "Thread using function"
                    " pointer as callable\n";
        }
        std::this_thread::sleep_for(chrono:seconds(5));
    }


    int main()
    {
        cout << "Threads 1 "
                "operating independently"
            << endl;

        // This thread is launched by using
        // function pointer as callable
        thread th1(foo, 3);
        th1.join();
        return 0;
    }

```

- ### Detach

  - It is used to detach the newly created thread fromt the parent thread , Always check before detaching a thread that it is joinable otherwise we may end up double detaching and double detach willresult into program execution.

```cpp

    void foo(int Z)
    {
        for (int i = 0; i < Z; i++) {
            cout << "Thread using function"
                    " pointer as callable\n";
        }
        std::this_thread::sleep_for(chrono:seconds(5));
    }


    int main()
    {
        cout << "Threads 1 "
                "operating independently"
            << endl;

        // This thread is launched by using
        // function pointer as callable
        thread th1(foo, 3);
        if(th1.joinale())
        {
            th1.detach();
        }
        return 0;
    }
```

- `To Compile Thread used code , you have to write `**g++ -c file_to_compiled.cpp -o Output_compiled_file.o -pthread** The -pthread flag in the g++ command is used to enable multithreading with the POSIX threads (pthreads) library in Linux.

## How to check Concurrent Connection :

To check if your server can handle concurrent connections, you need to perform a test that simulates multiple clients connecting to your server simultaneously. Here are a few methods to achieve this:

:4221/`: The URL of your server.

### 2. **Using `siege`**

`Siege` is another powerful tool for load testing and benchmarking your server.

First, install `siege`:

- On Debian-based systems:
  ```sh
  sudo apt-get install siege
  ```

Then run a test:

```sh
siege -c 10 -r 10 http://localhost:4221/
```

- `-c 10`: Number of concurrent users.
- `-r 10`: Number of repetitions for each user.

Certainly! Here's an explanation in simple language:

---

# Understanding `int argc, char **argv` in the `main` Function

When you write a C or C++ program, the `main` function is the starting point. Sometimes, you want your program to accept inputs from the command line. This is where `int argc` and `char **argv` come into play.

#### `int argc`

- `argc` stands for **argument count**.
- It tells you how many command-line arguments were passed to your program.
- This number includes the program's name itself.

For example:

```bash
./myprogram arg1 arg2
```

Here, `argc` would be 3 (`./myprogram`, `arg1`, `arg2`).

#### `char **argv`

- `argv` stands for **argument vector**.
- It is an array of pointers to strings (character arrays).
- Each element in this array is one of the command-line arguments.

In the same example:

```bash
./myprogram arg1 arg2
```

- `argv[0]` would be `"./myprogram"`
- `argv[1]` would be `"arg1"`
- `argv[2]` would be `"arg2"`

#### Putting It All Together

Here's a simple example of using `argc` and `argv` in a program:

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    return 0;
}
```

If you run this program with:

```bash
./myprogram first second third
```

The output will be:

```
Number of arguments: 4
Argument 0: ./myprogram
Argument 1: first
Argument 2: second
Argument 3: third
```

#### Summary

- `argc` gives the number of command-line arguments.
- `argv` is an array containing the actual arguments as strings.
- Use `argc` to know how many arguments there are.
- Use `argv` to access each argument.

---

### Understanding Content-Type in HTTP Responses

When a web server sends a response to a web browser, it includes various headers that provide information about the response. One important header is the `Content-Type`. This header tells the browser what kind of content it is receiving, so the browser knows how to display it correctly.

#### Common Content-Types:

1. **text/html**: HTML content. The browser will render this as a web page.
2. **text/plain**: Plain text. The browser will display this as simple text.
3. **application/json**: JSON data. The browser or a web application will process this as JSON.
4. **image/jpeg**: JPEG image. The browser will display this as an image.
5. **application/octet-stream**: Binary data. The browser will typically prompt to download this file.

#### How to Use Content-Type in Your Server Code

To ensure the browser handles the response correctly (e.g., displaying it instead of downloading it), you need to set the `Content-Type` header appropriately in your HTTP responses.

Here’s how you can achieve this in a C++ HTTP server:

1. **Include the `Content-Type` header in the response based on the type of content being served.**
2. **Use different content types for different types of responses (HTML, plain text, binary files, etc.).**

#### Example Code with Proper Content-Types

Here’s your code, modified to set the correct `Content-Type` headers:

### Summary

- **Content-Type Header**: Informs the browser about the type of content in the response.
- **Setting Content-Type**: Ensure the content is displayed correctly by setting the right `Content-Type` for HTML, plain text, JSON, images, etc.
- **Example Code**: Shows how to set the `Content-Type` header for different types of responses in a C++ HTTP server.

This explanation should be sufficient to understand and implement the proper use of `Content-Type` in HTTP responses.
