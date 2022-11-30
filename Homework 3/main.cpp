#include<vector>
#include<iostream>
#include <fstream>
#include <string>
//#include "Population.cpp"
using namespace std;

class Element{
    public:
    Element(int _weight, int _value){weight = _weight; value = _value;};
    int weight;
    int value;
};

class Backpack{
    public:
    vector<bool> elements;
    int combineValue;
    int combineWeight;

    Backpack(){
        combineWeight=0;
        combineValue=0;
    }

    Backpack(Backpack back1,Backpack back2){
        for(int i=0;i<back1.elements.size()/2;i++){
            elements.push_back(back1.elements[i]);
        }
        for(int i=back1.elements.size()/2;i<back1.elements.size();i++){
            elements.push_back(back2.elements[i]);
        }

    }

    int mutate(){
        int mutationPoint = rand()%elements.size();

        elements[mutationPoint] = !elements[mutationPoint];
        return mutationPoint;
    }

    void clear(){
        elements.clear();
        combineValue = 0;
        combineWeight = 0;
    }

    void show(){
        for(int i=0;i<elements.size();i++){
            cout<<elements[i];
        }
        cout<<endl;
    }

    bool operator==(const Backpack& rhs)
    {
        for(int i=0;i<elements.size();i++){
            if(elements[i]!=rhs.elements[i]) return false;
        }
        return true;
    }

    
};

bool sorting(const Backpack& lhs, const Backpack& rhs )
{
    return lhs.combineValue < rhs.combineValue;
}

class Population{
    public:
    vector<Element> elements;
    vector<Backpack> population;
    int populationSize;
    int elementsSize;
    int bestValue;
    int worstValue;
    int maxWeight;

    int setValue(Backpack pack){
        int value=0;
        for(int i=0;i<pack.elements.size();i++){
            if(pack.elements[i]==1){
                 value+=elements[i].value;
            }
        }
        return value;
    };

    int setWeight(Backpack pack){
        int weight=0;
        for(int i=0;i<pack.elements.size();i++){
            if(pack.elements[i]==1){
                 weight+=elements[i].weight;
            }
        }
        return weight;
    };

    Population(vector<Element> _elements, int _populationSize, int _maxWeight){
        elements = _elements;
        elementsSize = elements.size();
        maxWeight = _maxWeight;
        populationSize = _populationSize;

        worstValue = INT_MAX;
        bestValue = INT_MIN;

        for(int i=0;i<populationSize;i++){
            population.push_back(getRandomBackpack());
        }

        sort(population.begin(),population.end(), sorting);

        bestValue= population[populationSize-1].combineValue;
        worstValue = population[0].combineValue;

    }

    Backpack getRandomBackpack(){
        
        Backpack tempBackpack;
            for(int i=0;i<elementsSize;i++){
                bool temp = rand()%2;
                if(temp*elements[i].weight + tempBackpack.combineWeight<=maxWeight){
                    tempBackpack.combineWeight+=temp*elements[i].weight;
                    tempBackpack.combineValue+=temp*elements[i].value;
                    tempBackpack.elements.push_back(temp);
                }else{
                    tempBackpack.elements.push_back(0);
                }   
            }
        return tempBackpack;
    }

    Backpack createChild(){

        int firstParent=rand()%populationSize;
        int secondParent;
        do{
            secondParent=rand()%populationSize;
        }while(firstParent==secondParent);
        
        Backpack temp(population[firstParent],population[secondParent]);

        temp.mutate();

        temp.combineValue = setValue(temp);
        temp.combineWeight = setWeight(temp);
        return temp;
    }

    void generation(){
        Backpack child = createChild();
       

        if(child.combineWeight>maxWeight) {
            //cout<<"Wieght"<<endl;
            return;
        }

        if(child.combineValue<worstValue) {
            //cout<<"Value"<<endl;
            return;
        }

        for(Backpack backpack:population){
            if(backpack==child) return;
        }

        population[0]=child;

        sort(population.begin(),population.end(), sorting);

        bestValue= population[populationSize-1].combineValue;
        worstValue = population[0].combineValue;

    }

    void print(){
        for(auto backpack: population){
            for(auto element:backpack.elements){
                cout<<element;
            }
            cout<<"-"<<backpack.combineValue<<"-"<<backpack.combineWeight;
            cout<<endl;
        }
        cout<<"Worst Value:"<<worstValue<<endl;
        cout<<"Best Value:"<<bestValue<<endl;
    }
};

int main(){
    srand(time(NULL));
    vector<Element> temp;
    /*temp.push_back(Element(90, 150));
    temp.push_back(Element(130, 35));
    temp.push_back(Element(1530, 200));
    temp.push_back(Element(500, 160));
    temp.push_back(Element(150, 60));
    temp.push_back(Element(680, 45));
    temp.push_back(Element(270, 60));
    temp.push_back(Element(390, 40));
    temp.push_back(Element(230, 30));
    temp.push_back(Element(520, 10));
    temp.push_back(Element(110, 70));
    temp.push_back(Element(320, 30));
    temp.push_back(Element(240, 15));
    temp.push_back(Element(480, 10));
    temp.push_back(Element(730, 40));
    temp.push_back(Element(420, 70));
    temp.push_back(Element(430, 75));
    temp.push_back(Element(220, 80));
    temp.push_back(Element(70, 20));
    temp.push_back(Element(180, 12));
    temp.push_back(Element(40, 50));
    temp.push_back(Element(300, 10));
    temp.push_back(Element(900, 1));
    temp.push_back(Element(2000, 150));*/


    int x,y,x1,y1;
    ifstream myfile;
    string line;
    myfile.open ("KP long test data.txt");
    myfile >> x1 >> y1;
    for(int i=0;i<y1;i++){
        myfile >> x >> y;
        temp.push_back(Element(x, y));
    }
    int counter1=0,counter2=0,counter3=0,counter4=0,counter5=0;
        Population pop(temp, 100, 5000);
        for(int i=0;i<45000;i++){
            pop.generation();
            if( i==9 || i==10000 || i==20000 || i==30000 ){
                cout<<pop.bestValue<<endl;
            }
        }
        cout<<pop.bestValue<<endl;
    
}