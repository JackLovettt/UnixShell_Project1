#include "param.hpp"
#include <string>

using namespace std;

#ifndef PARSE_HPP
#define PARSE_HPP

class Parse{

    public:
          //parse the input and make the Param where param points
      static void parse(void* param, string input);  
      static Param* parseReturn(string input);

};

#endif