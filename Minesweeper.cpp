#include <iostream>
#include <cstdlib>  // rand()
#include <vector>
#include <cmath>
#include <utility>
#include <string>
#include <ctime>    
#include <chrono>
#include <thread>



const int board = 9;
const int bombs = 10;

using namespace std;




void sleep(int seconds){ // just make the code less cluttered
    this_thread::sleep_for(chrono::seconds(seconds));
}



void print(int mat[board][board]){
    cout << "\nMinesweeper Board:\n" << "\n";
    for(int i = 0; i < board; i++){
        for(int j = 0; j < board; j++){
            cout << mat[i][j] << " ";
        }
        cout << "\n"; 
    }
    cout << "\n"; 
}


bool check(int row, int col, int bombLocations[bombs][2]){ 
    for(int i = 0; i < bombs; i++){
        int loc1 = bombLocations[i][0];
        int loc2 = bombLocations[i][1];

        if((row == loc1) && (col == loc2)){
            cout << "\nBomb Detected! Game Over...\n";
            return true;
        }
    }
    cout << "\nNo Bomb Detected\n";
    return false;
}



pair<int, int> start(){
    string guess;
    while (true) {
        cout << "\nEnter the coordinates you would like to start at: (row,col)\n";
        cin >> guess;
        
        int row = guess[0] - '0';  //ASCII values. ASCII 48 = "0"
        int col = guess[2] - '0';  
        
        if((row <= 0 || row > board) || (col <= 0 || col > board)) {
            cout << "\nInvalid Choice. Please try again (1-9)\n";
            sleep(1);
            continue;
        }
        row--;  // 1-9 becomes 0-8
        col--;
        return {row, col}; //this part
    }
}



int init(int bombLocations[bombs][2], int safeRow, int safeCol) {
    for(int i = 0; i < bombs; i++) {
        int row, col;
        bool inSafeZone;
        
        do {
            row = rand() % board;
            col = rand() % board;
            
            // Check if in plus-shaped safe zone
            inSafeZone = false;
            
            // Center cell
            if(row == safeRow && col == safeCol) {
                inSafeZone = true;
            }
            // Up
            else if(row == safeRow-1 && col == safeCol) {
                inSafeZone = true;
            }
            // Down
            else if(row == safeRow+1 && col == safeCol) {
                inSafeZone = true;
            }
            // Left
            else if(row == safeRow && col == safeCol-1) {
                inSafeZone = true;
            }
            // Right
            else if(row == safeRow && col == safeCol+1) {
                inSafeZone = true;
            }
            
        } while (inSafeZone);  // Keep trying if in safe zone
        
        bombLocations[i][0] = row;
        bombLocations[i][1] = col;
    }
    return 0;
}



void adj(int mat[board][board], int bombLocations[bombs][2]){
    int countMat[board][board] = {0};
    for(int i = 0; i < board; i++){
        for(int j = 0; j < board; j++){
            int count = 0;
            for(int k = 0; k < bombs; k++){

                if((abs(i-bombLocations[k][0]) <= 1) &&
                   (abs(j-bombLocations[k][1]) <= 1) &&
                  !(i == bombLocations[k][0] && j == bombLocations[k][1])){
                    count++;
                }
            }
            mat[i][j] = count;  // Update the board
        }
    }
}



pair<int, int> userInput() {
    string guess;
    while (true) {
        cout << "\nEnter coordinates to check (row,col): ";
        cin >> guess;
        
        int row = guess[0] - '0'; //ASCII values. ASCII 48 = "0"
        int col = guess[2] - '0';
        
        if((row <= 0 || row > board) || (col <= 0 || col > board)) {
            cout << "Invalid! Use 1-9\n";
            continue;
        }
        
        row--;  // Convert to 0-based
        col--;
        return {row, col};
    }
}



int main() {
    srand(time(0));
    
    // Game boards
    int display[board][board];        // What player sees
    bool shown[board][board] = {false}; // Track shown cells
    int bombLoc[bombs][2];            // Bomb positions
    int counts[board][board];         // Bomb counts
    
    // Setup: all hidden (-2)
    for(int i = 0; i < board; i++)
        for(int j = 0; j < board; j++)
            display[i][j] = -2;
    
    cout << "=== MINESWEEPER ===\n";
    
    // 1. Get safe start
    auto [safeR, safeC] = start();
    shown[safeR][safeC] = true;
    
    // 2. Place bombs
    init(bombLoc, safeR, safeC);
    
    // 3. Calculate numbers
    adj(counts, bombLoc);
    display[safeR][safeC] = counts[safeR][safeC];
    
    // 4. Game loop
    bool gameOver = false;
    int revealed = 1;
    
    while(!gameOver && revealed < board*board - bombs) {
        // Show board
        cout << "\nBoard:\n";
        for(int i = 0; i < board; i++) {
            for(int j = 0; j < board; j++) {
                if(shown[i][j]) cout << display[i][j] << " ";
                else cout << ". ";
            }
            cout << endl;
        }
        
        // Get guess
        auto [r, c] = userInput();
        
        if(shown[r][c]) {
            cout << "Already shown!\n";
            continue;
        }
        
        // Check bomb
        if(check(r, c, bombLoc)) {
            cout << "BOOM! Game Over.\n";
            gameOver = true;
        } else {
            // Safe - reveal
            shown[r][c] = true;
            display[r][c] = counts[r][c];
            revealed++;
            cout << "Safe. " << counts[r][c] << " bomb(s) nearby.\n";
        }
    }
    
    // Win check
    if(!gameOver) {
        cout << "\nYOU WIN!\n";
    }
    
    return 0;
}


