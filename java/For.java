public class For {
    public static void main(String[] args) {
        int i = 0;  
before: for (System.out.print("init value : "), System.out.println(i); i < 11; System.out.print("i="), System.out.println(i++)) {  
            if (i == 10)  
                continue before;  
}  
    }
}
