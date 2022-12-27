package Algorithms;
import java.util.HashSet;
import java.util.Scanner;

public class Balls {

    public static void main(String[] args) {

        String input="";
        HashSet <String> colors = new HashSet<String>();
        int ballCounter=0;
        Scanner sc = new Scanner(System.in);
        input = sc.nextLine();

        while(!input.equals("End")){
            
            try {

                //Check if input is in correct format
                if(!input.contains(":")) throw new Exception();
                String[] temp =input.split(":");    
                if(temp.length!=2) throw new Exception();
                Integer.parseInt(temp[1]);

                //Add color to list of colors
                colors.add(temp[0]);
                //Add number of balls to the sum 
                ballCounter += Integer.parseInt(temp[1]);

            } catch (Exception e) {
                System.out.println("Input must be in format Color:count");
            }

            input = sc.nextLine();

            
        }

        sc.close();

        //If there is only one color we dont need to remove balls
        if(colors.size() == 1){
            System.out.println(0);
            return;
        }

        //If there are more than one color we need to remove all balls except 
        System.out.println(ballCounter-1);

        return;
    }


}
