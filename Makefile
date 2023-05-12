# Compiler options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# SFML options
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# macOS specific options
ifeq ($(shell uname), Darwin)
    SFML_INC = -I/opt/homebrew/include
    SFML_LDFLAGS = -L/opt/homebrew/lib
else
# Windows specific options
    SFML_INC = -I<sfml_install_directory>/include
    SFML_LDFLAGS = -L<sfml_install_directory>/lib
endif
# Source files
SRCS = main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable file
EXEC = game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SFML_LIBS) $(SFML_LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
