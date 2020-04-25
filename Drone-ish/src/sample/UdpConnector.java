package sample;

import java.io.IOException;
import java.net.*;

public class UdpConnector implements Runnable {
    private DatagramSocket socket;
    private int udpPort = 7007;
    private int udpPortEcho = 7000;
    private Controller controller;
    private boolean receiveMessages = true;

    public UdpConnector(Controller controller)
    {
        this.controller = controller;
        setupSocket();
    }

    public void setupSocket()
    {
        try {
            socket = new DatagramSocket(udpPort);
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }

    public void closeSocket()
    {
        socket.close();
    }

    public void echoServer()
    {
        do {
            UdpMessage msg = receiveMessage();
            sendMessage("received: "+ msg.getMessage(), msg.getIp() );
            controller.handleMessage(msg);
            //System.out.println(msg.getIp());
        } while (receiveMessages);
    }

    public void sendMessage(String string, String ip)
    {
        try {
            sendMessage(string.getBytes(), InetAddress.getByName(ip));
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }

    public void sendMessage(byte[] bytes, InetAddress address)
    {
        DatagramPacket packet = new DatagramPacket(bytes, bytes.length, address, udpPortEcho);
        try {
            socket.send(packet);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public UdpMessage receiveMessage()
    {
        byte[] buffer = new byte[256];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.receive(packet);
            UdpMessage udpMessage = new UdpMessage(packet.getData(), packet.getLength(), packet.getAddress(), packet.getPort());
            System.out.println(udpMessage);
            return  udpMessage;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }


    }


    @Override
    public void run() {
        while (true)
        {
            echoServer();
        }

    }
}
