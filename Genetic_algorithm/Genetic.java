package Genetic_algorithm;

public class Genetic {
    public static void main(String[] args) {
        Population demo = new Population(5);
        int counter = 0;
        for(int i=0;i<demo.size;i++){
            System.out.println("Generation:"+counter+"; Person:"+(i+1)+"; Fitness:"+demo.population[i].fitnes);
        }
        System.out.println("----------------------");
        while(demo.fittest < 5){
            counter+=1;
            int[] pair = demo.getPairIndex();
            System.out.println("Selected pair:"+pair[0]+ " and "+pair[1]);
            Person child = demo.cross(demo.population[pair[0]], demo.population[pair[1]]);
            child = demo.mutate(child);
            demo.addPerson(child);
        }
        System.out.println("----------------------");
        for(int i=0;i<demo.size;i++){
            System.out.println("Generation:"+counter+"; Person:"+(i+1)+"; Fitness:"+demo.population[i].fitnes);
        }


    }
}

