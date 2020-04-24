package sample;

import java.net.InetAddress;
import java.text.SimpleDateFormat;
import java.util.Date;

public class UdpMessage {
    protected String time;
    protected String message;
    protected String ip;
    protected int length;
    protected int port;

    public UdpMessage(String message, String ip, int port)
    {
        this.message = message;
        this.ip = ip;
        this.port = port;
        this.length = message.length();
        SimpleDateFormat formatter;
        formatter = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
        Date time = new Date();
        this.time =formatter.format(time);
    }

    public UdpMessage(byte[] message, int length, InetAddress ip, int port)
    {
        this( new String(message, 0, length), ip.getHostAddress(), port);
    }

    public String getTime() {
        return time;
    }

    public String getMessage() {
        return message;
    }

    public String getIp() {
        return ip;
    }

    public int getLength() {
        return length;
    }

    public int getPort() {
        return port;
    }

    @Override
    public String toString() {
        return "UdpMessage{" +
                "time='" + time + '\'' +
                ", message='" + message + '\'' +
                ", ip='" + ip + '\'' +
                ", length=" + length +
                ", port=" + port +
                '}';
    }
}
