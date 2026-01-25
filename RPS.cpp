#include <iostream>
#include <cmath>


using namespace std;


int main() {
    // Start
    cout << "\nWelcome to the game of Rock, Paper, Scissors\n";


    // Waiting for player 1 response
    string player1;

    while(player1.empty()){
        cout << "\nPlayer 1, please enter Rock, Paper, or Scissors: \n";
        cin >> player1;

        // Set to lower case
        for(char &c : player1){
            c = tolower(c);

        }

        if(player1 != "rock" && player1 != "paper" && player1 != "scissors"){ 
            cout << "\nInvalid input. Please try again.\n";
            player1.clear();
        }

        if(player1 == "rock" || player1 == "paper" || player1 == "scissors"){ 
            break;
        }

    }


    // Waiting for player 2 response
    string player2;

    while(player2.empty()){
        cout << "\nPlayer 2, please enter Rock, Paper, or Scissors: \n";
        cin >> player2;


        // Set to lower case
        for(char &c : player2){
            c = tolower(c);

        }

        if(player2 != "rock" && player2 != "paper" && player2 != "scissors"){ 
            cout << "\nInvalid input. Please try again.\n";
            player2.clear();
        }

        if(player2 == "rock" || player2 == "paper" || player2 == "scissors"){ 
            break;
        }

    }
    

    // Outcomes
    if((player1 == "rock" && player2 == "scissors") || (player1 == "scissors" && player2 == "paper") || (player1 == "paper" && player2 == "rock") ){
            cout << "\nPlayer 1 wins!\n";
    }

    else if((player2 == "rock" && player1 == "scissors") || (player2 == "scissors" && player1 == "paper") || (player2 == "paper" && player1 == "rock") ){
            cout << "\nPlayer 2 wins!\n";
    }

    else{
        cout << "\nIt is a tie!\n";
    }


    return 0;
}



