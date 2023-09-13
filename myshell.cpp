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

    char *inputRedirect;
    char *outputRedirect;
    int background=0;
    int argumentCount=0;
    char* argumentVector[MAXARGS];

    inStream.clear();
    inStream.str(input);

    string temp;

    while(!inStream.eof()){

        inStream >> temp;

        if(temp.at(0)=='<'){ //input redirect char
            
            cout << "Redirect detected" << endl;

            inputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(inputRedirect, temp.c_str()); //use c_str() to convert to char[] to use

            

        }

        
        else if(temp.at(0)=='>'){ //input redirect char
            cout << "Redirect detected" << endl;

            outputRedirect= new char[temp.size()];

            temp = temp.substr(1,temp.size());

            strcpy(outputRedirect, temp.c_str()); //use c_str() to convert to char[] to use

            

        }
                
        

        //cout << temp << endl;

    }


    

    //Param *out = new Param(inputRedirect, outputRedirect, background, argumentCount, argumentVector);

    Param* out = new Param(inputRedirect, NULL, 0, argumentCount, argumentVector);

    return out;


}


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //main loop will exit when this is set to true
    bool exit = false;

    Param* param;
    //Parse parser; //variable of type Parse named parser

    //Search for debug flag
    for(int i=1;i<argc;i++){ 
        if(argv[i]=="–Debug" || argv[i]=="-Debug")  //When I copy pasted the "-Debug" from the pdf it used a weird '-' character, 
            debug=true;                             //so I ORed it with a normal hyphen
    }

    cout << "Debug mode: " << debug << endl;


    while (!exit){
        
        cout << "Enter command > ";

        //gets entire line from buffer
        getline(cin, input);

        cout << endl;

         //exit condition
        if(input=="exit"){
            exit=true;
            continue;
        }

        //cout << "You entered: " << input << endl;
         
       

        
        
        param=parse(input); //not sure if & is correct 

        param->printParams();

    }

}





