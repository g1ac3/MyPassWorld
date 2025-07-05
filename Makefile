# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -static -Wall -IPWAUTH -std=c++11
CFLAGS = -static -Wall -IPWAUTH -I PWAUTH/BLAKE3/c -O3

# Source files
CPP_SRCS = mypass.cpp PWAUTH/PWAUTH.cpp
C_SRCS = PWAUTH/BLAKE3/c/blake3.c PWAUTH/BLAKE3/c/blake3_portable.c PWAUTH/BLAKE3/c/blake3_dispatch.c
BLAKE3_OPT_SRCS = PWAUTH/BLAKE3/c/blake3_avx2.c PWAUTH/BLAKE3/c/blake3_avx512.c PWAUTH/BLAKE3/c/blake3_sse2.c PWAUTH/BLAKE3/c/blake3_sse41.c

# Object files
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
C_OBJS = $(C_SRCS:.c=.o)
BLAKE3_OPT_OBJS = $(BLAKE3_OPT_SRCS:.c=.o)
OBJS = $(CPP_OBJS) $(C_OBJS) $(BLAKE3_OPT_OBJS)

# Executable name
TARGET = MyPassWorld

# Default target
all: $(TARGET)

# Submodules
submodules:
	git submodule update --remote --merge

# Link object files to create the executable
$(TARGET): submodules $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

PWAUTH/BLAKE3/c/blake3_avx2.o: PWAUTH/BLAKE3/c/blake3_avx2.c
	$(CC) $(CFLAGS) -mavx2 -c $< -o $@

PWAUTH/BLAKE3/c/blake3_avx512.o: PWAUTH/BLAKE3/c/blake3_avx512.c
	$(CC) $(CFLAGS) -mavx512f -mavx512vl -c $< -o $@

PWAUTH/BLAKE3/c/blake3_sse2.o: PWAUTH/BLAKE3/c/blake3_sse2.c
	$(CC) $(CFLAGS) -msse2 -c $< -o $@

PWAUTH/BLAKE3/c/blake3_sse41.o: PWAUTH/BLAKE3/c/blake3_sse41.c
	$(CC) $(CFLAGS) -msse4.1 -c $< -o $@

# Clean up generated files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean submodules