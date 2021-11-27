import java.util.Scanner;

public class Triangle extends Shape {
    private double height;
    private double base;

    public double getHeight() {
        return height;
    }

    public double getBase() {
        return base;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setBase(double base) {
        this.base = base;
    }

    public double getArea() {
        return base * height * 1 / 2;
    }

    public void getDimensions() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter height of triangle: ");
        this.height = sc.nextDouble();
        System.out.print("Enter base of triangle: ");
        this.base = sc.nextDouble();
    }
}
