# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Target executable
TARGET = test.exe

# Directories
SRC_DIRS = Server Socket

# Source files
SRCS = Server/test.cpp \
       Server/TestServer.cpp \
       Server/SimpleServer.cpp \
       Socket/SimpleSocket.cpp \
       Socket/BindingSocket.cpp \
       Socket/ListeningSocket.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Default rule to build the target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
