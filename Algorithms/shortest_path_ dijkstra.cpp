/*
 
 Searchin for minimal distance from Sofia to Varna
 using dijkstra's algorithm and heuristic values.
 
 */


#include<iostream>
#include<map>
#include<set>

using namespace std;

//Consts to work with city names
const int Sofia = 1;
const int Plovdiv = 2;
const int Vidin = 3;
const int Pleven = 4;
const int Blagoevgrad = 5;
const int Svishtov = 6;
const int Ruse = 7;
const int Varna = 8;
const int Shumen = 9;
const int Yambol = 10;
const int Veliko_Turrnovo = 11;
const int Burgas = 12;

map<int,map<int,int> > graph;
map<int,int> h_map;

//Add path in both directions
void add(int Begining, int Destinacion, int distanceBetweenCities){
    graph[Begining][Destinacion] = distanceBetweenCities;
    graph[Destinacion][Begining] = distanceBetweenCities;
};

//Create the graph and heuristics values
void create(){
    add(Sofia,Plovdiv,150);
    add(Sofia,Pleven,200);
    add(Sofia,Vidin,250);
    add(Sofia,Blagoevgrad,100);
    add(Blagoevgrad,Plovdiv,150);
    add(Vidin,Pleven,150);
    add(Pleven,Veliko_Turrnovo,150);
    add(Plovdiv,Veliko_Turrnovo,200);
    add(Plovdiv,Yambol,150);
    add(Veliko_Turrnovo,Ruse,100);
    add(Shumen,Veliko_Turrnovo,200);
    add(Yambol,Burgas,100);
    add(Ruse,Svishtov,100);
    add(Shumen,Svishtov,150);
    add(Shumen,Burgas,150);
    add(Svishtov,Varna,100);
    add(Burgas,Varna,100);

    
    h_map[Sofia] = 400;
    h_map[Plovdiv] = 250;
    h_map[Blagoevgrad] = 500;
    h_map[Vidin] = 500;
    h_map[Pleven] = 250;
    h_map[Yambol] = 100;
    h_map[Veliko_Turrnovo] = 200;
    h_map[Shumen] = 150;
    h_map[Ruse] = 100;
    h_map[Svishtov] = 50;
    h_map[Burgas] = 50;
    h_map[Varna] = 0;
}

//Find unvisited city with min distance
int min_distance(map<int,int> distance, map<int,bool> sptSet){
    int min = INT_MAX;
    int min_city;

    for(int city=Sofia; city<=Burgas;city+=1){
        if(min>distance[city] && !sptSet[city]){
            min = distance[city];
            min_city = city;
        }
    }

    return min_city;
}

void dijkstra(int start){
    map<int,int> distance;
    map<int,bool> sptSet;

    for(int city=Sofia; city<=Burgas;city+=1){
        distance[city] = INT_MAX, sptSet[city] = false;
    }
    
    //Set distance to first city
    distance[start] = 0 + h_map[start];

    for(int i=0;i<12;i++){

        //Find new city
        int temp = min_distance(distance, sptSet);
        //If city is Varna we are finished
        if(temp == Varna) break;
        
        cout<<"Travel to town "<<temp<<endl;
        
        //Set the city as traveled to
        sptSet[temp] = true;

        //Update distances
        for(int city=Sofia; city<=Burgas;city+=1){
            if(!sptSet[city] && graph[temp][city] != 0){
                distance[city] = min(distance[city], distance[temp]-h_map[temp]+graph[temp][city]+h_map[city]);
            }
        }

    }

    cout<<"Distance from Sofia to Varna is:"<< distance[Varna]<<" km."<<endl;

}

int main(){
    create();

    dijkstra(Sofia);
    
    return 0;
}