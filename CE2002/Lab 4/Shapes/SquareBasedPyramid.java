public class SquareBasedPyramid extends Shape {
    private Square baseArea;
    private Triangle sideArea;

    public Square getBaseArea() {
        return baseArea;
    }

    public Triangle getSideArea(){
        return sideArea;
    }

    public void setBaseArea(Square baseArea) {
        this.baseArea = baseArea;
    }

    public void setSideArea(Triangle sideArea) {
        this.sideArea = sideArea;
    }

    public double getArea() {
        return this.baseArea.getArea() + 4 * this.sideArea.getArea();
    }

    public void getDimensions() {
        Triangle triangle = new Triangle();
		System.out.println("Enter values for triangle sides");
		triangle.getDimensions();
        this.setSideArea(triangle);

        Square square = new Square();
        square.setLength(triangle.getBase());
        this.setBaseArea(square);
    }
}
