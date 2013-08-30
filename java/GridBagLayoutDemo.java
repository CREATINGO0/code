import javax.swing.*;
import java.awt.*;

public class GridBagLayoutDemo extends JPanel{  
    private JButton newGame, setting, hiscore;
    private ImageIcon titleImage;
    private JLabel title;
    private GridBagConstraints gbc = new GridBagConstraints();

    public GridBagLayoutDemo() {

        setLayout(new GridBagLayout());

        gbc.insets = new Insets(5,5,5,5);

        titleImage = new ImageIcon(getClass().getResource("title.png"));
        title = new JLabel(titleImage);
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.gridwidth = 2;
        add(title,gbc);

        newGame = new JButton("New Game");
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        gbc.fill = GridBagConstraints.BOTH;
        add(newGame,gbc);

        setting = new JButton("Setting");
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 1;
        add(setting,gbc);

        hiscore = new JButton("High Score");
        gbc.gridx = 1;
        gbc.gridy = 3;
        gbc.gridwidth = 1;
        add(hiscore,gbc);

    }

    public static void main(String[] args){  
        GridBagLayoutDemo t = new GridBagLayoutDemo();
        JFrame jf = new JFrame();

        jf.setTitle("Tutorial");
        jf.setSize(460,600);
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.setVisible(true);
        jf.add(t);
    }  
}  
