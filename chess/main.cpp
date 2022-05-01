
#include <memory>
#include <chess.h>
chess::chess(){}
chess::~chess(){
    delete selection;
    delete destination;
}






int main(){
    chess* Chess = new chess;
    Chess->beginGame();

    delete Chess;

    return 0;
}
