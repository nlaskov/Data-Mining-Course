#include<iostream>
#include "Board.h"
using namespace std;
int main(){
    int N;
    //cin>>N;
    N=5;
    srand(time(NULL));
    Board board(N);
    board.printBoard();
    cout<<"++++++++++++++++"<<endl;
    if(board.solver()){
        board.printBoard();
    }
}