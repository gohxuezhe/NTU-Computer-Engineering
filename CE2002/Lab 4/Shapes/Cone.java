import java.util.Scanner;

public class Cone extends Shape {

    private Circle base;
    private double slantHeight;

    public Circle getBase() {
        return base;
    }

    public void setBase(Circle base) {
        this.base = base;
    }

    public double getSlantHeight() {
        return slantHeight;
    }

    public void setSlantHeight(double slantHeight) {
        this.slantHeight = slantHeight;
    }

    public double getArea() {
        return base.getArea() * Math.PI * slantHeight;
    }

    public void getDimensions() {
        Circle cirle = new Circle();
        cirle.getDimensions();
        this.base = cirle;

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Slant Height: ");
        this.slantHeight = sc.nextDouble();
    }

}