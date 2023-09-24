#include "param.hpp"

#include <iostream>
#include <string>
#include <cstring>
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
    
    for(int i=0;i<MAXARGS;i++){
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
    
    for(int i=0; i<MAXARGS; i++){
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

bool Param::backgroundJob(){
    return background;
}



void Param::printParams(){
    
    if(inputRedirect!=NULL)
        cout << "InputRedirect: [" << inputRedirect << "]" << endl;
    
    if(outputRedirect!=NULL)
        cout << "OutputRedirect: ["<< outputRedirect << "]" << endl;

    if(background==1)
        cout << "Background: [" << background << "]" << endl;

    for (int i = 0; i < argumentCount; i++)
        cout << "ArgumentVector[" << i << "]: [" << argumentVector[i] << "]" << endl;

    cout << endl;
}

//if !background: returns 0 to the parent, 
//if background : returns the PID of the child to the parent
//child executes param, or exits with -1 if execution fails
int Param::execute(){

    cout.clear();
    std::cin.clear();
    
    /*  
    cout << "Checking arguments during execution:" << endl;

    //arg dup debugging
    if(fork()==0){
        for(int i=0;i<MAXARGS;i++){ //print everything till it fails
             cout <<"Arg " << i << ": " << argumentVector[i] << endl;
        }
        exit(1);
    }
    else{
        wait(NULL);
        cout << endl << endl;
    }
    */


    int forkVal=fork(); //split parent and child

    if(forkVal!=0){//if Parent
    
        if(background==0){              //if not running in background
            waitpid(forkVal, NULL, 0);  //wait for the child to execute
            return 0;
        }

        return forkVal; //return child PID if running in background
    }
    
    //else => Child:

    
    if(outputRedirect!=nullptr){    //if we need to write to file
        freopen(outputRedirect, "w", stdout);   //overrwite that file with out output
    }

    execvp(argumentVector[0], argumentVector);  //execute the Param
    

    //if exec failed:

    cout << "ERROR, exec() failed. Please check your input" << endl << endl;

    //end the failed task
    exit(-1); 

}
