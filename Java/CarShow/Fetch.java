package car.show;

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

import org.bson.Document;

class Fetch {
    private JFrame jF;
    private JTextField idField;
    private JLabel statusLabel;
    private JPanel controlPanel;
    private MUD mDB;

    public Fetch(MUD db){
        mDB = db;
        prepareGui();
    }

    private void prepareGui(){
        jF = new JFrame("CarShow");
        jF.setSize(500,400);
        jF.setLayout(new GridLayout(4,1));

        idField = new JTextField("ID", JLabel.CENTER);

        statusLabel = new JLabel("", JLabel.CENTER);
        statusLabel.setSize(350,100);


        jF.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent WindowEvent){
                jF.setVisible(false);
                jF.dispose();
            }
        });

        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout());

        jF.add(idField);

        jF.add(controlPanel);
        jF.add(statusLabel);
        jF.setVisible(true);
    }

    public void showActionListener(){
        idField.setText("Enter ID Here");

        JPanel panel = new JPanel();
        JPanel panel2 = new JPanel();
        panel2.setBackground(Color.green);
        panel.setBackground(Color.magenta);
        JButton okButton = new JButton("ok");
        JButton getButton = new JButton("Get Contestant");
        JButton delButton = new JButton("Delete Contestant");

        idField.addKeyListener(new CustomkeyListener());
        okButton.addActionListener(new okActionListener());
        getButton.addActionListener(new getActionListener());
        delButton.addActionListener(new delActionListener());

        panel2.add(getButton);
        panel2.add(delButton);
        panel.add(okButton);

        controlPanel.add(panel2);
        controlPanel.add(panel);
        jF.setVisible(true);
    }

    class CustomkeyListener implements KeyListener {
        public void keyTyped(KeyEvent k) {

        }

        public void keyPressed(KeyEvent k) {
            int idCode = 0;
            String name = "";
            int year = 0;
            String make = "";
            String model = "";
            String category = "";
            int votes = 0;

            if(k.getKeyCode() == KeyEvent.VK_ENTER) {
                // Get information from data base.

                Document read = mDB.read(idField.getText());

                idCode = ((Number)read.get("idCode")).intValue();
                name = read.getString("Name");
                year = ((Number)read.get("Year")).intValue();
                make = read.getString("Make");
                model = read.getString("Model");
                category = read.getString("Category");
                votes = ((Number)read.get("Votes")).intValue();

                statusLabel.setText("<html><body>Entered- ID: " + idCode +
                        "<br>Name: " + name +
                        "<br>Year: " + year +
                        "<br>Make: " + make +
                        "<br>Model: " + model +
                        "<br>Category: " + category +
                        "<br>Votes: " + votes + "</body></html");

                idField.setText("");

            }
        }

        public void keyReleased(KeyEvent k) {

        }
    }

    class getActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            int idCode = 0;
            String name = "";
            int year = 0;
            String make = "";
            String model = "";
            String category = "";
            int votes = 0;

            // Get info from db
            Document read = mDB.read(idField.getText());

            idCode = ((Number)read.get("idCode")).intValue();
            name = read.getString("Name");
            year = ((Number)read.get("Year")).intValue();
            make = read.getString("Make");
            model = read.getString("Model");
            category = read.getString("Category");
            votes = ((Number)read.get("Votes")).intValue();

            statusLabel.setText("<html><body>Entered- ID: " + idCode +
                    "<br>Name: " + name +
                    "<br>Year: " + year +
                    "<br>Make: " + make +
                    "<br>Model: " + model +
                    "<br>Category: " + category +
                    "<br>Votes: " + votes + "</body></html");

            idField.setText("");

        }
    }

    class okActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            jF.setVisible(false);
            jF.dispose();
        }
    }

    class delActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            if(idField.getText() == "00000"){
                mDB.deleteMany();
            } else {
                String text = idField.getText();
                mDB.deleteOne(text);
            }
        }
    }
}