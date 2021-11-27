import java.util.Scanner;

public class Circle extends Shape {
    private double radius;

    public double getRadius() {
        return radius;
    }

    public void setRadius(double radius) {
        this.radius = radius;
    }

    public double getArea() {
        return Math.PI * radius * radius;
    }

    public void getDimensions() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter radius of circle: ");
        this.radius = sc.nextDouble();
    }
}
