// https://www.cse.unsw.edu.au/~cs2911/13s1/lectures/Ch7/slide020.html

public class ArrayTest {
    public static void main(String[] args) {
        double[] a = new double[10];
        Class c = a.getClass();
        if(c.isArray())
            System.out.println(c.getComponentType());
    }
}
