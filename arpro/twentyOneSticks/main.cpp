#include <iostream>

using namespace std;

void show_sticks(int sticks){
    for(int i = 1; i<=sticks; i++){
        cout<<" | ";
    }
}

int main()
{
    int sticks_left = 21;
    show_sticks(sticks_left);

    cout << "\nWelcome to - 21 STICKS!"<<endl;
    cout << "";
}
