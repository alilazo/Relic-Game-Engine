import javax.swing.*;

public class MapEditor {
    private JButton button1;
    private JPanel MapPanel;

    public static void main(String[] args) {
        JFrame frame = new JFrame("MapEditor");
        frame.setContentPane(new MapEditor().MapPanel);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(1000, 500);
        frame.setVisible(true);
    }
}
