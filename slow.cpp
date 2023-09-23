#include <iostream>
#include <unistd.h>

using namespace std;

int main(){

    for(int i=0;i<=30;i++){
        cout << "Counting i: " << i << endl;
        sleep(1);
    }

}