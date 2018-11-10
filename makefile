CXXFLAGS += -std=c++11

ex: rekt_main.o book.o
	$(CXX) $(CXXFLAGS) -g -o rekt rekt_main.o book.o
rekt_main.o: rekt_main.cpp book.h
	$(CXX) $(CXXFLAGS) -c rekt_main.cpp
book.o: book.h book.cpp
	$(CXX) $(CXXFLAGS) -c book.cpp