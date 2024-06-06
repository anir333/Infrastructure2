package be.kdg.helloarduino.view;

import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

import javax.imageio.plugins.tiff.TIFFTag;

public class ArduinoView extends BorderPane {
    private Label title;
    private VBox parameters;
    private Label wonOrLost, score, numOfTimesClicked, totalTilesEaten;
    private TextField tfTextForArduino;
    private TextField tfTextFromArduino;

    public ArduinoView() {
        initialiseNodes();
        layoutNodes();
    }

    private void initialiseNodes() {
        title = new Label("Play Piano Tiles!");
        parameters = new VBox();
        tfTextForArduino = new TextField();
        tfTextForArduino.setMinWidth(100);
        tfTextFromArduino = new TextField();
        tfTextFromArduino.setEditable(false);
        tfTextFromArduino.setMinWidth(100);
        wonOrLost = new Label();
        score = new Label();
        numOfTimesClicked = new Label();
        totalTilesEaten = new Label();
    }

    private void layoutNodes() {
        title.setStyle("-fx-text-fill: white; -fx-font-size: 24px; -fx-font-family: 'Bitstream Charter'; -fx-font-weight: bolder;");
        setMargin(title, new Insets(50));

        wonOrLost.setStyle("-fx-text-fill: white;");
        score.setStyle("-fx-text-fill: white;");
        numOfTimesClicked.setStyle("-fx-text-fill: white;");
        totalTilesEaten.setStyle("-fx-text-fill: white;");

        parameters.getChildren().addAll(wonOrLost, score, numOfTimesClicked, totalTilesEaten);
        wonOrLost.setAlignment(Pos.CENTER);
        VBox.setMargin(wonOrLost, new Insets(10));
        VBox.setMargin(score, new Insets(10));
        VBox.setMargin(numOfTimesClicked, new Insets(10));
        VBox.setMargin(totalTilesEaten, new Insets(10));

        setMargin(parameters, new Insets(10, 50, 50, 0));

        setRight(parameters);

        setAlignment(title, Pos.TOP_RIGHT);
        setTop(title);

        setStyle("-fx-background-image: url('/arduinoBG.jpg');" +
                "-fx-background-size: 700;" +
                "-fx-opacity: 90%;" +
                "-fx-background-repeat: no-repeat");
    }

    public void setParameters(String wonOrLost, String score, String numOfTimesClicked, String totalTilesEaten) {
        System.out.println("Setting parameters!");
        Platform.runLater(() -> {
            this.wonOrLost.setText(wonOrLost.equalsIgnoreCase("0") ? "YOU LOST!" : "YOU WON!");
            this.score.setText("YOUR SCORE: " + score);
            this.numOfTimesClicked.setText("Number of times clicked: " + numOfTimesClicked);
            this.totalTilesEaten.setText("Total number of tiles eaten: " + totalTilesEaten);
        });
    }

    TextField getTfTextFromArduino() {
        return tfTextFromArduino;
    }
}
