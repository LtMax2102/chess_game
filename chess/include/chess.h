#ifndef CHESS_H
#define CHESS_H

#include <string>
#include <array>
#include <vector>
#include <iostream>
class chess {
    int count = 0;
    std::array<char,8> alpha = {'A','B','C','D','E','F','G','H'};
    int letter = 1;
    char board[8][8] = {{'R','H','B','Q','K','B','H','R'},
                        {'P','P','P','P','P','P','P','P'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'-','-','-','-','-','-','-','-'},
                        {'P','P','P','P','P','P','P','P'},
                        {'R','H','B','K','Q','B','H','R'}};
    char row;
    int column;
    int rowInt;
    char selection;
public:
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
        std::cout << "\n  ";

        for(int i = 0; i < 8; i++){
            std::cout << " " << i+1;
        }
        std::cout << std::endl;
    }


    chess();
    ~chess();
};

#endif // CHESS_H
