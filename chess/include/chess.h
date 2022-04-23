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
    int count = 0, column, letter = 1, rowInt, maxMovesY, maxMovesX, movement;
    char selection, row;
    std::string input;
    std::map<char, std::string> pieces = {{'R', "Rook"}, {'H', "Horse"},{'B', "Bishop"},{'Q', "Queen"},{'K', "King"},{'P', "Pawn"}};
    std::vector<std::string> validMoves;
    std::array<char,8> alpha = {'A','B','C','D','E','F','G','H'};
    char board[8][8] = {{'R','H','B','Q','K','B','H','R'},
                        {'P','P','P','P','P','P','P','P'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'P','P','P','P','P','P','P','P'},
                        {'R','H','B','K','Q','B','H','R'}};


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
        for(int i = 0; i < alpha.size(); i++){
            if(c == alpha[i]){
                return true;
            }
            continue;
        }
        return false;
    }
    bool checkAndBreak(std::string &str){
        if(str.size() > 2){std::cout << "Input must be a length of 2\n\n";return false;}
        row = str[0];
        column = static_cast<int>(str[1]) - 48;
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
    void getSelection(){
            switch(row){
        case 'A':
            rowInt = 0;
            break;
        case 'B':
            rowInt = 1;
            break;
        case 'C':
            rowInt = 2;
            break;
        case 'D':
            rowInt = 3;
            break;
        case 'E':
            rowInt = 4;
            break;
        case 'F':
            rowInt = 5;
            break;
        case 'G':
            rowInt = 6;
            break;
        case 'H':
            rowInt = 7;
            break;
        default:
            std::cout << "Letter is not Valid\n";
        }
        selection = board[rowInt][column-1];
        switch(selection){
        case 'P':
            maxMovesX = 0;
            maxMovesY = 1;
            break;

        }
    }
    void movePiece(){
        board[rowInt+maxMovesX][(column-1) + maxMovesY];
        // calculate all the moves that can be done and add them to the move vector, then show the player these moves

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
            getSelection();
            std::cout << "You have selected the " << pieces[selection] << "\n";
            std::cout << "This has a maximum X move of " << maxMovesX << " and a maximum Y move of " << maxMovesY << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        }

    }


    chess();
    ~chess();
};











//Hey I thought you looked cute in your profile picture so I decided to send you a friend request. Add me if you want to discuss trading lego instructions because I got some pretty rare ones baby
#endif // CHESS_H
