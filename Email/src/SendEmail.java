/**
 * @authors		Andrew Spackman, Josh Ravenscroft	
 * @version		0.2 - 04/03/2014
 */

import java.io.BufferedReader;
import java.io.OutputStream;
import java.util.Date;
import java.util.Properties;
import javax.mail.Message;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class SendEmail {

static BufferedReader input;
	
    static OutputStream output;
    
    static String from = "s1309454@gmail.com";					// Sender's email address. Currently using my (Andrew's) email account.
    static String password = "6v,.6v,.6v,.";					// Password of the sender.
    static String[] to = { "s1309454@connect.glos.ac.uk" }; 	// Recipient Email Address. This can be assigned multiple values
    static String host = "smtp.gmail.com";						// For gmail, use "smtp.gmail.com" For yahoo, use "smtp.mail.yahoo.com"
    static String portformail = "465";							// Port should be 465 if from within University. Otherwise, use 587
    
    
	 private static void sendFromGMail(String host, String port, String from, String pass, String[] to, String subject, String body) {
	    	Properties props = System.getProperties();
	        props.put("mail.smtp.host", host);
	        props.put("mail.smtp.port", port);
	        props.put("mail.smtp.auth", "true");
	        props.put("mail.smtp.socketFactory.class","javax.net.ssl.SSLSocketFactory");
	        
	        Session session = Session.getDefaultInstance(props);
	        MimeMessage message = new MimeMessage(session);

	        try {
	            message.setFrom(new InternetAddress(from));
	            InternetAddress[] toAddress = new InternetAddress[to.length];

	            for( int i = 0; i < to.length; i++ ) {
	                toAddress[i] = new InternetAddress(to[i]);
	            }

	            for( int i = 0; i < toAddress.length; i++) {
	                message.addRecipient(Message.RecipientType.TO, toAddress[i]);
	            }

	            message.setSubject(subject);
	            message.setText(body);
	            Transport transport = session.getTransport("smtp");
	            transport.connect(host, from, pass);
	            transport.sendMessage(message, message.getAllRecipients());
	            transport.close();
	        	}
	        
	        catch (Exception ex) {
	            ex.printStackTrace();
	        }
	        
	 }
	 
public static void main(String[] args) throws Exception{
    	
	Date date = new Date();
    
		String subject = "Security Breach Notification" ;
		String body = "Security was breached on " + (date.toString());
		sendFromGMail(host, portformail, from, password, to, subject, body);
     
	}

}
