public class SalePerson implements Comparable {
    private String firstName;
    private String lastName;
    private int totalSales;

    public SalePerson(String firstName, String lastName, int totalSales) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.totalSales = totalSales;
    }

    public String toString() {
        return String.format("%s , %s : %d", this.lastName, this.firstName, this.totalSales);
    }

    public boolean equals(Object o) {
        if (o.getClass() == this.getClass()) {
            SalePerson salePerson = (SalePerson) o;
            return (this.firstName == salePerson.getFirstName() && this.lastName == salePerson.getLastName());
        }
        return false;
    }

    public int compareTo(Object o) {
        if (o.getClass() == this.getClass()) {
            SalePerson salePerson = (SalePerson) o;
            if (this.totalSales < salePerson.getTotalSales()) {
                return -1;
            } else if (this.totalSales == salePerson.getTotalSales()) {
                return this.lastName.compareTo(salePerson.getLastName());
            }
        }
        return 1;
    }

    public String getFirstName() {
        return this.firstName;
    }

    public String getLastName() {
        return this.lastName;
    }

    public int getTotalSales() {
        return this.totalSales;
    }
}
