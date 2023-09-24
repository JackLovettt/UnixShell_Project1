#include <iostream>
#include <unistd.h>

using namespace std;

int main(){

    cout << "Lets count to 30!" << endl;

    for(int i=0;i<=30;i++){
        cout << "i: " << i << endl;
        sleep(1);
    }

}