CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wall -Werror=return-type  \
                        -Werror=uninitialized -Wno-sign-compare
RM = rm -rf

make: param.hpp param.cpp parse.hpp parse.cpp myshell.cpp 
		g++ param.hpp param.cpp parse.hpp parse.cpp myshell.cpp -o myshell
		
slow: slow.cpp
		g++ -o slow slow.cpp

clean:
		rm -rf *.dSYM
		rm -f slow
		rm -f myshell
		rm -f testfile.txt
		$(RM) *.o *.out *.gc* main 