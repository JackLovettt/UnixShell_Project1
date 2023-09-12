#include "parse.hpp"
#include "param.hpp"
#include <string>
#include <sstream>

using namespace std;

Param parse(string input){

    istringstream inStream;

    char *inputRedirect;
    char *outputRedirect;
    int background;
    int argumentCount;
    char *argumentVector[MAXARGS];

    inStream.clear();
    inStream.str(input);

    while(!inStream.eof()){
        
    }


    Param *out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);

    return *out;


}
