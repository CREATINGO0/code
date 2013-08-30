import java.awt.*;
import javax.swing.*;

public class ImageTutorial extends JFrame {
    private ImageIcon image1;
    private ImageIcon image2;
    private JLabel label1;
    private JLabel label2;

    ImageTutorial() {
        setLayout(new FlowLayout());

        image1 = new ImageIcon(getClass().getResource("1.jpg"));
        label1 = new JLabel(image1);
        add(label1);

        image2 = new ImageIcon(getClass().getResource("2.jpg"));
        label2 = new JLabel(image2);
        add(label2);
    }

    public static void main(String args[]) {
        ImageTutorial gui = new ImageTutorial();
        gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gui.setVisible(true);
        gui.pack();
        gui.setTitle("Image Program");
    }
}
