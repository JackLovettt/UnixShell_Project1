CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wall -Werror=return-type  \
                        -Werror=uninitialized -Wno-sign-compare
RM = rm -rf

make:
		g++ param.hpp param.cpp parse.hpp parse.cpp myshell.cpp 

clean:
		rm -rf *.dSYM
		$(RM) *.o *.gc* test/*.o main $(TESTS) test/catch/catch.o