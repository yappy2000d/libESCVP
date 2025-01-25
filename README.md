# libESCVP
libESCVP is a cross-platform C++ library that defines the ESC/VP21 protocol for communication with projectors. The actual communication is handled by [ESCVPClient](). The library provides simple interfaces for controlling and managing projectors.

## Features
+ Cross-platform support: Supports both Windows and Linux.
+ Dynamic and static libraries: Can be compiled as either a shared or static library.
+ Simple and easy-to-use interface: Provides clear APIs for sending commands and receiving projector responses.

## Installation
You can add libESCVP via FetchContent.
```
include(FetchContent)

FetchContent_Declare(
    libESCVP
    GIT_REPOSITORY "https://github.com/yappy2000d/libESCVP.git"
    GIT_TAG "v1.0.0"
)

FetchContent_MakeAvailable(libESCVP)

add_executable(MyApp main.cpp)
target_link_libraries(MyApp PRIVATE libESCVP)
```
## License
This project is licensed under the MIT License.
