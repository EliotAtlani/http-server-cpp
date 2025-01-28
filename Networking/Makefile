# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Target executable
TARGET = test.exe

# Source files
SRCS = Server/test.cpp \
       Server/TestServer.cpp \
       Server/SimpleServer.cpp \
       Socket/SimpleSocket.cpp \
       Socket/BindingSocket.cpp \
       Socket/ListeningSocket.cpp

# Default rule to build the target
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean
