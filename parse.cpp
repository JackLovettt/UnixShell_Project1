#include "parse.hpp"
#include "param.hpp"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

static Param parse(string input){

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


    // TURN INPUT INTO ARGUMENTVECTOR HERE

    //Param *out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);

    Param *out = new Param(NULL, NULL, 0, 1, argumentVector);

    return *out;


}
