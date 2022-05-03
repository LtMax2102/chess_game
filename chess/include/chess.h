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
    int count = 0, column, column2, letter = 1, rowInt, maxMovesY, maxMovesX, movement, blackPieces, whitePieces;
    char  row, buffer;
    char* selection;
    char* destination;
    bool blackTurn = false, whiteTurn = true, end = true;
    std::string input, placeHolder;
    std::map<char, std::string> pieces = {{'R', "Rook"}, {'H', "Horse"},{'B', "Bishop"},{'Q', "Queen"},{'K', "King"},{'P', "Pawn"},{'r', "Rook"}, {'h', "Horse"},{'b', "Bishop"},{'q', "Queen"},{'k', "King"},{'p', "Pawn"}};
    std::vector<std::string> validYMoves;    std::vector<std::string> validXMoves;
    std::vector<std::string> allMoves;

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
//    char board[8][8] = {{'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','-','p','-','-','-'},
//                        {'-','-','-','P','-','P','-','-'},
//                        {'-','-','-','-','-','-','-','-'},
//                        {'-','-','-','p','-','p','-','-'},
//                        {'-','-','-','-','P','-','-','-'},
//                        {'-','-','-','-','-','-','-','-'}};

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
        case 'b':
        case 'B':
            maxMovesX = 8;
            maxMovesY = 8;
            break;
        case 'h':
        case 'H':
            maxMovesX = 1;
            maxMovesY = 1;
            break;
        case 'q':
        case 'Q':
            maxMovesX = 8;
            maxMovesY = 8;
            break;
        case 'k':
        case 'K':
            maxMovesX = 1;
            maxMovesY = 1;
            break;
        default:
            maxMovesX = 0;
            maxMovesY = 0;
            std::cout << "Selection is invalid\n";
        }
    }

    void countPieces(){
        blackPieces = 0;
        whitePieces = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(islower(board[i][j])){
                    blackPieces += 1;
                }
                else if(isupper(board[i][j])){
                    whitePieces += 1;
                }
            }
        }
        if(blackPieces == 0 || whitePieces == 0){
            end = false;
            return;
        }
        std::cout << "White: " << whitePieces
                  << "\nBlack: " << blackPieces << "\n";
    }


    void setMovement(){
        switch(*selection){

        case 'R':
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
                else if(islower(board[rowInt+i][column-1])){
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            break;

        case 'r':
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            break;

        case 'b':
            // Checks the row up one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;

        case 'B':
            // Checks the row up one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;

        case 'h':
            // Does loads of if statements to see if the row is empty, could be done more efficiently but I can't be asked right now
            // Look below horse both left and right
            // Right
            if(board[rowInt+2][column] == '-' && (rowInt+2) <= 8 && (column) < 8){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt+2][column]) && (rowInt+2) <= 8 && (column) < 8){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Left
            if(board[rowInt+2][column-2] == '-' && (rowInt+2) <= 8 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt+2][column-2]) && (rowInt+2) <= 8 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Look up then both left and right
            // Right
            if(board[rowInt-2][column] == '-' && (rowInt-2) >= 0 && (column) < 8){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt-2][column]) && (rowInt-2) >= 0 && (column) < 8){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Left
            if(board[rowInt-2][column-2] == '-' && (rowInt-2) >= 0 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt-2][column-2]) && (rowInt-2) >= 0 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Looking at left side of horse both up and down
            // Down
            if(board[rowInt+1][column-3] == '-' && (rowInt+1) <= 8 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt+1][column-3]) && (rowInt+1) <= 8 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Up
            if(board[rowInt-1][column-3] == '-' && (rowInt-1) >= 0 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt-1][column-3]) && (rowInt-1) >= 0 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Look right and then up and down
            // Down
            if(board[rowInt+1][column+1] == '-' && (rowInt+1) <= 8 && (column+1) <= 8){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt+1][column+1]) && (rowInt+1) <= 8 && (column+1) <= 8){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Up
            if(board[rowInt-1][column+1] == '-' && (rowInt-1) >= 0 && (column+1) <= 8){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(isupper(board[rowInt-1][column+1]) && (rowInt-1) >= 0 && (column+1) <= 8){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            break;

        case 'H':
            // Does loads of if statements to see if the row is empty, could be done more efficiently but I can't be asked right now
            // Look below horse both left and right
            // Right
            if(board[rowInt+2][column] == '-' && (rowInt+2) <= 8 && (column) < 8){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt+2][column]) && (rowInt+2) <= 8 && (column) < 8){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Left
            if(board[rowInt+2][column-2] == '-' && (rowInt+2) <= 8 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt+2][column-2]) && (rowInt+2) <= 8 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt+2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Look up then both left and right
            // Right
            if(board[rowInt-2][column] == '-' && (rowInt-2) >= 0 && (column) < 8){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt-2][column]) && (rowInt-2) >= 0 && (column) < 8){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)+1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Left
            if(board[rowInt-2][column-2] == '-' && (rowInt-2) >= 0 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt-2][column-2]) && (rowInt-2) >= 0 && (column-2) >= 0){
                placeHolder.push_back(alpha[rowInt-2]);
                placeHolder.push_back((column+48)-1);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Looking at left side of horse both up and down
            // Down
            if(board[rowInt+1][column-3] == '-' && (rowInt+1) <= 8 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt+1][column-3]) && (rowInt+1) <= 8 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Up
            if(board[rowInt-1][column-3] == '-' && (rowInt-1) >= 0 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt-1][column-3]) && (rowInt-1) >= 0 && (column-3) >= 0){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)-2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Look right and then up and down
            // Down
            if(board[rowInt+1][column+1] == '-' && (rowInt+1) <= 8 && (column+1) < 8){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt+1][column+1]) && (rowInt+1) <= 8 && (column+1) < 8){
                placeHolder.push_back(alpha[rowInt+1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            // Up
            if(board[rowInt-1][column+1] == '-' && (rowInt-1) >= 0 && (column+1) < 8){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            else if(islower(board[rowInt-1][column+1]) && (rowInt-1) >= 0 && (column+1) < 8){
                placeHolder.push_back(alpha[rowInt-1]);
                placeHolder.push_back((column+48)+2);
                allMoves.push_back(placeHolder);
                placeHolder.clear();
            }
            break;

        case 'q':
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks the row up one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;

        case 'Q':
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
                else if(islower(board[rowInt+i][column-1])){
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks the row up one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 8; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;

        case 'k':
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(isupper(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            for(int i = 1; i <= 1; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(isupper(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;
        case 'K':
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
                else if(islower(board[rowInt+i][column-1])){
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
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)-i] == '-' && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)-i]) && column-i > 0){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)-i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
                break;
            }
            // Checks along the X axis for positions that are equal to -, going right on the axis
            for(int i = 1; i <= maxMovesX; i++){
//                std::cout << "Row Int: " << rowInt << "\n";
                if(board[rowInt][(column-1)+i] == '-' && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    continue;
                }
                else if(islower(board[rowInt][(column-1)+i]) && column+i <= 8){
                    placeHolder.push_back(alpha[rowInt]);
                    placeHolder.push_back((column+48)+i);
                    validXMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            for(int i = 1; i <= 1; i++){
                if(board[rowInt-i][column-i] == '-' && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column-i]) && (column-i) > 0 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt+i][column+i] == '-' && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column+i]) && (column+i) <= 8 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row down one and column left one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt+i][column-i] == '-' && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt+i][column-i]) && (column-i) > 0 && (rowInt+i) <= 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            // Checks the row up one and column right one until it reaches another piece or the end of the loop
            for(int i = 1; i <= 1; i++){
                if(board[rowInt-i][column+i] == '-' && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                else if(islower(board[rowInt-i][column+i]) && (column+i) <= 8 && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+i);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                    break;
                }
            }
            break;
        case 'p':
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt+i][column-1] == '-' && (rowInt+i) < 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48));
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                if(isupper(board[rowInt+i][column]) && column < 8){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)+1);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                if(isupper(board[rowInt+i][column-2]) && (column-2) >= 0){
                    placeHolder.push_back(alpha[rowInt+i]);
                    placeHolder.push_back((column+48)-1);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
            }
            break;
        case 'P':
            for(int i = 1; i <= maxMovesY; i++){
                if(board[rowInt-i][column-1] == '-' && (rowInt-i) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48));
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                if(islower(board[rowInt-i][column]) && column < 8){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)+1);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
                if(islower(board[rowInt-i][column-2]) && (column-2) >= 0){
                    placeHolder.push_back(alpha[rowInt-i]);
                    placeHolder.push_back((column+48)-1);
                    allMoves.push_back(placeHolder);
                    placeHolder.clear();
                }
            }
            break;
        }
    }


    void movePiece(){
        // Checks to see if the selection is a - in which they would need to then change their selection
        if(*selection == '-'){
            if(whiteTurn == true){
                whiteTurn = false;
                blackTurn = true;
            }
            else{
                whiteTurn = true;
                blackTurn = false;
            }
            return;
        }


        std::cout << "You have selected the " << pieces[*selection] << "\n";
        std::cout << "This has a horizontal move of " << maxMovesX << " and a vertical move of " << maxMovesY << "\n";

        // Uses the set movement function
        setMovement();
        // Fills the allMoves vector so that it can be looked through later
        for(const auto& i : validXMoves){
            allMoves.push_back(i);
        }
        for(const auto& i : validYMoves){
            allMoves.push_back(i);
        }
        // Checks to see if the all moves is empty, if it's empty say that there's no selections and give the player their turn back
        if(allMoves.size() == 0){
            std::cout << "No moves available\n";
            if(whiteTurn == true){
                whiteTurn = false;
                blackTurn = true;
            }
            else{
                whiteTurn = true;
                blackTurn = false;
            }
            return;
        }

        // Print all valid moves in vectors
        std::cout << "Printing valid moves: \n";
        // If y is empty it doesn't need to be printed
        if(validYMoves.size() != 0){
            std::cout << "\n Y: ";
            printAOrV(validYMoves);
        }
        // If x is empty it doesn't need to be printed
        if(validXMoves.size() != 0){
            std::cout << "\n X: ";
            printAOrV(validXMoves);
        }
        // If both are empty it could mean that the piece doesn't use that vector for it's movement
        if(allMoves.size() != 0){
            std::cout << "\nAll Moves Possible\n ";
            printAOrV(allMoves);
        }



        // Used to count how many moves have been looked at in the vector later
        unsigned counts = 1;

        std::cout << "\n";
        // Used to store the users inputted move
        std::string input2;

        std::cout << "Choose move: ";
        std::getline(std::cin, input2);


        // Adds all available moves to the all moves vector
//        std::cout << "All moves size " << allMoves.size() << "\n";
        for(const auto& i : allMoves){
            if(i == input2){
                break;
            }
            else if(counts == allMoves.size()){
                std::cout << "Move was not in list\n";
                validXMoves.clear();
                validYMoves.clear();
                allMoves.clear();
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
        // If the destination is not - but is upper then change it to empty to show that the player has lost a piece
        if(*destination != '-' && isupper(*destination)){
            std::cout << "White loses a " << pieces[*destination] << "\n";
            *destination = '-';
        }
        // If the destination is not - but is lower then change it to empty to show that the player has lost a piece
        else if(*destination != '-' && islower(*destination)){
            std::cout << "Black loses a " << pieces[*destination] << "\n";
            *destination = '-';
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
        allMoves.clear();

    }
public:
    // Begins the main game sequence
    void beginGame(){
        // Gives users instructions ACTIVATE BEFORE ACTUAL USE, DISABLED FOR TESTING BECAUSE I CAN'T BE ASKED TO WAIT ALL THE TIME

        std::cout << "Enter you choice of piece in the following way\nLetter then number e.g B1, C4, H8\n";
        std::cout << "White is uppercase and black is lowercase\nWhite moves first\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        // Begins the game loop, will happen until someone has lost
        while(end == true){
            // Prints the board
            printBoard();
            countPieces();
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
            // Checks to see if the selection is upper and that it's whites turn
            if(isupper(*selection) && whiteTurn == true){
                whiteTurn = false;
                blackTurn = true;
                movePiece();
            }
            // Otherwise checks to see if it's blacks turn and if the selection is lower
            else if(islower(*selection) && blackTurn == true){
                whiteTurn = true;
                blackTurn = false;
                movePiece();
            }
            // Otherwise will inform the user that they've selected the wrong side
            else {
                if(whiteTurn == true){
                    printf("You choose the wrong side you are white\n");
                }
                else{
                    printf("You choose the wrong side you are black\n");
                }
            }
            // Moves the piece
            movePiece();
            // Sleeps the thread for 2000 milliseconds (2 secs)
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        if(whitePieces == 0){
            std::cout << "Black has won\n";
        }
        else {
            std::cout << "White has won\n";
        }

    }


    chess();
    ~chess();
};







// Could make another chess board where all the pieces are classes and it changes what they do depending on what piece it is, would probably work better than this one lmao



//Hey I thought you looked cute in your profile picture so I decided to send you a friend request. Add me if you want to discuss trading lego instructions because I got some pretty rare ones baby
#endif // CHESS_H
