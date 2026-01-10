# Dungeon Game Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = dungeon

# Source files
SRCS = main.cpp \
       Dungeon.cpp \
       Object.cpp \
       GameCharacter.cpp \
       Player.cpp \
       Monster.cpp \
       NPC.cpp \
       Item.cpp \
       Room.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Header files (for dependency tracking)
HDRS = Dungeon.hpp \
       Object.hpp \
       GameCharacter.hpp \
       Player.hpp \
       Monster.hpp \
       NPC.hpp \
       Item.hpp \
       Room.hpp

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild from scratch
rebuild: clean all

# Debug build with extra flags
debug: CXXFLAGS += -DDEBUG -O0
debug: rebuild

# Release build with optimizations
release: CXXFLAGS += -DNDEBUG -O2
release: rebuild

# Phony targets (not actual files)
.PHONY: all clean rebuild run debug release
