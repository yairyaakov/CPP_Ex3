#ID : 207723198
#Mail : yair852258@gmail.com

# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = .

# Files
DEMO_SRC = Demo.cpp Player.cpp Board.cpp Vertex.cpp Plot.cpp DevelopmentCard.cpp Edge.cpp
TEST_SRC = Test.cpp Player.cpp Board.cpp Vertex.cpp Plot.cpp DevelopmentCard.cpp Edge.cpp

# Executables
DEMO = demo
TEST = test

catan: $(DEMO)
	./$(DEMO)

runtest: $(TEST)
	./$(TEST)

.PHONY: all clean

all: $(DEMO) $(TEST)

$(DEMO): $(DEMO_SRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) Demo.o Player.o Board.o Vertex.o Plot.o DevelopmentCard.o Edge.o -o $(DEMO)

$(TEST): $(TEST_SRC:.cpp=.o)
	$(CXX) $(CXXFLAGS) Test.o Player.o Board.o Vertex.o Plot.o DevelopmentCard.o Edge.o -o $(TEST)

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(DEMO) $(TEST)











