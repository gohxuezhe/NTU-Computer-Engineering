public class Cuboid extends Rectangle {
    public double getArea() {
        return (super.getArea() * 4 + (this.getWidth() * this.getWidth() * 2));
    }
}
