#include <iostream>
#include "param.hpp"
using std::endl;
using std::cout;

int x=0;

Param::Param(char *inputRedirect, char *outputRedirect, int background, int argumentCount, char *argumentVector[MAXARGS]){




}

Param::~Param(){

}

/*
void Param::printParams(){

    for(int i=0;i<argumentCount;i++){
        cout << argumentVector[i] << " ";
    }

    cout << endl;
}

*/

void Param::printParams() { //taken from canvas
    
    cout << "InputRedirect: ["
        << (inputRedirect != NULL) ? inputRedirect : "NULL";
    
    cout << "]" << endl
        << "OutputRedirect: ["
        << (outputRedirect != NULL) ? outputRedirect : "NULL";
    
    cout << "]" << endl
        << "Background: ["
        << background
        << "]"
        << endl

    << "ArgumentCount: ["
        << argumentCount
        << "]"
        << endl;
    
    for (int i = 0; i < argumentCount; i++)
        cout << "ArgumentVector["
            << i
            << "]: ["
            << argumentVector[i]
            << "]"
            << endl;
}

