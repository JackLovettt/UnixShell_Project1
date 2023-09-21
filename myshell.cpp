#include "param.hpp"
#include "parse.hpp"

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

    inStream.clear();
    inStream.str(input);

    string temp;

    while(!inStream.eof()){

        inStream >> temp;

        if(temp.at(0)=='<'){ //input redirect char

            //cout << "Input redirect detected" << endl;

            inputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(inputRedirect, temp.c_str()); //use c_str() to convert to char[] to use


        }

        else if(temp.at(0)=='>'){   //output redirect char 

            //cout << "Output redirect detected" << endl;

            outputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(outputRedirect, temp.c_str()); //use c_str() to convert to char[] to use

        }

        else if(temp.at(0)=='&'){
            //cout << "Background flag detected" << endl;
            background=1;
        }

        else{
       
            argumentVector[argumentCount]= strdup(temp.c_str()); //need to allocate memory for new string
            argumentCount++;

        }
        
    }

    //cout << endl; //DELETE ME WHEN DONE DEBUGGING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    Param* out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);
    
    return out;
}

//called when user enters "exit"
void shutdown(){ 

    //wait for all processes to end
    wait(NULL);

    //exit
    exit(1);

}


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //Points at the param
    Param* param;

    //Search for debug flag
    for(int i=0;i<argc;i++){ 
        
        //cout << "arg " << i << ": " << argv[i] << endl;


        if(strcmp(argv[i], "–Debug")==0 || strcmp(argv[i], "-Debug")==0){  //When I copy pasted the "-Debug" from the pdf it used a weird '-' character, 
           debug=true;                                                     //so I ORed it with a normal hyphen
        }

        

        //debug=true; //done to manually force debug mode since "-Debug" =/= "-Debug" apparently

    }

    cout << endl;

    cout << "Debug mode: " << debug << endl;

    //exit check is done after user input
    while (1==1){
        
        //prompt
        cout << "Enter command > ";

        //get entire line of input from buffer
        getline(cin, input);
        cout << endl;

        //check exit condition
        if(input=="exit"){
            shutdown();
        }
        
        //if the user hits enter without typing anything
        if(input.empty()){
            cin.clear();
            continue;
        }
       
        param=parse(input); 

        if(debug)   //print params if debugging is flagged
            param->printParams();

        //Need a datastructure, or at least a basic array to hold these to check 
        //that they finish execution...
        int child=param->execute();

        //if(!param->backgroundJob()){
           // join();
        //} 

        //after execution we must delete param
        delete param;
    }

}





