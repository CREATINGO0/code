import java.util.*;

public class DateTester {
    public static void main(String[] args) {
        Calendar c = Calendar.getInstance();
        System.out.print(c.get(Calendar.YEAR) + ", ");
        c.add(Calendar.DAY_OF_MONTH, 700);
        System.out.println(c.get(Calendar.YEAR));
    }
}