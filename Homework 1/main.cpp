#include<iostream>
#include<chrono>
#include "Board.h"
using namespace std;
std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;

int IDAsearch(Board board,int limit,int cost){
    
    int minimal_overload = INT_MAX;
    if(board.isMyGoal()){
        stop = chrono::high_resolution_clock::now();
        board.printPath();
        return -1;
    }
    else{
        int new_cost = cost + board.manhattan_distance();
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
    //cin>>N>>pos;
    /*N=3;
    pos=1;
    int arr[]={2,1,0,3};
    for(int i=0;i<N+1;i++){
        cin>>arr[i];
    }
    */
    N=8;
    pos=-1;
    int arr[]={5,7,3,2,0,4,6,1,8};
    start = chrono::high_resolution_clock::now();
    Board board(N/3+1,pos,arr);
    
    //Check if it is solvable
    if(!board.isSolavable()){
        cout<<"This board is unsolvable! :("<<endl;
        return 0;
    }

    int limit = board.manhattan_distance();
    while(true){
        int new_limit = IDAsearch(board,limit,0);
        if(new_limit == -1){
            auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
            cout<<"Time to find solution: "<<duration.count()/1000<<"."<<duration.count()%1000<<"sec."<<endl;
            return 0;
        } 
        else limit = new_limit;
    }

    return 0;
}