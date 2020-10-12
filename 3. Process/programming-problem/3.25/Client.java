package com.company;

import java.io.*;
import java.net.Socket;

public class Client {

    public static void main(String[] args) {
        try {
            Socket socket = new Socket("127.0.0.1", 6017);
            InputStream in = socket.getInputStream();
            OutputStream out = socket.getOutputStream();
            String message = "Hello world";
            out.write(message.getBytes());
            out.flush();

            int buffer;
            while((buffer = in.read())!= -1){
                System.out.print((char) buffer);
            }
            socket.close();
        } catch (IOException e) {
            System.err.println(e);
        }
    }
}
