package sample;

import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;


public class Controller {

    @FXML
    TextArea textArea;
    @FXML
    Pane canvas;
    UdpConnector udpConnector;
    Circle drone;


    // this method is executed when our GUI is ready
    public void initialize() {
        udpConnector = new UdpConnector(this);
        new Thread(udpConnector).start();
        canvas.setStyle("-fx-background-color: white;");
        canvas.setMinSize(200, 200);
        canvas.setPrefSize(400, 400);
        drone = new Circle(100, 100, 10);
        drone.setFill(Color.BLUE);
        canvas.getChildren().add(drone);

    }

    public void handleMessage(UdpMessage e) {
        try {
            String[] msgArray = e.getMessage().split(",");
            textArea.setText(showCommands(msgArray));
            potSize(msgArray[0]);
            moveX(msgArray[1]);
            moveY(msgArray[2]);
            buttonClick(msgArray[3]);
        }catch (ArrayIndexOutOfBoundsException error){
            error.printStackTrace();
        }
    }

    private String showCommands(String[] msgArray) {
        String potRead = "Potentiometer: " + msgArray[0];
        String xRead = "x: " + msgArray[1];
        String yRead = "y: " + msgArray[2];
        String butRead = "Button: " + msgArray[3];
        String result = potRead + "\n" +
                xRead + "\n" +
                yRead + "\n" +
                butRead + "\n";
        return result;
    }

    private void potSize(String potentiometer) {
        drone.setRadius(Integer.parseInt(potentiometer));
    }

    private void moveX(String x) {
        if (x.equals("LEFT")) {
            //System.out.println("left");
            drone.setCenterX(drone.getCenterX() - 10);
            drone.relocate(drone.getCenterX(), drone.getCenterY());
        } else if (x.equals("RIGHT")) {
            //System.out.println("right");
            drone.setCenterX(drone.getCenterX() + 10);
            drone.relocate(drone.getCenterX(), drone.getCenterY());
        }
    }

    private void moveY(String y) {

        if (y.equals("BACKWARD")) {
            //System.out.println("down");
            drone.setCenterY(drone.getCenterY() + 10);
            drone.relocate(drone.getCenterX(), drone.getCenterY());

        } else if (y.equals("FORWARD")) {
            //System.out.println("up");
            drone.setCenterY(drone.getCenterY() - 10);
            drone.relocate(drone.getCenterX(), drone.getCenterY());
        }
    }

    private void buttonClick(String button) {
        if (button.equals("TRUE")) {
            drone.setFill(Color.RED);
            //System.out.println("click");
        } else drone.setFill(Color.BLUE);
    }
}
