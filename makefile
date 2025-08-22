CXX = g++
CXXFLAGS = -Wall -std=c++11

program: driver.o songQueue.o
	$(CXX) $(CXXFLAGS) driver.o songQueue.o -o program

driver.o: driver.cpp songQueue.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

songQueue.o: songQueue.cpp songQueue.h
	$(CXX) $(CXXFLAGS) -c songQueue.cpp

clean:
	rm -f *.o program

run:
	./program

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -s ./program
