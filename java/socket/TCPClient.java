import java.io.*;
import java.net.*;

class TCPClient {

    public static void main(String argv[]) throws Exception {

        String Sentence;
        String modifiedSentence;

        /* creat input stream */
        BufferedReader inFromUser =
            new BufferedReader(
                new InputStreamReader(System.in));

        /* create client socket, connect to server */
        Socket clientSocket = new Socket("hostname",6789);

        /* create output stream attached to socket */
        DataOutputStream outToServer =
            new DataOutputStream(
                    clientSocket.getOutputStream());

        /* create input stream attached to socket */
        BufferedReader inFromUser =
            new BufferedReader(
                    new InputStreamReader(
                        clientSocket.getInputStream()));

        Sentence = inFromUser.readLine();

        /* send line to server */
        outToServer.writeBytes(sentence + '\n');

        /* read line from server */
        modifiedSentence = inFromServer.readLine();

        System.out.println("From Server: " + modifiedSentence);

        clientSocket.close();
    }
}
