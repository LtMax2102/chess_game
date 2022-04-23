
#include <memory>
#include <chess.h>


chess::chess(){
    bool end = true;
    while(end == true){
            std::cout << "Choose Row ";
            std::cin >> row;
            for(int i = 0; i < alpha.size(); i++){
                    if(row == alpha[i]){
                        break;
                    }
            std::cout << "Input not accepted\n";
        }
    }
}
chess::~chess(){

}






int main(){

    chess* Chess = new chess;

    // Chess->printBoard();

    /*
    std::cout << "Choose Row: ";
    std::cin >> row;
    for(int i = 0; i < 8; i++){

    }
    std::cout << "Choose Column: ";
    std::cin >> column;

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
        break;
    }

    char selection = a[rowInt][column-1];

    std::cout << selection << "\n";
    */
    delete Chess;
    return 0;
}
