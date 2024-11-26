# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Targets
TARGET = WordCountTest
OBJS = WordCount.o tddFuncs.o Lab07Test.o

# Default target
all: $(TARGET)

# Build the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile WordCount.cpp
WordCount.o: WordCount.cpp
	$(CXX) $(CXXFLAGS) -c WordCount.cpp

# Compile tddFuncs.cpp
tddFuncs.o: tddFuncs.cpp
	$(CXX) $(CXXFLAGS) -c tddFuncs.cpp

# Compile lab06Tests.cpp
Lab07Test.o: Lab07Test.cpp
	$(CXX) $(CXXFLAGS) -c Lab07Test.cpp

# Clean up build files
clean:
	rm -f $(TARGET) *.o