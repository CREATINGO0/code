/**
 * this program computes the factorial of a number
 */
public class Factorial {
    public static void main(String[] args) {
        int input = Integer.parseInt(args[0]);
        double result = factorial(input);
        System.out.println(result);
    }
    public static double factorial(int x) {
        if ( x<0 )
            return 0.0;
        double fact = 1.0;
        while ( x > 1 ) {
            fact *= x;
            x--;
        }
        return fact;
    }
}
