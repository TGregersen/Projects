package car.show;

import java.awt.event.*;
import java.awt.*;
import javax.swing.*;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class Manage {
    private JFrame jF;
    private JTextField idField;
    private JTextField nameField;
    private JTextField yearField;
    private JTextField makeField;
    private JTextField modelField;
    private JList<String> categories;
    private JLabel statusLabel;
    private JPanel controlPanel;
    private MUD mDB;

    private DefaultListModel<String> cat;

    public Manage(MUD db){
        mDB = db;
        prepareGui();
    }

    private void prepareGui(){
        jF = new JFrame("CarShow");
        jF.setSize(500,400);
        jF.setLayout(new GridLayout(4,1));

        idField = new JTextField("ID", JLabel.CENTER);
        nameField=new JTextField("Name", JLabel.CENTER);
        yearField=new JTextField("Year", JLabel.CENTER);
        makeField=new JTextField("Make", JLabel.CENTER);
        modelField = new JTextField("Model", JLabel.CENTER);
        statusLabel = new JLabel("", JLabel.CENTER);
        statusLabel.setSize(350,100);

        cat = new DefaultListModel<>();

        BufferedReader rdr;
        try{

            rdr = new BufferedReader(new FileReader("Categories.txt"));
            String line = rdr.readLine();
            while( line != null ) {
                cat.addElement(line);
                line = rdr.readLine();
            }
            rdr.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        categories = new JList<>(cat);
        categories.setSize(75,75);


        jF.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent WindowEvent){
                jF.setVisible(false);
                jF.dispose();
            }
        });
        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout());

        jF.add(idField);
        jF.add(nameField);
        jF.add(yearField);
        jF.add(makeField);
        jF.add(modelField);
        jF.add(new JScrollPane(categories));
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
        JButton winButton = new JButton("Winners List");

        idField.addKeyListener(new CustomkeyListener());
        nameField.addKeyListener(new CustomkeyListener());
        yearField.addKeyListener(new CustomkeyListener());
        makeField.addKeyListener(new CustomkeyListener());
        modelField.addKeyListener(new CustomkeyListener());
        okButton.addActionListener(new okActionListener());
        getButton.addActionListener(new getActionListener());
        winButton.addActionListener(new winActionListener());

        panel.add(okButton);
        panel2.add(getButton);
        panel2.add(winButton);
        controlPanel.add(panel);
        controlPanel.add(panel2);
        jF.setVisible(true);
    }

    class CustomkeyListener implements KeyListener {
        public void keyTyped(KeyEvent k) {

        }

        public void keyPressed(KeyEvent k) {
            String idCode = "";
            String name="";
            String year="";
            String make="";
            String model="";

            if(k.getKeyCode() == KeyEvent.VK_ENTER) {
                try{
                    idCode = idField.getText();
                    name = nameField.getText();
                    year = yearField.getText();
                    make = makeField.getText();
                    model = modelField.getText();
                    // Category add
                } catch (Exception e){
                    statusLabel.setText("ERROR: bad string!");
                }
                statusLabel.setText("<html><body>Entered- ID: " + idCode +		// Store data to data base, id as key,
                        "<br>Name: " + name +
                        "<br>Year: " + year +
                        "<br>Make: " + make +
                        "<br>Model: " + model +
                        "<br>Category: " + categories.getSelectedValue() + "</body></html");

                mDB.create(idCode, name, year, make, model, categories.getSelectedValue());

                idField.setText("");
                nameField.setText("");
                yearField.setText("");
                makeField.setText("");
                modelField.setText("");
                categories.clearSelection();
            }
        }

        public void keyReleased(KeyEvent k) {

        }
    }

    class okActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            String idCode = "";
            String name="";
            String year="";
            String make="";
            String model="";
            try{
                idCode = idField.getText();
                name = nameField.getText();
                year = yearField.getText();
                make = makeField.getText();
                model = modelField.getText();
            } catch (Exception f){
                statusLabel.setText("ERROR: bad string!");
            }
            statusLabel.setText("<html><body>Entered- ID: " + idCode +
                    "<br>Name: " + name +
                    "<br>Year: " + year +
                    "<br>Make: " + make +
                    "<br>Model: " + model +
                    "<br>Category: " + categories.getSelectedValue() + "</body></html");

            mDB.create(idCode, name, year, make, model, categories.getSelectedValue());

            idField.setText("");
            nameField.setText("");
            yearField.setText("");
            makeField.setText("");
            modelField.setText("");
            categories.clearSelection();
        }
    }

    class getActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            Fetch fetchC = new Fetch(mDB);
            fetchC.showActionListener();
        }
    }

    class winActionListener implements ActionListener{
        public void actionPerformed(ActionEvent e){
            String[] arr = new String[cat.getSize()];
            cat.copyInto(arr);
            for( String categ : arr ){
                mDB.printWin(categ);  // Retrieve the 3 item list.
            }

            JFrame wF = new JFrame("Winners");
            wF.setSize(400,400);
            wF.setLayout(new GridLayout(4,1));
            JLabel jL = new JLabel("The Winners are: ", JLabel.CENTER);
            // Append 3 item list.
            wF.add(jL);
            wF.setVisible(true);

        }
    }
}