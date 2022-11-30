package Genetic_algorithm;

import java.util.Random;
public class Population{
    int size;
    int fittest;
    Person[] population;

    Population(int _size){
        fittest = -1;
        population = new Person[_size];
        for(int i=0;i<_size;i+=1){
            population[i] = new Person();
            if(population[i].fitnes>fittest){
                fittest = population[i].fitnes;
            }
        }
        size = _size;
    }

    int[] getPairIndex(){
        Random rn = new Random();
        int firstParent = rn.nextInt(size);
        int secondParent = rn.nextInt(size);
        while(firstParent == secondParent){
            secondParent = rn.nextInt(size);
        }
        return new int[] {firstParent,secondParent};
    }
    
    int getLeastFitIndex(){
        int leastFit=Integer.MAX_VALUE;
        int leastFitIndex=0;
        for(int i=0;i<size;i++){
            if(leastFit>population[i].fitnes){
                leastFit = population[i].fitnes;
                leastFitIndex = i;
            }
        }
        return leastFitIndex;
    }

    Person mutate(Person person){
        Random rn = new Random();
        int rand = rn.nextInt(5);
        if(person.genes[rand] == 0)person.genes[rand] = 1;
        else person.genes[rand] = 0;
        return person;
    }
    
    Person cross(Person father, Person mother){ 
        Person child = new Person(father,mother);
        return child;
    }

    void addPerson(Person child){
        int leastFitIndex = getLeastFitIndex();

        if(child.fitnes > population[leastFitIndex].fitnes){
            population[leastFitIndex] = child;
            if(fittest<child.fitnes){
                fittest = child.fitnes;
            }
        }
    }

}
