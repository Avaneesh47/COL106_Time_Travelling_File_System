# ------------------------------
# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -std=c++17

# ------------------------------
# Source and object files
SRCS = src/main.cpp src/File.cpp src/FileManager.cpp src/HashMap.cpp src/Heap.cpp
OBJS = $(SRCS:.cpp=.o)

# ------------------------------
# Detect OS
ifeq ($(OS),Windows_NT)
    TARGET = program.exe
    RM = del /Q
else
    TARGET = program
    RM = rm -f
endif

# ------------------------------
# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files and executable
clean:
	$(RM) $(OBJS) $(TARGET)
