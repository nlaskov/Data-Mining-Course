#include<vector>
#include<iostream>
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
    int combineValue = 0;
    int combineWeight = 0;

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
        srand(time(NULL));
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
};

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
            bestValue = max(bestValue, population[i].combineValue);
            worstValue = min(worstValue, population[i].combineValue);
        }

    }

    Backpack getRandomBackpack(){
        
        Backpack tempBackpack;
        do{
            tempBackpack.clear();
            for(int i=0;i<elementsSize;i++){
                bool temp = rand()%2;
                tempBackpack.elements.push_back(temp);
            }

            tempBackpack.combineWeight = setWeight(tempBackpack);
        }while(tempBackpack.combineWeight>maxWeight);
        tempBackpack.combineValue = setValue(tempBackpack);

        return tempBackpack;
    }

    void print(){
        for(auto backpack: population){
            for(auto element:backpack){
                cout<<element;
            }
            cout<<"-"<<backpack.combineValue<<"-"<<backpack.combineWeight;
            cout<<endl;
        }
    }

    Backpack createChild(){

        int firstParent=rand()%populationSize;
        int secondParent;
        do{
            secondParent = rand()%populationSize;
        }while(firstParent==secondParent);

        population[firstParent].show();
        cout<<endl;
        population[secondParent].show();
        cout<<endl;
        
        Backpack temp(population[firstParent],population[secondParent]);

        temp.mutate();

        temp.show();
        

        temp.combineValue = setValue(temp);
        temp.combineWeight = setWeight(temp);
        cout<<endl<<temp.combineValue<<endl;
        return temp;
    }

    void generation(){
        Backpack child = createChild();
       
        if(child.combineWeight>maxWeight) return;

        if(child.combineValue<worstValue) return;

        bestValue=max(bestValue,child.combineValue);

        for(int i=0;i<populationSize;i++){
            if(population[i].combineWeight==worstValue){
                population[i] = child;
                break;
            }
        }

        worstValue = INT_MAX;

        for(int i=0;i<populationSize;i++){
            worstValue = min(worstValue, population[i].combineValue);
        }
    }
};