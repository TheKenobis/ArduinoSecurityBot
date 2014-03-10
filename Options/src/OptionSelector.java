import glos.*;


import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;


public class OptionSelector {
	static InputStream input;
	static OutputStream output;
	
	public static void readFromArduino() throws Exception{
			
		CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier("COM5");
		
		SerialPort port = (SerialPort)portId.open("serial talk", 4000);
		input = port.getInputStream();
		port.setSerialPortParams(9600,
				SerialPort.DATABITS_8,
				SerialPort.STOPBITS_1,
				SerialPort.PARITY_NONE);
		
		while (true) {
			if (input.available()>0) {
				System.out.print((char)(input.read()));
			}
			}
		
		}
		
	public static void sendToArduino (int command) {
		try {
			CommPortIdentifier portId = CommPortIdentifier.getPortIdentifier("COM5");
			SerialPort port = (SerialPort)portId.open("serial talk", 4000);
			output = port.getOutputStream();
			port.setSerialPortParams(9600,
					SerialPort.DATABITS_8,
					SerialPort.STOPBITS_1,
					SerialPort.PARITY_NONE);
			
				output.write((command+"").getBytes());
				output.flush();
			port.close();
			}catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	
    public static void main(String[] args) throws Exception{

    	while(true){
    		Scanner reader = new Scanner(System.in);
            System.out.println("Enter the command");
            int command=reader.nextInt();
            System.out.println("**** Sending ["+command + "]");
    	    sendToArduino(command);
    	    }
    }
	
		int choice = 0; {
		
		while (choice !=4){	
		if (choice == 1){
		IO.display("LED is ON");
			}
			else if (choice == 2){
			IO.display("LED is OFF");
			}
			else if (choice == 3){
			IO.display("Music is Playing");
			}
		
		choice=IO.readInt("Enter 1 to switch LED on \n Enter 2 to switch LED off \n Enter 3 to play music \n Enter 4 to quit the program");
		}
	}
}