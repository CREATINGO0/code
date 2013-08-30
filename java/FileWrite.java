import java.io.*;

public class FileWrite {
    public static void main(String[] args) {
        try {
            FileWriter f = new FileWriter();
            // BufferedWriter out = new BufferedWriter(f);
            // out.write("Hello, Java");
            // out.close();
            f.write("Hello");
            f.close();
        } catch ( Exception e ) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
