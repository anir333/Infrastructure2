package be.kdg.helloarduino.model;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;

import java.io.PrintWriter;

public class SerialArduinoConnection {
    public static final int ARDUINO_PORT = 1;

    private SerialPort arduinoPort;

    public SerialArduinoConnection() {
        for (SerialPort port : SerialPort.getCommPorts()){
            System.out.println(port.toString());//check welke bij jou de Arduino port is...
        }
        arduinoPort = SerialPort.getCommPort("/dev/ttyACM0");
        boolean result = arduinoPort.openPort();
        System.out.println(result?"port opened!":"port NOT opened!");
    }

    public void sendString(String data) {
        System.out.printf("Sending %s to Arduino...\n", data);
        PrintWriter writer = new PrintWriter(arduinoPort.getOutputStream());
        writer.print(data);
        writer.close();
    }

    public byte[] receiveBytes(){
        byte[] newData = new byte[arduinoPort.bytesAvailable()];
        arduinoPort.readBytes(newData, newData.length);
        System.out.print("Receiving data from Arduino:");
        for (byte newDatum : newData) {
            System.out.printf("%c",(char)newDatum);
        }
        System.out.println();
        return newData;
    }

    public void addDatalistener(SerialPortDataListener dataListener){
        arduinoPort.addDataListener(dataListener);
    }
}
