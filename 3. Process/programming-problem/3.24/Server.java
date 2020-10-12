package com.company;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ThreadLocalRandom;

public class Server {

    String[][] haiku = {
            {
                "From time to time",
                "The clouds give rest",
                "To the moon-beholders."
            },
            {
                "Sparrow’s child",
                "out of the way, out of the way!",
                "the stallion’s coming through"
            },
            {
                "Over the wintry",
                "forest, winds howl in rage",
                "with no leaves to blow."
            }
    };

    public static void main(String[] args) {
        try{
            ServerSocket socket = new ServerSocket(5575);

            while(true){
                Server main = new Server();
                System.out.println("Waiting for the connections");
                Socket client = socket.accept();
                System.out.println("Connection establish");
                PrintWriter printWriter = new PrintWriter(client.getOutputStream(), true);
                String[] haiku = main.getRandomHaiku();
                for(int i = 0; i < haiku.length; i++){
                    printWriter.println(haiku[i]);
                }
                client.close();
                System.out.println("Connection close");
            }

        } catch (IOException e) {
            System.err.println(e);
        }
    }

    int getRandomNumber(){
        return ThreadLocalRandom.current().nextInt(0, this.haiku.length);
    }

    String[] getRandomHaiku(){
        return this.haiku[this.getRandomNumber()];
    }
}
