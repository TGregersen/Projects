package car.show;

/**
 * <h1> CarShow </h1>
 * The Car Show application produces a simple and quick user
 * interface for tabulating votes during a car show. Uses a
 * MongoDB as storage for details about contestants and vote
 * counts.
 *
 *
 * @author: Todd Gregersen
 * @version:
 * @since: 9/25/19
 *
 */

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

/**
 * Builds starting UI and contains main method.
 */
public class CarShow{
    private JFrame jF;
    private JTextField idField;
    private JLabel statusLabel;
    private JPanel controlPanel;
    private MUD mDB;

    /**
     * Initializes the data base and calls UI creation.
     */
    public CarShow(){
        mDB = new MUD();
        prepareGui();
    }

    /**
     * Creates instance of class, then sets the action listener.
     * @param args unused
     * @return nothing
     */
    public static void main(String[] args) {
        CarShow exampleA = new CarShow();
        exampleA.showActionListener();
    }

    /**
     * Creates; the user interface, labels, listener and sets visible.
     */
    private void prepareGui(){
        jF = new JFrame("CarShow");
        jF.setSize(500,400);
        jF.setLayout(new GridLayout(4,1));

        idField = new JTextField("ID", JLabel.CENTER);
        statusLabel = new JLabel("", JLabel.CENTER);
        statusLabel.setSize(350,100);

        jF.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent WindowEvent){
                System.exit(0);
            }
        });
        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout());

        jF.add(idField);
        jF.add(controlPanel);
        jF.add(statusLabel);
        jF.setVisible(true);
    }

    /**
     * Creates panels, buttons, and assigns listeners and values.
     */
    public void showActionListener(){
        idField.setText("Enter ID Here");

        /**
         * Creating panels for UI organization.
         */
        JPanel panel = new JPanel();
        JPanel panel2 = new JPanel();

        panel.setBackground(Color.magenta);
        panel2.setBackground(Color.blue);

        /**
         * Creating the buttons for interaction.
         */
        JButton okButton = new JButton("ok");
        JButton modButton = new JButton("Car List");

        /**
         * Assigning listeners to items.
         */
        idField.addKeyListener(new customKeyListener());
        okButton.addActionListener(new okActionListener());
        modButton.addActionListener(new modActionListener());

        /**
         * Adding items to panels, then the panels to the UI.
         */
        panel.add(okButton);
        panel2.add(modButton);
        controlPanel.add(panel);
        controlPanel.add(panel2);
        jF.setVisible(true);
    }

    /**
     * Listener for the "Enter" key to avoid having to use the mouse.
     */
    class customKeyListener implements KeyListener {

        public void keyTyped(KeyEvent k) {
            // No action on typed.
        }

        /**
         * Get the text number and output to status label as user feedback while increaseing vote count.
         * @param k contains key pressed event.
         * @exception Exception on failed get text.
         */
        public void keyPressed(KeyEvent k) {
            String idCode = "";
            if(k.getKeyCode() == KeyEvent.VK_ENTER) {
                try{
                    idCode = idField.getText();
                } catch (Exception e){
                    statusLabel.setText("ERROR: bad string!");
                }
                statusLabel.setText("Entered text: " + idCode);

                mDB.increaseVote(idCode); //add 1 to count inside data base.

                idField.setText("");
            }
        }

        public void keyReleased(KeyEvent k) {
            // No action on typed.
        }
    }

    /**
     * For the OK button, similar to the enter key, return value as feedback and increase count.
     * @param e unused.
     * @see ActionListener
     */
    class okActionListener implements ActionListener{

        public void actionPerformed(ActionEvent e){

            statusLabel.setText("Entered text: " + idField.getText());

            mDB.increaseVote(idField.getText()); //add 1 to count inside data base.

            idField.setText("");
        }
    }

    /**
     * Initiate the Manage interface by creating object and starting listener.
     * @parameter E unused.
     * @see ActionListener
     */
    class modActionListener implements ActionListener{

        public void actionPerformed(ActionEvent e){

            Manage manageB = new Manage(mDB);

            manageB.showActionListener();
        }
    }
}