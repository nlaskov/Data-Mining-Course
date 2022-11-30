package Rent_a_Car;

import java.util.ArrayList;

public class Rental {

    private ArrayList<Car> cars;

    Rental(){
        cars = new ArrayList<Car>();
    }

    public void addCar(){

    }

    public void editCar(int id){

    }

    public void listCars(){

    }

    public boolean rentCar(int id){
        return true;
    }

    public boolean checkАvailability(int id){
        return true;
    }

    public static void main(String[] args) {
        Car myCar = new Car(0,1967,"Ford Mustang",true,15);
        myCar.getCarInfo();
    }
}
