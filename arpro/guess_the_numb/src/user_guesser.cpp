#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    auto comp_number = rand() % 101;
    int user_number;

    cout << "Welcome to - GUESS THE NUMBER! (0-100)" << endl;
    //cout << comp_number;

    while (user_number != comp_number){
        cout << "\n\tYour input: ";
        cin >> user_number;

        if (user_number == comp_number){
            cout <<"\nYou guessed it! The number is " << comp_number <<endl;
            return 0;
        }
        else if(user_number > comp_number){
            cout << "\nYour guess is LARGER than the number." <<endl;
        }
        else if (user_number < comp_number){
            cout << "\nYour guess is SMALLER than the number" <<endl;
        }
    }
    return 0;
}
