package be.kdg.helloarduino.view;

import be.kdg.helloarduino.model.SerialArduinoConnection;
import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;
import com.fazecast.jSerialComm.SerialPortEvent;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;

import java.util.List;

public class ArduinoPresenter implements SerialPortDataListener {
    private SerialArduinoConnection model;
    private ArduinoView view;

    public ArduinoPresenter(SerialArduinoConnection model, ArduinoView view) {
        this.model = model;
        this.view = view;
        addEventListeners();
        model.addDatalistener(this);
    }

    private void addEventListeners() {

    }

    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
    }

    @Override
    public void serialEvent(SerialPortEvent event) {
        System.out.println(Thread.currentThread());
        if (event.getEventType() != SerialPort.LISTENING_EVENT_DATA_AVAILABLE) {
            return;
        }
        StringBuilder text = new StringBuilder(view.getTfTextFromArduino().getText());
        for (byte oneByte : model.receiveBytes()) {
            text.append((char) oneByte);
        }

        if (text.toString().contains("***...")) {
            System.out.println("\n\n\n Game ended! \n\n\n");
            System.out.println(text);
            this.presentData(text.toString());
        }

        //De methode serialEvent wordt vanop een andere Thread aangeroepen (asynchroon)
        //Omdat het aanpassen van de UI enkel mag op de JavaFX Application Thread
        //gebruiken we Platform.runLater. Threads wordt behandeld in de leerstof java van het tweede jaar!

        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                view.getTfTextFromArduino().setText(text.toString());
            }
        });
    }

    public void presentData(String values) {
        List<String> gameInformation = List.of(values.split("SEPARATOR"));

        view.setParameters(gameInformation.get(1), gameInformation.get(2), gameInformation.get(3), gameInformation.get(4));
    }

} // class
