import java.util.Scanner;

public class Rectangle extends Shape {
    private double height;
    private double width;

    public double getHeight() {
        return height;
    }

    public double getWidth() {
        return width;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getArea() {
        return height * width;
    }

    public void getDimensions() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter height of rectangle: ");
        this.height = sc.nextDouble();
        System.out.print("Enter width of rectangle: ");
        this.width = sc.nextDouble();
    }
}
