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
