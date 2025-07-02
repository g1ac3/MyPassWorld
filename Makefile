# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -static -Wall -IPWAUTH

# Source files
SRCS = mypass.cpp PWAUTH/PWAUTH.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = MyPassWorld

# Default target
all: $(TARGET)

# Submodules
submodules:
	git submodule update --init --recursive

# Link object files to create the executable
$(TARGET): submodules $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean submodules