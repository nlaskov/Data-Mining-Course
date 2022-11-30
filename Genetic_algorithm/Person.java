package Genetic_algorithm;

import java.util.Random;

class Person{
    int fitnes;
    int[] genes = new int[5];

    Person(){
        Random rn = new Random();
        for(int i=0;i<5;i+=1){
            genes[i] = rn.nextInt(2);
        }
        fitnes = calculateFitness();
    }

    Person(Person father, Person mother){
        for(int i=0;i<5;i++){
            if(i<3){
                genes[i] = father.genes[i];
            }
            else{
                genes[i] = mother.genes[i];
            }
        }
        fitnes = calculateFitness();
    }

    int calculateFitness(){
        int counter=0;
        for(int i=0;i<5;i++){
            counter+=genes[i];
        }
        return counter;
    }

}