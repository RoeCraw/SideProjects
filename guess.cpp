#include <iostream>
#include <cmath>
#include <cstdlib>  // rand()
#include <ctime>    
#include <chrono>
#include <thread>


using namespace std;

void sleep(int seconds){ // just make the code less cluttered
    this_thread::sleep_for(chrono::seconds(seconds));
}

void leave(double money){
    sleep(2);
    cout << "\nVinny: Have a great day!\n";
    cout << "\nYou left with $" << money << "\n";
}


void game(double &money){
    bool again = true;
    cout << "\nMr. James: Welcome to my table.\n";
    sleep(2);
    while(again == true){
        double bet = 0;
        cout << "Mr. James: You know rules, guess my number and you double your money. Ready? (Yes or No)\n";
        cout << "\nYou: ";
        string quote1;
        cin >> quote1;

        for(char &c : quote1){
            c = tolower(c);
        }

        if(quote1 == "yes"){

            if(money <= 0){
                cout << "\nMr. James: You ain't got no money to play with. Get outta here.\n";
                sleep(1);
                cout << "\nYou were kicked out of the table.\n";
                again = false;
                return;
            }

            cout << "\nMr. James: What's your bet?\n";
            cout << "\nEnter your bet: $";


            cin >> bet;
            int count = 0;
            while((bet < 0) || (bet > money)){
                count += 1;
                cout << "\nMr. James: What do I look like to you? Put in a real bet before I kick you off this table.\n";
                if(count == 3){
                    cout << "\nMr. James: That's it. You're out of here.\n"; //Kick off table 
                    again = false;
                    leave(money);
                    return;
                }
                cout << "\nEnter your bet: $";
                cin >> bet;
            }
            cout << "\nMr. James: Alright let me think...\n";
            cout << "\nLoading...\n";
            int dealerNumber = (rand() % 5) + 1;//gives numbers between 0 and 4 and then we'll just always at 1 so it works out to numbers between 1 and 5
            sleep(3);
            cout << "\nMr. James: Got it. What do you got?\n";
            cout << "\nEnter your number: ";
            int userNumber;
            cin >> userNumber;

            if(dealerNumber == userNumber){
                cout << "\nMr. James: Well I'll be... You read my mind. You won.\n";
                sleep(2);
                cout << "\nMr. James: Here's your money.\n";
                sleep(2);
                money = money + bet * 2;
                cout << "\nMr. James gave you $" << bet * 2 << ".\n";
                cout << "\nYour new balance is $" << money << "\n";


                cout << "\nWant to play again? (Yes or No):";
                string userDecision2;
                cin >> userDecision2;

                for(char &c : userDecision2){
                    c = tolower(c);
                }

                if (userDecision2 == "no"){
                again = false;
                }

                else if (userDecision2 == "yes"){
                again = true;
                }
                else{
                    cout << "\nInvalid Answer. You're out of here buddy.\n";
                    again = false;
                }
            }

            else{
                int lossMessage;
                lossMessage = rand() % 3; // [0,2]
                if(lossMessage == 0){
                    cout << "\nMr. James: Not quite. Better luck next time champ.\n";
                }
                else if(lossMessage == 1){
                    cout << "\nMr. James: No sir. No sir. I'll be taking that now.\n";
                }
                else{
                    cout << "\nMr James: Not even close my friend. You sure you should be here?\n";
                }

                money = money - bet;
                cout << "\nYour new balance is $" << money << "\n";


                if(money <= 0){
                    cout << "\nMr. James: You're out of money. Time to leave.\n";
                    again = false;
                }
                else{
                    cout << "\nWant to play again? (Yes or No): ";
                    string playAgain;
                    cin >> playAgain;
                    for(char &c : playAgain){
                        c = tolower(c);
                    }
                    if(playAgain == "yes"){
                        again = true;
                    }
                    else{
                        again = false;
                    }
                }
                
            }
        }
        else{
            cout << "\nMr. James: Well then scram. I got paying customers waitin' for me.\n";
            again = false;

        }

    }
    leave(money);
}




int main() {
    double money = 0;
    srand(time(NULL)); //random seed gen

    
    cout << "\nVinny: Welcome to the Crawford Casino!\n";
    sleep(3);
    cout << "\nVinny: You know the deal, choose a number between 1 and 5.\n";
    sleep(2);
    cout << "\nVinny: If we guess the same number, you double your money.\n";
    sleep(2);
    cout << "\nVinny: You want to play? (Yes or No)\n";
    sleep(2);
    cout << "\nEnter your decision: ";
    
    string userDecision;
    cin >> userDecision;
    
    for(char &c : userDecision){
        c = tolower(c);
    }

    if(userDecision == "yes"){
        cout << "\nVinny: Right this way. Mr. James will take care of you!\n";
        sleep(2);
        cout << "\nVinny: Here is $100 to start to off on the house. Good luck! \n";
        sleep(2);
        money = 100; // Start game 1 with $100
        cout << "\nYour balance is now $100.\n";
        sleep(2);
        game(money);

    }
    else if(userDecision == "no"){
        cout << "\nVinny: Well then, see you next time!\n";
        leave(money);
    }

    else{
        cout << "\nAnswer was invalid\n";
        sleep(2);
        cout << "\nVinny: I'm not sure I follow. Would you like to play or not?\n";
        while((userDecision != "yes") && (userDecision != "no")){
            sleep(2);
            cout << "\nWould you like to play? (Yes or No):";

            cin >> userDecision;

            for(char &c : userDecision){
                c = tolower(c);
            }
        }

        if (userDecision == "yes"){
            cout << "\nVinny: Right this way. Mr. James will take care of you!\n";
            sleep(2);
            cout << "\nVinny: Here is $100 to start to off on the house. Good luck!\n";
            sleep(2);
            money = 100; 
            cout << "\nYour balance is now $100.\n";
            sleep(2);
            game(money);
        }
        else{
            leave(money);
        }
    }
}
// power ups
// 2x earnings, 5x, 10x
// get luckier (expand range) 2x, 5x
// double picks
// 1,000,000 buy the casino. You win!

// error handling:
// not a number for betting/guesses
// not in range for guesses
// show balance at the start of each round