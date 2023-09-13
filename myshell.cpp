#include "param.hpp"
#include "parse.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;


Param* parse(string input){ //I wanted to have this in parse.cpp but I was getting errors returning a Param pointer

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


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //main loop will exit when this is set to true
    bool exit = false;

    //Points at the param
    Param* param;

    cout << "Entered: ";

    //Search for debug flag
    for(int i=0;i<argc;i++){ 

        cout << argv[i] << " ";
        
        //This was working, I changed other things, and for some reason this stopped working
        //I don't see a reason why it shouldn't work
        if(argv[1]=="–Debug" || argv[1]=="-Debug"){  //When I copy pasted the "-Debug" from the pdf it used a weird '-' character, 
            debug=true;                              //so I ORed it with a normal hyphen
        }

        debug=true; //done to manually force debug mode since "-Debug" =/= "-Debug" apparently

    }

    cout << endl;

    cout << "Debug mode: " << debug << endl;


    while (!exit){
        
        //prompt
        cout << "Enter command > ";

        //get entire line from buffer
        getline(cin, input);
        cout << endl;

        //check exit condition
        if(input=="exit"){
            exit=true;
            continue;
        }

        //parse the input and save the Param
        param=parse(input); 

        if(debug)   //print params if debugging is flagged
            param->printParams();

    }

}





