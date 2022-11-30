#include<iostream>
#include<queue>
#include <iomanip>
using namespace std;
class Board
{
    public:
    int N;
    int empty_space;
    vector<char> frogs;
    vector< vector<char> > steps;

    void printSteps(){
        steps.push_back(frogs);
        for(int i=0;i<steps.size();i++){
            
            for(int j=0;j<frogs.size();j++){
                cout<<steps[i][j];
            }
            cout<<endl;
        }

    }
};


int main(){
    int N ;
    cout<<"Number of frogs on either side:";
    cin>>N;
    queue<Board> line;
    Board board;
    board.empty_space = N;
    for(int i=0;i<N*2+1;i++){
        if(i<N) board.frogs.push_back('>');
        else if(i==N) board.frogs.push_back('_');
        else board.frogs.push_back('<');
    }
    line.push(board);
    vector<char> goal;
    for(int i=0;i<N*2+1;i++){
        if(i<N) goal.push_back('<');
        else if(i==N) goal.push_back('_');
        else goal.push_back('>');
    }

    while(true){
        Board temp = line.front();
        line.pop();
        if(temp.frogs == goal){
            temp.printSteps();
            return 0;
        }

        if(temp.empty_space-2>=0 && temp.frogs[temp.empty_space-2]=='>'){
            Board temp1 = temp;
            temp1.steps.push_back(temp.frogs);
            temp1.frogs[temp.empty_space-2] = '_';
            temp1.frogs[temp.empty_space] = '>';
            temp1.empty_space-=2;
            line.push(temp1);
        }
        if(temp.empty_space-1>=0 && temp.frogs[temp.empty_space-1]=='>'){
            Board temp1 = temp;
            temp1.steps.push_back(temp.frogs);
            temp1.frogs[temp.empty_space-1] = '_';
            temp1.frogs[temp.empty_space] = '>';
            temp1.empty_space-=1;
            line.push(temp1);
        }
        if(temp.empty_space+2<N*2+1 && temp.frogs[temp.empty_space+2]=='<'){
            Board temp1 = temp;
            temp1.steps.push_back(temp.frogs);
            temp1.frogs[temp.empty_space+2] = '_';
            temp1.frogs[temp.empty_space] = '<';
            temp1.empty_space+=2;
            line.push(temp1);   
        }
        if(temp.empty_space+1<N*2+1 && temp.frogs[temp.empty_space+1]=='<'){
            Board temp1 = temp;
            temp1.steps.push_back(temp.frogs);
            temp1.frogs[temp.empty_space+1] = '_';
            temp1.frogs[temp.empty_space] = '<';
            temp1.empty_space+=1;
            line.push(temp1);
        }
    }


}