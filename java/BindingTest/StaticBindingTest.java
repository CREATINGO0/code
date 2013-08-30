import java.util.*;

public class StaticBindingTest{
    public static void main(String[] args) {
        Collection c = new HashSet();
        StaticBindingTest et = new StaticBindingTest();
        et.sort(c);
        HashSet h = new HashSet();
        et.sort(h);
    }

    // overloaded method takes Collection Argument
    public Collection sort(Collection c) {
        System.out.println("Inside collection sort method.");
        return c;
    }

    // another overloaded method which takes HashSet argument
    // which is sub class
    public Collection sort(HashSet hs) {
        System.out.println("Inside HashSet sort method.");
        return hs;
    }
}
