#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    int comp_score = 0, user_score = 0;
    auto user_hand = -1, comp_hand = -1;

    cout <<"Welcome to - ROCK, PAPER, SCISSORS!"<<endl;

    while(comp_score < 5 && user_score < 5){
        cout<<"\nSCOREBOARD:\tCOMP:" <<comp_score<<"\tUSER:"<<user_score<<endl;

        cout<<"\nRock [0], Paper [1], or Scissors [2]?"<<endl;
        cin>>user_hand;

        comp_hand = rand() % 3;
        cout<<"\nComputer hand: "<<comp_hand<<endl;

        if(user_hand == comp_hand){
            cout<<"\nNo one scores!"<<endl;
        }
        else if ((user_hand == 0 && comp_hand == 2) || (user_hand == 1 && comp_hand == 0) || (user_hand == 2 && comp_hand == 1)){
            user_score+=1;
            cout << "\nUser scores!"<<endl;
        }
        else if ((user_hand == 0 && comp_hand == 1) || (user_hand == 1 && comp_hand == 2) || (user_hand == 2 && comp_hand == 0)){
            comp_score+=1;
            cout << "\nComp scores!"<<endl;
        }
    }

    if (user_score > comp_score){
        cout << "\nYOU WIN!"<<endl;
    }
    else{
        cout<< "\nCOMP WINS!"<<endl;
    }
}
