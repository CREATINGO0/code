public class DynamicBindingTest {
    public static void main(String[] args) {
        Vehicle vehicle = new Car();
        vehicle.start();
    }
}

class Vehicle {
    public void start() {
        System.out.println("Inside start method of Vehicle.");
    }
}

class Car extends Vehicle {
    @Override
    public void start() {
        System.out.println("Inside start method of Car.");
    }
}
