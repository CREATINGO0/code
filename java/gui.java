import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class gui {

    public static void main(String args[]){

        //———–Look and Feel————-
        try {
            UIManager.setLookAndFeel(“com.sun.java.swing.plaf.motif.MotifLookAndFeel”);             

        } catch (Exception e) {
            System.err.println(“Look and feel not set.”);
        }
        //———–Look and Feel————-
        gui myGui = new gui();
        myGui.launchFrame();
    }//end main()
}
