public class PlaneSeat {
    private int seatID = 0;
    private boolean assigned = false;
    private int customerId = 0;

    public PlaneSeat(int seatID) {
        this.seatID = seatID;
    }

    public int getSeatID() {
        return this.seatID;
    }

    public int getCustomerID() {
        return this.customerId;
    }

    public boolean isOccupied() {
        return this.assigned;
    }

    public void assign(int cust_id) {
        this.customerId = cust_id;
        assigned = true;
    }

    public void unAssign() {
        this.customerId = 0;
        this.assigned = false;
    }

}
