#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>

using namespace std;

vector<string> dataset;

int dem[16][3];
int rep[16][3];

double counterDem = 0;
double counterRep = 0;

#define startPosDem 9
#define startPosRep 11

int testSize;

void setCounter(string line, int diff)
{
    bool isRep;
    int initPos;
    int counter = 0;


    if(line[0] == 'r'){
        isRep = true;
        counterRep+=diff;
        initPos = startPosRep;
    } 
    else{
        isRep = false;
        counterDem+=diff;
        initPos = startPosDem;
    }

    for (int i = initPos; i<line.size(); i+=2)
    {
       if(line[i] == 'y'){
        if(isRep) rep[counter][0]+=diff;
        else dem[counter][0]+=diff;
       }
       else if(line[i] == 'n'){
         if(isRep) rep[counter][1]+=diff;
         else dem[counter][1]+=diff;
       }
       else{
        if(isRep) rep[counter][2]+=diff;
        else dem[counter][2]+=diff;
       }
       counter++;
    }
}

bool testLine(string line)
{
    bool isRep;
    int initPos;


    if(line[0] == 'r'){
        isRep = true;
        initPos = startPosRep;
    } 
    else{
        isRep = false;
        initPos = startPosDem;
    }


    double probRep = 0;
    double probDem = 0;

    int counter = 0;

    for (int i = initPos; i<line.size(); i+=2)
    {
        if(line[i] == 'y'){
            probRep += log((rep[counter][0]) / (counterRep));
            probDem += log((dem[counter][0]) / (counterDem));
        }
        else if(line[i] == 'n'){
            probRep += log((rep[counter][1]) / (counterRep));
            probDem += log((dem[counter][1]) / (counterDem));
        }
        else{
            //Laplace smoothing
            //Alpha = 5; num of features = 2; number of + revues = counterRep or counterDem
            probRep += log((rep[counter][2] + 5) / (counterRep + 2));
            probDem += log((dem[counter][2] + 5) / (counterDem + 2));
        }
        counter++;
    }

    //probRep += log((counterRep) / (counterRep + counterDem));
    //probDem += log((counterDem) / (counterRep + counterDem));

    if(isRep){
        return probRep >= probDem;
    }
    else return probRep <= probDem;
    
}

double calculateAccuracy(int init)
{
    int rightCounter = 0;
    for (int i = 0; i < testSize; i++)
    {
        rightCounter += testLine(dataset[init+i]);
    }

    return (double)rightCounter/testSize * 100;
}

int main()
{
    ifstream filein("house-votes-84.data", ios::in);
    string line;

    while (getline(filein, line)) {
        dataset.push_back(line);
        setCounter(line, 1);
    }

    filein.close();

    testSize = dataset.size()/10;

    double combineAccuracy = 0;
    double accuracy;

    for (int j = 0; j < 10; j++)
    {

        for (int i = j * testSize; i < (j * testSize) + testSize; i++)
        {
            setCounter(dataset[i], -1);
        }

        accuracy = calculateAccuracy(j * testSize);
        cout << accuracy << "%"<<endl;
        combineAccuracy += accuracy;

        for (int i = j * testSize; i < (j * testSize) + testSize; i++)
        {
            setCounter(dataset[i], 1);
        }
    }

    cout <<"---------"<<endl;
    cout << combineAccuracy/10 << "%"<<endl;
}

