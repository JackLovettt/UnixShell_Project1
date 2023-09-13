I am unfamilliar with C++ and have been struggleing through this.

I intended to use parse.cpp and parse.hpp to parse my inputs, however I was having issues with returning pointers,
so I decided to paste that function into myshell.cpp instead.


I had debug flag checking working, however after I changed unrelated code C++ has now determined that "-Debug" =/= "-Debug".
I'm forcing debug to be true on line 121 of myshell, just after the check