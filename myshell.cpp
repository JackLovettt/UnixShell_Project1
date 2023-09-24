#include "param.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;


Param* parse(string input){ //I wanted to have this in parse.cpp but I was getting errors returning a Param pointer

    istringstream inStream;

    char *inputRedirect=nullptr;
    char *outputRedirect=nullptr;
    int background=0;
    int argumentCount=0;
    char *argumentVector[MAXARGS];

    
    for(int i=0;i!=MAXARGS;i++){ //set every element of the array to a null character
        //argumentVector[i] = new char;
        argumentVector[i] = strdup("\0");
        //strcpy(argumentVector[i],"\0"); //trying to construct and destruct all 32 entries and it failed
    }
    
    //cout << endl;
    //cout << "Parsing input :" << input << "|" << endl;
    //cout << "After trimming :" << input.substr(0, input.find_last_not_of(" ")+1) << "|" << endl;
    
    inStream.clear();

    //loads inStream with input, with all trailing " " characters removed
    inStream.str(input.substr(0,(input.find_last_not_of(" ")+1)));

    string temp;

    while(!inStream.eof()){

        inStream >> temp;

        if(temp.at(0)=='<'){ //input redirect char

            if(temp=="<"){
                cout << "ERROR, input redirect characted detected but no file specified" << endl;
                return nullptr;
            }

            //cout << "Input redirect detected" << endl;

            inputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(inputRedirect, temp.c_str()); //use c_str() to convert to char[] to use
            
            strcpy(argumentVector[argumentCount],temp.c_str());  //MAYBE DELETE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            argumentCount++;

        }

        else if(temp.at(0)=='>'){   //output redirect char 

            //cout << "Output redirect detected" << endl;
            if(temp==">"){
                cout << "ERROR, output redirect characted detected but no file specified" << endl;
                return nullptr;
            }
            outputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(outputRedirect, temp.c_str()); //use c_str() to convert to char[] to use

        }

        else if(temp.at(0)=='&'){
            //cout << "Background flag detected" << endl;
            background=1;
        }

        else{
            
            //argumentVector[argumentCount]=strdup(temp.c_str()); //need to allocate memory for new string
            strcpy(argumentVector[argumentCount],temp.c_str()); 
            argumentCount++;

        }
        
    }

    if(argumentCount<MAXARGS){              //if we need a final NULL
        argumentVector[argumentCount]=NULL; //sets the last arg to NULL
    }

    /*
    cout << "Args during parsing:" << endl;
    for(int i=0;i<MAXARGS;i++){
        cout << "Arg " << i << ": " << argumentVector[i] << endl;
    }
    cout << endl;
    */
    
    Param* out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);
    
    return out;
}

//called when user enters "exit"
//we call WAIT() for each background job. 
//some of these may have already ended
void shutdown(int backgroundJobs){ 

    cout << "Beginning shutdown procedure" << endl;

    //wait for all child processes to end
    for(int i=0; i<backgroundJobs; i++){    

        cout << "Shutting down background job #" << i+1 << "/" << backgroundJobs << endl;
        wait(NULL);

    }

    cout << "Shutdown procedure complete" << endl << endl;
    exit(1);

}


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //Points at the param for execution
    Param* param;

    //Search for debug flag
    for(int i=0;i<argc;i++){ 
        if(strcmp(argv[i], "–Debug")==0 || strcmp(argv[i], "-Debug")==0){  //When I copy pasted the "-Debug" from the pdf it used a weird '-' character, 
           debug=true;                                                     //so I ORed it with a normal hyphen
        }
    }

    cout << endl << "Debug mode: " << debug << endl;

    int backgroundJobs=0;   //we will WAIT(NULL) this many times during shutdown 
                            //to ensure that all child processes have exited

    //exit check is done after user input
    while (1==1){
        
        //prompt
        cout << endl << "~> ";

        //get entire line of input from buffer
        getline(cin, input);
        cin.clear(); //clear input buffer after getting one line
        cout << endl;

        //check exit condition
        if(input=="exit"){
            shutdown(backgroundJobs);
        }
        
        //if the user hits enter without typing anything
        if(input.empty()){
            cin.clear(); //prevents infinite loop that crashes computer
            continue;
        }
       
        param=parse(input); 

        if(param==nullptr){ //if input parsing failed
            continue;}

        if(param->backgroundJob()){
            backgroundJobs++;
        }

        if(debug)   //print params if debugging is flagged
            param->printParams();

        //Need a datastructure, or at least a basic array to hold these to check 
        //that they finish execution...
        int child=param->execute();

        //after execution we must delete param
        delete param;
    }

}





