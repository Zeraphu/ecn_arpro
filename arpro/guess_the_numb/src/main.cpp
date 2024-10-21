#include <iostream>

using namespace std;

int main()
{
    auto guess_done = 0;

    int low = 1, high = 100;
    auto GreaterThan = -1;
    int thresh = -1;

    cout << "Welcome to - GUESS THE NUMBER! (1-100)" << endl;
    cout << "Pick a number between 1-100 and don't tell anyone!"<<endl;

    for (int i = 0;i<10;i++){
        thresh = low + (high-low)/2;

        cout << "Is your number smaller [0], bigger [1] than or equal [2] to "<<thresh<<"?";
        cout<< "\tNumber of guesses left: "<<10-i<<endl;
        cin >>GreaterThan;

        if(GreaterThan == 1){
            low = thresh;
        }else if (GreaterThan == 0){
            high = thresh;
        }else if (GreaterThan == 2){
            cout <<"Your number is : "<<thresh<<endl;
            cout<< "Guessed your number in "<<i<<" tries!"<<endl;
            return 0;
        }
    }

    if(GreaterThan){
        cout<< "Is your number here?\n";
        for(int i = high;i>thresh;i--){
            cout <<i;
        }
        cout <<endl;
    }
    else{
        cout<< "Is your number here?\n";
        for(int i = low;i<thresh;i++){
            cout <<i;
        }
        cout <<endl;
    }
    return 0;
}
