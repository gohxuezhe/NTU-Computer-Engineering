public class Plane {
    private PlaneSeat[] seat;
    private int numEmptySeat;

    public Plane() {
        this.numEmptySeat = 12;
        this.seat = new PlaneSeat[12];
        for (int i = 0; i < 12; i++) {
            /* initializing each plane seat in plane seat array */
            this.seat[i] = new PlaneSeat(i + 1);
        }
    }

    private PlaneSeat[] sortSeats() {
        int n = this.seat.length;
        PlaneSeat[] seat2 = new PlaneSeat[n];
        PlaneSeat temp;

        /* making a copy of original seat array */
        for(int i = 0; i < n; i++) {
            seat2[i] = new PlaneSeat(this.seat[i].getSeatID());
            if(this.seat[i].isOccupied()){
                seat2[i].assign(this.seat[i].getCustomerID());
            }
        }

        /* using bubble sort to sort seat array */
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < (n - 1); j++) {
                if (seat2[j].getCustomerID() > seat2[j + 1].getCustomerID()) {
                    temp = seat2[j];
                    seat2[j] = seat2[j + 1];
                    seat2[j + 1] = temp;
                }
            }
        }
        return seat2;
    }

    public void showNumEmptySeats() {
        System.out.printf("There are %d empty seats\n", this.numEmptySeat);
    }

    public void showEmptySeats() {
        if (this.numEmptySeat == 0) {
            System.out.println("There are no empty seats");
            return;
        }

        System.out.println("The following seats are empty:");
        for (int i = 0; i < seat.length; i++) {
            if (!this.seat[i].isOccupied()) {
                System.out.printf("SeatID %d\n", this.seat[i].getSeatID());
            }
        }
    }

    public void showAssignedSeats(boolean bySeatId) {
        PlaneSeat[] seat3;

        if (this.numEmptySeat == this.seat.length) {
            System.out.println("There are no occupied seats");
            return;
        }

        if (bySeatId) {
            seat3 = this.seat;
        } else {
            seat3 = sortSeats();
        }

        System.out.println("The seats assignment are as follow:");
        for (int i = 0; i < seat3.length; i++) {
            if (seat3[i].isOccupied()) {
                System.out.printf("SeatID %d assigned to CustomerID %d.\n", seat3[i].getSeatID(),
                        seat3[i].getCustomerID());
            }
        }
    }

    public void assignSeat(int seatId, int cust_id) {
        // check if empty seat
        if (this.numEmptySeat == 0) {
            System.out.println("No more empty seats.");
            return;
        }

        // check if seat is occupied
        if (this.seat[seatId - 1].isOccupied()) {
            System.out.println("Seat already assigned to a customer.");
            return;
        }

        this.numEmptySeat--;
        this.seat[seatId - 1].assign(cust_id);
        System.out.println("Seat Assigned!");
    }

    public void unAssignSeat(int seatId) {
        if (!this.seat[seatId - 1].isOccupied()) {
            System.out.println("Seat is unoccupied.");
            return;
        }

        this.numEmptySeat++;
        this.seat[seatId - 1].unAssign();
        System.out.println("Seat Unassigned!");
    }
}
