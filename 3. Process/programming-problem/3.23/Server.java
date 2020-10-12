package com.company;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadLocalRandom;

public class Main {

    String[] quote = {
            "Never do today what you can do tomorrow",
            "Nobody lies on the internet",
            "The cake is a lie"
    };

    public static void main(String[] args) {
        try{
            ServerSocket socket = new ServerSocket(6017);

            while(true){
                Main main = new Main();
                Socket client = socket.accept();
                PrintWriter printWriter = new PrintWriter(client.getOutputStream(), true);
                printWriter.println(main.getRandomQuote());
                client.close();
            }

        } catch (IOException e) {
            System.err.println(e);
        }
    }

    int getRandomNumber(){
        return ThreadLocalRandom.current().nextInt(0, this.quote.length);
    }

    String getRandomQuote(){
        return this.quote[this.getRandomNumber()];
    }
}
