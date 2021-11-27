import java.util.Scanner;

public class Square extends Shape {
    private double length;

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public double getArea() {
        return length * length;
    }

    public void getDimensions() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter length of square: ");
        this.length = sc.nextDouble();
    }
}
