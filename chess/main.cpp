
#include <memory>
#include <chess.h>
chess::chess(){}
chess::~chess(){}






int main(){

    chess* Chess = new chess;
    Chess->beginGame();

    delete Chess;
    return 0;
}
