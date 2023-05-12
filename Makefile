# Compiler options
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic

# SFML options
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# macOS specific options
ifeq ($(shell uname), Darwin)
    SFML_INC = -I/opt/homebrew/include
    SFML_LDFLAGS = -L/opt/homebrew/lib $(SFML_LIBS)
else
# Windows specific options
    SFML_INC = -I$(wildcard C:/SFML*/include)
    SFML_LDFLAGS = -L$(wildcard C:/SFML*/lib) $(SFML_LIBS)
endif
# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable file
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJS)	
	$(CXX) $(CXXFLAGS) $(SFML_INC) $^ -o $@ $(SFML_LDFLAGS) 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
