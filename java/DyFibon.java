import java.util.*;

public class DyFibon  {  
    public static void main(String[] args)  {  
        Scanner s = new Scanner(System.in);
        System.out.print("Calc: ");  
        long n = s.nextLong();
        System.out.println("Fibonacci(" + n +")=" + fibonacci(n));  

    }  

    public static long fibonacci(long n)  {  
        long result = 1,f1 = 1,f2 = 1;  

        if(n<2) return 1;  
        for(long i=2;i<=n;i++)  {  
            result = f1 + f2;  
            f1 = f2;  
            f2 = result;  
        }  
        return result;  
    }  
}  
