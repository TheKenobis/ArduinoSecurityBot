
Send to Multiple Recipents:
void addRecipients(Message.RecipientType type, 
                   Address[] addresses)
throws MessagingException

Provide Email User ID for Email Authentication:
 
props.setProperty("mail.user", "myuser");
 props.setProperty("mail.password", "mypwd");

Email time and date stampe:

Date date = new Date();
SimpleDateFormat sdf = new SimpleDateFormat("MM/dd/yyyy h:mm:ss a");
String formattedDate = sdf.format(date);
System.out.println(formattedDate); // 12/01/2011 4:48:16 PM
