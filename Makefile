# Makefile for Mastermind Project Part B
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Target executable
TARGET = mastermind

# Object files
OBJECTS = main.o mastermind.o response.o code.o

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile main.cpp
main.o: main.cpp mastermind.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile mastermind.cpp
mastermind.o: mastermind.cpp mastermind.h code.h response.h
	$(CXX) $(CXXFLAGS) -c mastermind.cpp

# Compile response.cpp
response.o: response.cpp response.h
	$(CXX) $(CXXFLAGS) -c response.cpp

# Compile code.cpp (assuming you have this from Part A)
code.o: code.cpp code.h
	$(CXX) $(CXXFLAGS) -c code.cpp

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything from scratch
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets (not actual files)
.PHONY: all clean rebuild run
