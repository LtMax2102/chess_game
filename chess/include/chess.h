#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
template<typename T>
void printAOrV(T i){
    for(const auto& j : i){
        std::cout << j << ", ";
    }
    std::cout << "\n";
}
class chess {
    int count = 0, column, column2, letter = 1, rowInt, maxMovesY, maxMovesX, movement, blackPieces = 16, whitePieces = 16;
    char  row, buffer;
    char* selection;
    char* destination;
    std::string input, placeHolder;
    std::map<char, std::string> pieces = {{'R', "Rook"}, {'H', "Horse"},{'B', "Bishop"},{'Q', "Queen"},{'K', "King"},{'P', "Pawn"},{'r', "Rook"}, {'h', "Horse"},{'b', "Bishop"},{'q', "Queen"},{'k', "King"},{'p', "Pawn"}};
    std::vector<std::string> validYMoves;    std::vector<std::string> validXMoves;

    std::array<char,8> alpha = {'A','B','C','D','E','F','G','H'};
    char board[8][8] = {{'r','h','b','q','k','b','h','r'},
                        {'p','p','p','p','p','p','p','p'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'P','P','P','P','P','P','P','P'},
                        {'R','H','B','K','Q','B','H','R'}};
    // Board for testing pieces
//    char board[8][8] = {{'-','-','-','-','r','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','R','-','-','-'},
//                        {'-','-','-','-','R','-','-','-'}};

    // Prints the board
    void printBoard(){
        std::cout << "A: ";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(count == 8){
                    std::cout << "\n" << alpha[letter] << ": ";
                    count = 0;
                    letter++;
                }
                std::cout << board[i][j] << "";
                count += 1;
            }
        }
        letter = 1;
        count = 0;
        std::cout << "\n  ";

        for(int i = 0; i < 8; i++){
            std::cout << "" << i+1;
        }
        std::cout << std::endl;
    }
    // Checks to make sure that the chosen letter was within the allowed ones
    bool checker(char &c){
        for(unsigned i = 0; i < alpha.size(); i++){
            if(c == alpha[i]){
                return true;
            }
            continue;
        }
        return false;
    }
    // Takes input as argument and makes sure that it's two long
    bool checkAndBreak(std::string &str){
        if(str.size() > 2){std::cout << "Input must be a length of 2\n\n";return false;}

        row = str[0];

        column = static_cast<int>(str[1] - 48);
        if(checker(row) == false){
            std::cout << "Invalid letter entered\n\n";
            return false;
        }
        else if(column > 8 || column < 1){
            std::cout << "Invalid number entered\n";
            return false;
        }
        printf("Row %c Column %d Selected\n", row, column);
        return true;
    }

    // Takes the row and converts the character into a number, then sets the selection to the board of both the rowInt and the column then sets the max moves this piece has
    int getSelection(){
            switch(row){
        case 'A':
        case 'a':
            return 0;
            break;
        case 'B':
        case 'b':
            return 1;
            break;
        case 'C':
        case 'c':
            return 2;
            break;
        case 'D':
        case 'd':
            return 3;
            break;
        case 'E':
        case 'e':
            return 4;
            break;
        case 'F':
        case 'f':
            return 5;
            break;
        case 'G':
        case 'g':
            return 6;
            break;
        case 'H':
        case 'h':
            return 7;
            break;
        default:
            std::cout << "Letter is not Valid\n";
            return 8;
            break;
        }

    }
    // Might need to add a movement selection so that it changes depending on the piece
    void setMoveAmount(){
        selection = &board[rowInt][column-1];
        switch(*selection){
        case 'p':
        case 'P':
            maxMovesX = 0;
            maxMovesY = 1;
            break;
        case 'r':
        case 'R':
            maxMovesX = 8;
            maxMovesY = 8;
            break;
//        case 'r':
//        case 'R':
//            maxMovesX = 8;
//            maxMovesY = 8;
//            break;
//        case 'r':
//        case 'R':
//            maxMovesX = 8;
//            maxMovesY = 8;
//            break;
        default:
            maxMovesX = 0;
            maxMovesY = 0;
            std::cout << "Selection is invalid\n";
        }
    }
    void movePiece(){
//        std::cout << "Before move: " << *selection << "\n";
//        std::cout << "After move: " << board[rowInt+maxMovesY][(column-1) + maxMovesX] << "\n";
        if(*selection == '-'){
            return;
        }


        std::cout << "You have selected the " << pieces[*selection] << "\n";
        std::cout << "This has a maximum X move of " << maxMovesX << " and a maximum Y move of " << maxMovesY << "\n";

        // For uppercase characters
        if(isupper(*selection)){
            // Checks along the Y axis for positions that are equal to -, going up on the axis
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt-i][column-1] == '-'){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt-i][column-1])){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the Y axis for positions that are equal to -, going down on the axis
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt+i][column-1] == '-'){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }

            // Checks along the X axis for positions that are equal to -, going left on the axis
            for(int i = 1; i <= maxMovesX; i++){
                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }
        }
        // For lowercase characters
        if(islower(*selection)){
            // Checks along the Y axis for positions that are equal to -, going up on the axis
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt-i][column-1] == '-'){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt-i][column-1])){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the Y axis for positions that are equal to -, going down on the axis
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt+i][column-1] == '-'){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt+i][column-1])){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }

            // Checks along the X axis for positions that are equal to -, going left on the axis
            for(int i = 1; i <= maxMovesX; i++){
                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }
        }

        // Print all valid moves in vectors
        std::cout << "Printing valid moves: \n Y: ";
        printAOrV(validYMoves);
        std::cout << " X: ";
        printAOrV(validXMoves);

        // Used to count how many moves have been looked at in the vector later
        unsigned counts = 1;
        // Used later to make sure that only one of the lanes are selected, and that if one is selected the other doesn't conflict with it
        bool pass = false;

        std::cout << "\n";
        // Used to store the users inputted move
        std::string input2;

        std::cout << "Choose move: ";
        std::getline(std::cin, input2);
        // Looks through the moves and checks to see if they are in the move list, if true will change pass to true so that the other axis isn't checked otherwise will break and allow other axis check to happen

        // Not working needs to be fixed !!!!!!!!!!!
        for(const auto& i : validYMoves){
            if(i == input2){
                pass = true;
                break;
            }
            else if(counts == validYMoves.size()){
                break;
            }
            counts += 1;
            continue;
        }
        counts = 1;
        // Only happens if pass isn't true
        if(pass != true){
            // Checks the other axis to see if move is in there, if it's not found then it will declare that the move isn't in the vector and clear them before leaving the program
            for(const auto& i : validXMoves){
                if(i == input2){
                    break;
                }
                else if(counts == validXMoves.size()){
                    std::cout << "Move was not in list\n";
                    validXMoves.clear();
                    validYMoves.clear();
                    return;
                }
                counts += 1;
                continue;
            }
        }

        // Sets row equal to the input letter
        row = input2[0];
        // Sets column to to be equal to correct number
        column2 = input2[1] - 48;
        // Sets destination to the chosen move in the list
        destination = &board[getSelection()][column2-1];
        if(*destination != '-' && isupper(*destination)){
            *destination = '-';
            blackPieces--;
        }
        else if(*destination != '-' && islower(*destination)){
            *destination = '-';
            whitePieces--;
        }
        // Holds value of destination
        buffer = *destination;
        // Sets destination to be the selected piece
        *destination = *selection;
        // Sets the selection position to be equal to the value held in the buffer
        *selection = buffer;
        // Clears the valid moves so that it can be refilled next time
        validYMoves.clear();
        validXMoves.clear();

    }
public:
    void beginGame(){
        bool end = true;
        // Gives users instructions
        std::cout << "Enter you choice of piece in the following way\nLetter then number e.g B1, C4, H8\n";
        // Begins the game loop, will happen until someone has lost
        while(end == true){
            // Prints the board
            printBoard();
            std::cout << "Choose Row and Column: ";
            std::getline(std::cin, input);
            // Uses the check and break function to check the input, if it returns false will force the thread to sleep and then continue and ask for a move again
            if(checkAndBreak(input) == false){
                // Sleeps thread
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                continue;
            }
            // Sets the rowInt to the correct number based on the selected row
            rowInt = getSelection();
            // if the rowInt is set to 8 by the function it will then continue and ask for a move again
            if(rowInt == 8){continue;}
            // Uses the setMoveAmount function to set the move amount depending on the inputted piece
            setMoveAmount();
            // Moves the piece
            movePiece();
            // Sleeps the thread for 2000 milliseconds (2 secs)
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

    }


    chess();
    ~chess();
};







// Could make another chess board where all the pieces are classes and it changes what they do depending on what piece it is, would probably work better than this one lmao



//Hey I thought you looked cute in your profile picture so I decided to send you a friend request. Add me if you want to discuss trading lego instructions because I got some pretty rare ones baby
#endif // CHESS_H
