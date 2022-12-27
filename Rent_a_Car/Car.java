package Rent_a_Car;

public class Car {
    private int id = 0;
    private int year = 0;
    private String model = "";
    private boolean availability = false;
    private int pricePerHour = 0;

    Car(int _id,int _year,String _model,boolean _availability,int _pricePerHour){
        id = _id;
        year = _year;
        model = _model;
        availability = _availability;
        pricePerHour = _pricePerHour;
    }

    public int getId() {
        return id;
    }

    public void setYear(int _year) {
        year = _year;
    }

    public int getYear() {
        return year;
    }

    public void setModel(String _model) {
        model = _model;
    }

    public String getModel() {
        return model;
    }

    public void setAvailability(boolean _availability) {
        availability = _availability;
    }

    public boolean getAvailability(){
        return availability;
    }

    public void setPricePerHour(int _pricePerHour) {
        pricePerHour = _pricePerHour;
    }

    public int getPricePerHour() {
        return pricePerHour;
    }

    public void getCarInfo(){
        System.out.println("Model:" + model + ", Year:" + year + ", Available:" + (availability ? "Yes":"No ") + ", PricePerHour:" + pricePerHour + "$");
    }
}
