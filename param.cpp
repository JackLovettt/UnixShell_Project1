#include <iostream>
#include "param.hpp"
using std::endl;
using std::cout;

int x=0;

Param::Param(char *inputRedirect, char *outputRedirect, int background, int argumentCount, char *argumentVector[MAXARGS]){

    this->inputRedirect=inputRedirect;
    this->outputRedirect=outputRedirect;
    this->background=background;
    this->argumentCount=argumentCount;
    
    for(int i=0;i<argumentCount;i++){
        this->argumentVector[i]=argumentVector[i];
    }

}

Param::~Param(){

    cout << "Deleting stuff now" << endl;

    if(inputRedirect!=nullptr)
        delete inputRedirect;

    cout << "Deleted input stuff" << endl;

    if(outputRedirect!=nullptr)
        delete outputRedirect;

    cout << "Deleted output stuff" << endl;
    
    cout << "Background's value: " << background << endl;



    for(int i=0; i<argumentCount; i++){
        delete[] argumentVector[i];
            cout << "Deleting loop interation " << i << endl;
    }

    cout << "Deleted loop" << endl;



    //Do I even need to delete these last three?
    //Are they on myshell's stack?
    //Is that why parse.cpp is failing? Do I need to save it's values to the heap?

    //delete &argumentVector; 
    //cout << "Deleted array pointer" << endl;

    //delete &argumentCount;
    //cout << "Deleted argument count" << endl;


    //delete &background;
    //cout << "Deleted background" << endl;

}



void Param::printParams(){
    
    if(inputRedirect!=NULL)
        cout << "InputRedirect: [" << inputRedirect << "]" << endl;
    
    if(outputRedirect!=NULL)
        cout << "OutputRedirect: ["<< outputRedirect << "]" << endl;

    if(background==1)
        cout << "Background: [" << background << "]" << endl;

    

    
    for (int i = 0; i < argumentCount; i++)
        cout << "ArgumentVector["
            << i
            << "]: ["
            << argumentVector[i]
            << "]"
            << endl;
    

    cout << endl;
}



/*
void Param::printParams() { //taken from canvas, prints 1 or 0 instead of string values

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
            << endl << endl;
}
*/