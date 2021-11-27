import java.util.Scanner;

public class Shape3DApp {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter total number of figures:  ");
        int number = scan.nextInt();
        Double totalSurfaceArea = 0.0;

        for (int i = 0; i < number; i++) {
            System.out.println(String.format("\nEnter figure %d : ", i + 1));
            System.out.println("=============");
            System.out.println("1. Sphere");
            System.out.println("2. Square-based Pyramid");
            System.out.println("3. Cube");
            System.out.println("4. Cuboid");
            System.out.println("5. Cone");
            System.out.println("6. Cylinder");
            System.out.println("Enter figure option(1-6): ");
            int choice = scan.nextInt();

            switch (choice) {
                case 1:
                    Sphere sphere = new Sphere();
                    sphere.getDimensions();
                    totalSurfaceArea += sphere.getArea();
                    break;
                case 2:
                    SquareBasedPyramid squareBasedPyramid = new SquareBasedPyramid();
                    squareBasedPyramid.getDimensions();
                    totalSurfaceArea += squareBasedPyramid.getArea();
                    break;
                case 3:
                    Cube cube = new Cube();
                    cube.getDimensions();
                    totalSurfaceArea += cube.getArea();
                    break;
                case 4:
                    Cuboid cuboid = new Cuboid();
                    cuboid.getDimensions();
                    totalSurfaceArea += cuboid.getArea();
                    break;
                case 5:
                    Cone cone = new Cone();
                    cone.getDimensions();
                    totalSurfaceArea += cone.getArea();
                    break;
                case 6:
                    Cylinder cylinder = new Cylinder();
                    cylinder.getDimensions();
                    totalSurfaceArea += cylinder.getArea();
                    break;
            }
        }
        System.out.printf("\nTotal Surface Area: %.2f", totalSurfaceArea);
        scan.close();
    }
}
