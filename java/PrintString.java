import javax.swing.*;
import java.awt.*;

public class PrintString {
    public static void main(String[] args) {
        JFrame window = new JFrame();
        window.setSize(600,400);
        window.setTitle("Print String");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setVisible(true);

        drawingComponent DC = new drawingComponent();
        window.add(DC);
    }
}
