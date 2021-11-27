import java.util.Scanner;

public class Shape2DApp {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter total number of shapes:  ");
        int number = scan.nextInt();
        Double totalArea = 0.0;

        for (int i = 0; i < number; i++) {
            System.out.println(String.format("\nEnter shape %d : ", i + 1));
            System.out.println("=============");
            System.out.println("1. Circle");
            System.out.println("2. Triangle");
            System.out.println("3. Square");
            System.out.println("4. Rectangle");
            System.out.println("Enter shape option(1-4): ");
            int choice = scan.nextInt();

            switch (choice) {
                case 1:
                    Circle circle = new Circle();
                    circle.getDimensions();
                    totalArea += circle.getArea();
                    break;
                case 2:
                    Triangle triangle = new Triangle();
                    triangle.getDimensions();
                    totalArea += triangle.getArea();
                    break;
                case 3:
                    Square square = new Square();
                    square.getDimensions();
                    totalArea += square.getArea();
                    break;
                case 4:
                    Rectangle rectangle = new Rectangle();
                    rectangle.getDimensions();
                    totalArea += rectangle.getArea();
                    break;
            }
        }
        System.out.printf("\nTotal Area: %.2f", totalArea);
        scan.close();
    }
}
