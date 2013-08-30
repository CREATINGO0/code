import java.util.*;

public class InputTester {
    public static void main(String[] args) {
        Scanner i = new Scanner(System.in);
        System.out.print("How old are you? ");
        int age = i.nextInt();
        age++;
        System.out.println("Next year, you will be " + age);
    }
}
