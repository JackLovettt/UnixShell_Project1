#include "parse.hpp"
#include "param.hpp"

#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

static void parse(void* param, string input){

    istringstream inStream;

    char *inputRedirect=NULL;
    char *outputRedirect=NULL;
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
  
            //argumentVector[argumentCount] = (char*)temp.c_str(); //just makes argumentVector[i] point at temp

            //cout << argumentVector[argumentCount] << endl;

            argumentCount++;
        }
        


    }

    //cout << endl; //DELETE ME WHEN DONE DEBUGGING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    param = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);
    
}


Param* parseReturn(string input){ //I wanted to have this in parse.cpp but I was getting errors returning a Param pointer

    istringstream inStream;

    char *inputRedirect=NULL;
    char *outputRedirect=NULL;
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
  
            //argumentVector[argumentCount] = (char*)temp.c_str(); //just makes argumentVector[i] point at temp

            //cout << argumentVector[argumentCount] << endl;

            argumentCount++;
        }
        


    }

    //cout << endl; //DELETE ME WHEN DONE DEBUGGING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    

    //Param *out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);

    Param* out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);
    

    return out;
}