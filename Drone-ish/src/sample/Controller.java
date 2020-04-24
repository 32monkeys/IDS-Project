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
    public void initialize()
    {
        udpConnector = new UdpConnector(this);
        new Thread(udpConnector).start();
        canvas.setStyle("-fx-background-color: white;");
        canvas.setMinSize(200,200);
        canvas.setPrefSize(400,400);
        drone = new Circle(100,100,10);
        drone.setFill(Color.BLUE);
        canvas.getChildren().add(drone);
        /*
        graphicsContext = canvas.getGraphicsContext2D();
        drone.setHeight(10);
        drone.setWidth(10);
        drone.DrawObject(graphicsContext);
        */

    }

    public void handleMessage(UdpMessage e) {
        String[] msgArray = e.getMessage().split(",");
        String potRead = "Potentiometer: " + msgArray[0];
        String xRead = "x: " + msgArray[1];
        String yRead = "y: " + msgArray[2];
        String butRead = "Button: " + msgArray[3];
        String result = potRead + "\n" +
                        xRead + "\n" +
                        yRead + "\n" +
                        butRead + "\n";
        textArea.setText(result);
        if (msgArray[2].equals("BACKWARD")){
            System.out.println("down");
            drone.setCenterY(drone.getCenterY()+10);
            drone.relocate(drone.getCenterX(),drone.getCenterY());

        } else if (msgArray[2].equals("FORWARD")){
            System.out.println("up");
            drone.setCenterY(drone.getCenterY()-10);
            drone.relocate(drone.getCenterX(),drone.getCenterY());

        }
        if (msgArray[1].equals("LEFT")){
            System.out.println("left");
            drone.setCenterX(drone.getCenterX()-10);
            drone.relocate(drone.getCenterX(),drone.getCenterY());
        } else if (msgArray[1].equals("RIGHT")){
            System.out.println("right");
            drone.setCenterX(drone.getCenterX()+10);
            drone.relocate(drone.getCenterX(),drone.getCenterY());
        }
        if(msgArray[3].equals("TRUE")){
            drone.setFill(Color.RED);
            System.out.println("click");
        } else drone.setFill(Color.BLUE);
        drone.setRadius(Integer.parseInt(msgArray[0])+10);
    }
}
