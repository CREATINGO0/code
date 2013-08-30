import java.awt.event.*;
import javax.swing.*;

public class Tutorial extends JFrame {
       JPanel jp = new JPanel();
       JLabel jl = new JLabel();
       JTextField jt = new JTextField(30);
       JButton jb = new JButton("Enter");

       public Tutorial() {
              setTitle("Tutorial");
              setVisible(true);
              setSize(400, 200);
              setDefaultCloseOperation(EXIT_ON_CLOSE);

              jp.add(jt);


              jt.addActionListener(new ActionListener() {
                     public void actionPerformed(ActionEvent e) {
                           String input = jt.getText();
                           jl.setText(input); 
                     }
              });

              jp.add(jb);
              jb.addActionListener(new ActionListener() {
                      public void actionPerformed(ActionEvent e) {
                             String input = jt.getText();
                             jl.setText(input);
                      }
              });
              
              jp.add(jl);
              add(jp);

       }

       public static void main(String[] args) {
             Tutorial t = new Tutorial();
       }
}
