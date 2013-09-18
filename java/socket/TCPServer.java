import java.io.*;
import java.net.*;

class TCPServer {

    public static void main(String argv[]) throws Exception {

        String clientSentence;
        String capitalizedSentence;

        ServerSocket welcomeSocket = new ServerSocket(6789);

        while(true) {
            /* wait on welcoming socket for contact by client */
            Socket connectionSocket = welcomeSocket.accept();

            /* create input stream, attached to socket */
            BufferedReader inFromClient =
                new BufferedReader(
                    InputStreamReader(connectionSocket.getInputStream()));

            /* create output stream, attached to socket */
            DataOutputStream outToClient =
                new DataOutputStream(connectionSocket.getOutputStream());

            /* read in line from socket */
            clientSentence = inFromClient.readLine();

            capitalizedSentence = clientSentence.toUpperCase() + '\n';

            /* write out line to socket */
            outToClient.writeBytes(capitalizedSentence);
        }
    }
}
