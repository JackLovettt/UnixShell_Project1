//#include "param.hpp"
#include "parse.hpp"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


int main(int argc, char* argv[]){

    //holds user input until it is parsed to a Param
    string input;

    //verbose if true
    bool debug = false;

    //main loop will exit when this is set to true
    bool exit = false;

    Param *param;


    //Search for debug flag
    for(int i=1;i<argc;i++){ 
        if(argv[i]=="–Debug")
            debug=true;
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
         
       

        
        
        //param=Parse::parse(input);

    }

}



