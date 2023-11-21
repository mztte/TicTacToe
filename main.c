//Author: Matt Briggs
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char checkWin();
int getEmptySpaces();
void printBoard();
int processInput(char [], char);


char gameboard[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '}};


int main() {
    char input[4];
    const char exit[4] = "ext";
    char turn = 'X';
    char winner;
    printf("\nTic-Tac-Toe\n\n\ttype in \"ext\" to exit at any time\n\n");

    while( (checkWin() == ' ' && getEmptySpaces() != 0) ) {
        printBoard();

        printf("\nPlayer %c's turn. Enter a position (1-1 to 3-3): ", turn);
        fgets(input, 4, stdin);
        getchar(); //clears \n input buffer

        if(strncmp(input, exit, 3) == 0) { break; } //check if ext was typed

        //if input is invalid exit program
        if(processInput(input, turn) == 1) { break; }
        turn == 'X' ? (turn = 'O') : (turn = 'X');
    }

    //display winner or tie once game is over
    winner = checkWin();

    if(winner != ' ') {
        printBoard();
        printf("\n**** Player %c WINS! ****\n", winner);
    } else if(getEmptySpaces() == 0) {
        printBoard();
        printf("\n**** Tie! ****\n");
    } else {
        printf("\nExiting game...\n");
    }

    return 0;
}

char checkWin() {
    int xRowCount; //X row count
    int xColCount; //X column count
    int oRowCount;
    int oColCount;

    //check diagonally
    char center = gameboard[1][1];
    if( ((gameboard[0][0] == gameboard[2][2]) && (gameboard[0][0] == center)) || ((gameboard[2][0] == gameboard[0][2]) && (gameboard[2][0] == center))) {
        return center;
    }
    
    //check orthogonally
    for(int i = 0; i < sizeof(gameboard)/sizeof(gameboard[0]); i++) {
        xRowCount = 0;
        xColCount = 0;
        oRowCount = 0;
        oColCount = 0;

        for(int j = 0; j < sizeof(gameboard[0])/sizeof(gameboard[0][0]); j++) {
            //check X's
            if(gameboard[i][j] == 'X') { xRowCount++; }
            if(gameboard[j][i] == 'X') { xColCount++; }

            //check O's
            if(gameboard[i][j] == 'O') { oRowCount++; }
            if(gameboard[j][i] == 'O') { oColCount++; }
        }
        //check if either a row or column has 3 X's or O's
        if(xRowCount == 3 || xColCount == 3) { return 'X'; }
        if(oRowCount == 3 || oColCount == 3) { return 'O'; }
    }

    return ' ';
}
int getEmptySpaces() {
    int emptySpaces = 9;
    for(int i = 0; i < sizeof(gameboard)/sizeof(gameboard[0]); i++) {
        for(int j = 0; j < sizeof(gameboard[0])/sizeof(gameboard[0][0]); j++) {
            if(gameboard[i][j] != ' ') {
                emptySpaces--;
            }
        }
    }
    return emptySpaces;
}
void printBoard() {
    //show the user where every space is located at start of game
    if(getEmptySpaces() == 9) {
        printf("\nBoard is empty. Positions are shown:\n\n");
        for(int i = 0; i < sizeof(gameboard)/sizeof(gameboard[0]); i++) {
            for(int j = 0; j < sizeof(gameboard[0])/sizeof(gameboard[0][0]); j++) {
                printf("  %d-%d ", (i+1), (j+1));
            }
            if(i < 2) {
                printf("\n|-----|-----|-----|\n");
            }
        }
        printf("\n");
    } else {
        //print out gameboard
        printf("\n");
        for(int i = 0; i < sizeof(gameboard)/sizeof(gameboard[0]); i++) {
            for(int j = 0; j < sizeof(gameboard[0])/sizeof(gameboard[0][0]); j++) {
                printf("   %c  ", gameboard[i][j]);
            }
            if(i < 2) {
                printf("\n|-----|-----|-----|\n");
            }
        }
        printf("\n");
    }
}
int processInput(char input[], char turn) {
    int indexes[2] = { (int) input[0], (int) input[2]};
    int isSuccess;
    //ASCII digits start at 48, subtract 1 more because user input starts at 1-1 not 0-0
    indexes[0] = abs(indexes[0] - 49); //48 + 1
    indexes[1] = abs(indexes[1] - 49);

    //check if valid input
    if( (input[1] == '-') && (indexes[0] <= 2) && (indexes[1] <=2) && (gameboard[indexes[0]][indexes[1]] == ' ') ) {
        //put the turn in the selected spot on board
        gameboard[indexes[0]][indexes[1]] = turn;

        isSuccess = 0;
    } else {
        //error handling
        printf("\nERROR: INVALID INPUT");
        isSuccess = 1;
    }
    return isSuccess;
}