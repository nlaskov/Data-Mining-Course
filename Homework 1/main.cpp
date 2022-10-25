#include<iostream>
#include<chrono>
#include<set>
#include<cmath>
#include "Board.h"
using namespace std;
std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;


int IDAsearch(Board board,int limit,int cost){
    /*if(limit >= 50 && cost>30){
        
        board.printBoard();
        board.printPath();
        cout<<board.manhattan<<endl;
        cout<<"-----------------"<<endl;
    }*/
    
    int minimal_overload = INT_MAX;
    if(board.isMyGoal()){
        stop = chrono::high_resolution_clock::now();
        board.printPath();
        return -1;
    }
    else{
        int new_cost = cost + board.manhattan + board.linear;
        if(new_cost<= limit){
            
            vector<string> possibleMoves = board.possible_moves();
            for(int i = 0; i<possibleMoves.size();i++){
                //cout<<possibleMoves[i]<<endl;
                int result = IDAsearch(Board(board,possibleMoves[i]),limit,cost+1);
                if(result == -1) return -1;
                else minimal_overload = min(minimal_overload,result);
            }
            

        }

        else{
            minimal_overload = new_cost;
        }
        return minimal_overload;
    }

}

int main(){
    
    int N, pos;
    //Normal entry

    cout<<"Enter number of blocks:";
    cin>>N;
    cout<<"Enter position of zero in the solution:";
    cin>>pos;
    cout<<"Enter blocks order:";
    int arr[N+1];
    for(int i=0;i<N+1;i++){
        cin>>arr[i];
    }

    //Example with 15 blocks
/*
    N=15;
    pos = -1;
    int arr[] = {5,15,8,10,6,13,3,11,1,2,0,14,7,9,4,12};
*/
    //Example with 8 blocks
/*
    N=8;
    pos = -1;
    int arr[] = {0,5,4,6,3,7,1,2,8};
*/

    start = chrono::high_resolution_clock::now();
    Board board(sqrt(N+1),pos,arr);
    
    //Check if it is solvable
    if(!board.isSolavable()){
        cout<<"This board is unsolvable! :("<<endl;
        return 0;
    }

    int limit = board.manhattan + board.linear;
    while(true){
        int new_limit = IDAsearch(board,limit,0);
        
       
        if(new_limit == -1){
            auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
            printf("Time to find solution: %.3f seconds.\n", duration.count() * 1e-9);
            
            return 0;
        } 
        else limit = new_limit;
    }
    return 0;
}