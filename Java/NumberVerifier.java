public class NumberVerifier extends javax.swing.JFrame {
    int[] d = new int[16];
    /**
     * Creates new form Frame
     */
    public NumberVerifier() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        ISBN_textField = new javax.swing.JTextField();
        card_textField = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        TextArea = new javax.swing.JTextArea();
        ISBN_verify = new javax.swing.JButton();
        Card_verify = new javax.swing.JButton();
        Clear_Button = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Number Verifier");

        ISBN_textField.setText("ISBN no.");
        ISBN_textField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ISBN_textFieldActionPerformed(evt);
            }
        });
        ISBN_textField.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyTyped(java.awt.event.KeyEvent evt) {
                ISBN_textFieldKeyTyped(evt);
            }
        });

        card_textField.setText("Card No.");

        TextArea.setColumns(20);
        TextArea.setRows(5);
        jScrollPane1.setViewportView(TextArea);

        ISBN_verify.setText("Verify1");
        ISBN_verify.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ISBN_verifyMouseClicked(evt);
            }
        });
        ISBN_verify.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ISBN_verifyActionPerformed(evt);
            }
        });

        Card_verify.setText("Verify2");
        Card_verify.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                Card_verifyActionPerformed(evt);
            }
        });

        Clear_Button.setText("Clear");
        Clear_Button.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Clear_ButtonMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 290, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(ISBN_textField, javax.swing.GroupLayout.PREFERRED_SIZE, 166, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                        .addGroup(layout.createSequentialGroup()
                            .addContainerGap()
                            .addComponent(card_textField, javax.swing.GroupLayout.PREFERRED_SIZE, 166, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                            .addGap(211, 211, 211)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                .addComponent(ISBN_verify)
                                .addComponent(Clear_Button)
                                .addComponent(Card_verify)))))
                .addContainerGap(122, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap(23, Short.MAX_VALUE)
                .addComponent(ISBN_textField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(5, 5, 5)
                .addComponent(ISBN_verify)
                .addGap(28, 28, 28)
                .addComponent(card_textField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(7, 7, 7)
                .addComponent(Card_verify)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(Clear_Button)
                .addGap(20, 20, 20))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void ISBN_textFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ISBN_textFieldActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_ISBN_textFieldActionPerformed

    //ISBN number verification
    private void ISBN_verifyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ISBN_verifyActionPerformed
        // Get input & filter     
        String s = ISBN_textField.getText();
        s = s.replaceAll("[-]","");
        System.out.println(s);
        for(int i=0; i<9 ; i++){
            d[i]= Integer.parseInt(String.valueOf(s.charAt(i)));
        }
        
        //check for X
        if (s.charAt(9)== 'X'){
            d[9]= 10;
        }
       
        //Check 
        if(((d[0]+2*(d[1])+3*(d[2])+4*(d[3])+5*(d[4])+6*(d[5])+7*(d[6])+8*(d[7])+9*(d[8])+10*(d[9]))%11)== 0){
            TextArea.setText("Valid ISBN Number.");
        }
        else {
            TextArea.setText("Invalid ISBN Number.");
        }
    }//GEN-LAST:event_ISBN_verifyActionPerformed

    private void Clear_ButtonMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Clear_ButtonMouseClicked
        ISBN_textField.setText("");
        card_textField.setText("");
        TextArea.setText("");
    }//GEN-LAST:event_Clear_ButtonMouseClicked

    private void ISBN_verifyMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ISBN_verifyMouseClicked
        // TODO add your handling code here:
        
    }//GEN-LAST:event_ISBN_verifyMouseClicked

    private void ISBN_textFieldKeyTyped(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_ISBN_textFieldKeyTyped
        // TODO add your handling code here:
    }//GEN-LAST:event_ISBN_textFieldKeyTyped

    //Credit card verification
    private void Card_verifyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_Card_verifyActionPerformed
        // TODO add your handling code here:
        int total = 0;
        String s = card_textField.getText();

        for(int i =0; i <16; i++){
            d[i]= Integer.parseInt(String.valueOf(s.charAt(i)));
            
            if(i%2 == 0){
                d[i] = d[i]*2;
                
                if(d[i]>9){
                    d[i]-=9;
                }
            }
            total += d[i];
        }
        
        if (total%10 == 0){
            TextArea.setText("Valid credit card number");
        }
        else {
            TextArea.setText("Invalid credir card number");
        }
    }//GEN-LAST:event_Card_verifyActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(NumberVerifier.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(NumberVerifier.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(NumberVerifier.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(NumberVerifier.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new NumberVerifier().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Card_verify;
    private javax.swing.JButton Clear_Button;
    private javax.swing.JTextField ISBN_textField;
    private javax.swing.JButton ISBN_verify;
    private javax.swing.JTextArea TextArea;
    private javax.swing.JTextField card_textField;
    private javax.swing.JScrollPane jScrollPane1;
    // End of variables declaration//GEN-END:variables
}