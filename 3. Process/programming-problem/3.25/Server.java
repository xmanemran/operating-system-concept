package com.company;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadLocalRandom;

public class Server {
    public static void main(String[] args) {
        try{
            ServerSocket socket = new ServerSocket(6017);

            while(true){
                Server main = new Server();
                System.out.println("Waiting for the connections");
                Socket client = socket.accept();
                System.out.println("Connection establish");

                InputStream in = client.getInputStream();
                OutputStream out = client.getOutputStream();

                int buffer;
                while((buffer = in.read())!= -1){
                    out.write(buffer);
                }
                out.flush();
                out.close();
                System.out.println("Connection close");
            }

        } catch (IOException e) {
            System.err.println(e);
        }
    }
}
