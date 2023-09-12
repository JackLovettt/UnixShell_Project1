#include "param.hpp"
#include "parse.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //main loop will exit when this is set to true
    bool exit = false;

    Param* param;
    Parse parser; //variable of type Parse named parser

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

         //exit condition
        if(input=="exit"){
            exit=true;
            continue;
        }

        cout << "You entered: " << input << endl;
         
       

        
        
        param=Parse::parse(input); //not sure if & is correct 

        param.printParams();

    }

}



