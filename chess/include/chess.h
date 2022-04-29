#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>
class chess {
    int count = 0, column, column2, letter = 1, rowInt, maxMovesY, maxMovesX, movement;
    char  row, buffer;
    char* selection;
    char* destination;
    std::string input, placeHolder;
    std::map<char, std::string> pieces = {{'R', "Rook"}, {'H', "Horse"},{'B', "Bishop"},{'Q', "Queen"},{'K', "King"},{'P', "Pawn"},{'r', "Rook"}, {'h', "Horse"},{'b', "Bishop"},{'q', "Queen"},{'k', "King"},{'p', "Pawn"}};
    std::vector<std::string> validYMoves;
    std::array<char,8> alpha = {'A','B','C','D','E','F','G','H'};
//    char board[8][8] = {{'r','h','b','q','k','b','h','r'},
//                        {'p','p','p','p','p','p','p','p'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'P','P','P','P','P','P','P','P'},
//                        {'R','H','B','K','Q','B','H','R'}};
    // Board for testing pieces
    char board[8][8] = {{'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','R','-','-','-'}};


    void printBoard(){
        std::cout << "A: ";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(count == 8){
                    std::cout << "\n" << alpha[letter] << ": ";
                    count = 0;
                    letter++;
                }
                std::cout << board[i][j] << " ";
                count += 1;
            }
        }
        letter = 1;
        count = 0;
        std::cout << "\n  ";

        for(int i = 0; i < 8; i++){
            std::cout << " " << i+1;
        }
        std::cout << std::endl;
    }
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
//        if(isupper(*selection)){
//            // If selection is uppercase
//            for(int i = 1; i <= maxMovesY; i++){
//                if(board[rowInt-i][column-1] == '-'){
//                    placeHolder.push_back(alpha[rowInt-i]);
//                    placeHolder.push_back(input[1]);
//                    validYMoves.push_back(placeHolder);
//                    placeHolder.clear();
//                    continue;
//                }
//                break;
//            }
//        }
//        else{
//            // If selection is lowercase
//            for(int i = 1; i <=  maxMovesY; i++){
//                if(board[rowInt+i][column-1] == '-'){
//                    placeHolder.push_back(alpha[rowInt+i]);
//                    placeHolder.push_back(input[1]);
//                    validYMoves.push_back(placeHolder);
//                    placeHolder.clear();
//                    continue;
//                }
//                break;
//            }
//        }

            std::cout << rowInt << "\n";
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt-i][column-1] == '-'){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back(input[1]);
                    validYMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                break;
            }
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

        // Print all valid moves in vector
        std::cout << "Printing valid moves: \n Y: ";
        for(const auto& i : validYMoves){
            std::cout << i << ", ";
        }
        unsigned counts = 1;
        std::cout << "\n";
        std::string input2;
        std::cout << "Choose move: ";
        std::getline(std::cin, input2);
        for(const auto& i : validYMoves){
            if(i == input2){
                break;
            }
            else if(counts == validYMoves.size()){
                std::cout << "Move was not in list\n";
                validYMoves.clear();
                return;
            }
            counts += 1;
            continue;
        }

        // Sets row equal to the input letter
        row = input2[0];
        // Sets column to to be equal to correct number
        column2 = input2[1] - 48;
        // Sets destination to the chosen move in the list
        destination = &board[getSelection()][column2-1];

        // Holds value of destination
        buffer = *destination;
        // Sets destination to be the selected piece
        *destination = *selection;
        // Sets the selection position to be equal to the value held in the buffer
        *selection = buffer;
        // Clears the valid moves so that it can be refilled next time
        validYMoves.clear();

    }
public:
    void beginGame(){
        bool end = true;
        std::cout << "Enter you choice of piece in the following way\nLetter then number e.g B1, C4, H8\n";
        while(end == true){
            printBoard();
            std::cout << "Choose Row and Column: ";
            std::getline(std::cin, input);
            if(checkAndBreak(input) == false){
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                continue;
            }
            rowInt = getSelection();
            if(rowInt == 8){continue;}
            setMoveAmount();
            movePiece();
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

    }


    chess();
    ~chess();
};











//Hey I thought you looked cute in your profile picture so I decided to send you a friend request. Add me if you want to discuss trading lego instructions because I got some pretty rare ones baby
#endif // CHESS_H
