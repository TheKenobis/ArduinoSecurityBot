/**
 * @authors		Andrew Spackman, Josh Ravenscroft	
 * @version		0.7 - 18/03/2014
 */

import gnu.io.CommPortIdentifier;	
import gnu.io.SerialPort;

import java.io.Flushable;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Date;
import java.util.Properties;
import java.util.Scanner;

import javax.mail.Message;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;
																// Import external libraries
public class SendEmail {										// Begin program

	static InputStream input;									// Define InputStream as input
    static OutputStream output;
    
    static String from = "s1309454@gmail.com";					// Sender's email address. Currently using my (Andrew's) email account.
    static String password = "6v,.6v,.6v,.";					// Password of the sender.
    static String[] to = { "s1309454@connect.glos.ac.uk" }; 	// Recipient Email Address. This can be assigned multiple values
    static String host = "smtp.gmail.com";						// For gmail, use "smtp.gmail.com" For yahoo, use "smtp.mail.yahoo.com"
    static String portformail = "465";							// Port should be 465 if from within University. Otherwise, use 587
    
	public static void readFromArduino() throws Exception{		// Code to read value from Arduino
			
		try{													// Try/Catch for testing
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier("COM5");
																// Set Com port 5
			SerialPort port = (SerialPort)portId.open("serial talk", 4000);
			input = port.getInputStream();
			port.setSerialPortParams(9600,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);
																// Establish communication through Com port
			while (true) {
				if (input.available()>0) {
					int value=input.read();
					System.out.print((char)(value)); 
																// Print value from Com port, if not 0
					processInoutValueFromArduino(value);		// Initiate process to determine outcome, in relation to the recieved value
				}
				}
			
		}catch(Exception ex){									// If anything goes wrong, with the above code, do the following 
			ex.printStackTrace();								// Print the problem to help diagnose the solution
			
		}
	 }

	
	public static void processInoutValueFromArduino(int input){
																// Process to determine next steps in relation to Com port input
		Date date = new Date();									// Define date for use with email code
		
		if (input == 5) {
			sendToArduino(6);									// Initialisation code.
		}
		
		if (input == 7) {										// If a 7 is received from the Arduino,
			String subject = "Security Breach Notification" ;
																// Create email subject with the above content
			String body = "Security was breached on " + (date.toString());
																// Create email body content with above content
			sendFromGMail(host, portformail, from, password, to, subject, body);
																// Send to the GMail account with the details provided above
																// The strings for this are found above as declared variables
		}

		if (input == 8) {										// If an 8 is received from the Arduino,
			String subject = "Program Error" ;					// Send a different email with the following values
			String body = "An error has occured with the program on " + (date.toString());
			sendFromGMail(host, portformail, from, password, to, subject, body);
		}
		
	}
	
	public static void sendToArduino (int command) {			// Code to send value to Arduino
		
		try {
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier("COM5");
																// Set Com port 5
			SerialPort port = (SerialPort)portId.open("serial talk", 4000);
			output = port.getOutputStream();
			port.setSerialPortParams(9600,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);
																// Establish communication through Com port
				output.flush();									// Output is flushed; stops memory leak and potential errors
				port.close();									// Port is closed after use
			} 
		
			catch (Exception ex) {								// If anything goes wrong, with the above code, do the following 
				ex.printStackTrace();							// Print the problem to help diagnose the solution
				}
		}
		
	 public static void sendFromGMail(String host, String port, String from, String pass, String[] to, String subject, String body) {
		 														// Defining the various data types for use with email code
	    	Properties props = System.getProperties();			
	        props.put("mail.smtp.host", host);
	        props.put("mail.smtp.port", port);
	        props.put("mail.smtp.auth", "true");
	        props.put("mail.smtp.socketFactory.class","javax.net.ssl.SSLSocketFactory");
	        													// Email library components are defined
	        Session session = Session.getDefaultInstance(props);
	        MimeMessage message = new MimeMessage(session);
	        													// Create a new email message
	        try {
	            message.setFrom(new InternetAddress(from));
	            InternetAddress[] toAddress = new InternetAddress[to.length];

	            for( int i = 0; i < to.length; i++ ) {
	                toAddress[i] = new InternetAddress(to[i]);
	            }

	            for( int i = 0; i < toAddress.length; i++) {
	                message.addRecipient(Message.RecipientType.TO, toAddress[i]);
	            }
	            												// The above confirms the email address is legitimate
	            message.setSubject(subject);					// Setting the email's subject line from the subject variable
	            message.setText(body);							// Setting the email's body text from the body vairiable
	            Transport transport = session.getTransport("smtp");
	            transport.connect(host, from, pass);
	            transport.sendMessage(message, message.getAllRecipients());
	            transport.close();								// Creating an SMTP connection, sending an email and then closing the connection
	            System.out.println("Email sent");				// Confirming the email has been sent with a confirmation message
	        	}
	        
	        catch (Exception ex) {								// If anything goes wrong, with the above code, do the following 
	            ex.printStackTrace();							// Print the problem to help diagnose the solution
	        }
	        
	        
	        
	 }
		
	 public static void main(String[] args) throws Exception{	
		 														// Initiation code for the initial "readFromArduino" code
			readFromArduino();
			// processInoutValueFromArduino(7);					// Test line, for when a physical Arduino is unavailable

	 }
	 
}

