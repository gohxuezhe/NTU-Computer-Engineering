import java.util.Scanner;

public class Cylinder extends Shape {

    private Circle base;
    private int height;

    public Circle getBase() {
        return base;
    }

    public void setBase(Circle base) {
        this.base = base;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public double getArea() {
        return (base.getArea() * 2) + (base.getRadius() * height);
    }

    public void getDimensions() {
        Circle circle = new Circle();
        circle.getDimensions();
        this.base = circle;

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter height: ");
        this.height = sc.nextInt();
    }

}