#include "param.hpp"

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using std::endl;
using std::cout;
using std::string;

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

    //cout << "Deleting stuff now" << endl;

    if(inputRedirect!=nullptr)
        delete inputRedirect;

    //cout << "Deleted input stuff" << endl;

    if(outputRedirect!=nullptr)
        delete outputRedirect;

    //cout << "Deleted output stuff" << endl;
    
    for(int i=0; i<argumentCount; i++){
        delete[] argumentVector[i];
        //cout << "Deleting loop interation " << i << endl;
    }

    //cout << "Deleted loop" << endl;



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

//if !background: returns 0 to the parent, 
//if background : returns the PID of the child to the parent
//child executes param, or exits with -1 if execution fails
int Param::execute(){

    int forkVal=fork();

    if(forkVal!=0){             //if Parent
        if(background==0){      //if not running in background
            wait(NULL);         //wait for the child to execute
            return 0;
        }
        return forkVal; //return child PID if running in background
    }
    
    //if Child:

    execvp(argumentVector[0], argumentVector);

    //if exec failed:

    cout << "ERROR, exec() failed. Please check your input" << endl << endl;

    //end the failed task
    exit(-1); 

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