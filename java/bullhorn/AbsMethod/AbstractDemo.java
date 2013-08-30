public class AbstractDemo {  
    public static void main(String[] args) throws InstantiationException, IllegalAccessException, ClassNotFoundException{  
        DemoClass.printMessage("Hello, World");  
    }  
}  

abstract class DemoClass{  
    public DemoClass(){}  

    public static void printMessage(String msg){  
        System.out.println(msg);  
    }  
}  
