#ID : 207723198
#Mail : yair852258@gmail.com

CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = Demo.cpp Player.cpp Board.cpp Vertex.cpp Plot.cpp DevelopmentCard.cpp Edge.cpp Test.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = catan
TESTEXEC = runtest

all: $(EXEC)

$(EXEC): $(filter-out Test.o, $(OBJS))
	$(CXX) $(CXXFLAGS) $^ -o $@

Demo.o: Demo.cpp Board.hpp Player.hpp Vertex.hpp Plot.hpp DevelopmentCard.hpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Board.o: Board.cpp Board.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Vertex.o: Vertex.cpp Vertex.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Plot.o: Plot.cpp Plot.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

DevelopmentCard.o: DevelopmentCard.cpp DevelopmentCard.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Edge.o: Edge.cpp Edge.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Test.o: Test.cpp doctest.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TESTEXEC): $(filter Test.o, $(OBJS)) $(filter-out Demo.o, $(OBJS))
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(OBJS) $(EXEC) $(TESTEXEC)

.PHONY: all clean runtest catan

runtest: $(TESTEXEC)
	./$(TESTEXEC)

catan: $(EXEC)
	./$(EXEC)
