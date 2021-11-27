import java.util.Scanner;

public class PlaneApp {
    public static void main(String[] args) {
        int choice;
        Scanner sc = new Scanner(System.in);
        Plane plane = new Plane();

        System.out.println("(1) Show number of empty seats");
        System.out.println("(2) Show the list of empty seats");
        System.out.println("(3) Show the list of seat assignment by seat ID");
        System.out.println("(4) Show the list of seat assignment by customer ID");
        System.out.println("(5) Assign a customer to a seat");
        System.out.println("(6) Remove a seat assignment");
        System.out.println("(7) Exit");
        do {
            System.out.println();
            System.out.print("   Enter the number of your choice: ");
            choice = sc.nextInt();
            switch (choice) {
                case 1: /* show number of empty seats */
                    plane.showNumEmptySeats();
                    break;
                case 2: /* show list of empty seats */
                    plane.showEmptySeats();
                    break;
                case 3: /* show list of customers in order of seat numbers */
                    plane.showAssignedSeats(true);
                    break;
                case 4: /* show list of customers in order of customer ID */
                    plane.showAssignedSeats(false);
                    break;
                case 5: /* assign customer to a seat */
                    System.out.println("Assigning Seat .. ");
                    System.out.print("   Please enter SeatID: ");
                    int seatIdAssign = sc.nextInt();
                    System.out.print("   Please enter Customer ID: ");
                    int customerIdAssign = sc.nextInt();
                    plane.assignSeat(seatIdAssign, customerIdAssign);
                    break;
                case 6: /* remove a seat assignment */
                    System.out.print("   Enter SeatID to unassign customer from: ");
                    int seatIdUnassign = sc.nextInt();
                    plane.unAssignSeat(seatIdUnassign);
                    break;
                case 7:
                    break;
            }
        } while (choice < 7);
        sc.close();
    }
}
