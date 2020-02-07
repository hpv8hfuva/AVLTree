#Hunter Vaccaro
#hpv8hf
#Lab Section 11:00 am
CXX = clang++ $(CXXFLAGS)
CXXFLAGS = -std=c++11
DEBUG= -Wall -g
.SUFFIXES: .o .cpp
AVLSearchTree: AVLNode.o AVLTree.o AVLPathTest.o
	$(CXX) $(DEBUG) AVLNode.o AVLTree.o AVLPathTest.o 

AVLNode.o: AVLNode.cpp AVLNode.h
	$(CXX) -c AVLNode.cpp

AVLTree.o: AVLNode.cpp AVLNode.h AVLTree.h AVLTree.cpp
	$(CXX) -c AVLTree.cpp

AVLPathTest.o: AVLTree.h AVLTree.cpp AVLPathTest.cpp
	$(CXX) -c AVLPathTest.cpp

clean:
	-rm *.o *~ AVLSearchTree.exe
