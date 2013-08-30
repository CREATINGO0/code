import java.awt.*;
import javax.swing.*;

public class drawingComponent extends JComponent {
    public void paintComponent(Graphics g) {
        Graphics2D g2 = (Graphics2D) g;
        g2.drawString("WTF",20,20);
    }
}
