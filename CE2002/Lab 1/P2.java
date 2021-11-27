// import java library classes
// google "java api spec" to view available classes in JDK
// Scanner class is most commonly used class to get console input and others..(check API Spec)
import java.util.Scanner;

class P2 // class name - file name must be same as class name
{
    // // for a start, use "public static" when defining your methods (function)
    // // "public static" make the method global just like 'C'
    // // when you have learnt OO, you will use LESS of static
    // public static <return type> methodname(<argument list>) {
    // //write your code here
    // // think in 'C' syntax
    // }

    // entry into a Java program - in 'C' is int main()
    public static void main(String args[]) {
        // write your code here
        // think in 'C' syntax
        // use "System.out.println" for output display
        // "System.out.println" uses "+" to concatenate (join) String and other variable
        // data
        Scanner scanner = new Scanner(System.in); // create instance of Scanner class

        System.out.println("Please enter your salary:"); // create question for salary
        Integer salary = scanner.nextInt(); // prompt user for salary

        System.out.println("Please enter your merit points:"); // create question for merit
        Integer merit = scanner.nextInt(); // prompt user for merit point

        String grade = new String(); // create empty string to store grade

        if (700 <= salary && salary <= 899) { // if loop to check for salary range
            if (salary <= 799 && merit <= 20) { // check if user qualifies for upper grade
                grade = "B"; // user did not qualify for upper grade and set grade
            } else {
                grade = "A"; // user qualify for upper grade and set grade
            }
        } else if (600 <= salary && salary <= 799) { // if loop to check for salary range
            if (salary <= 649 && merit < 10) { // check if user qualifies for upper grade
                grade = "C"; // user did not qualify for upper grade and set grade
            } else {
                grade = "B"; // user qualify for upper grade and set grade
            }
        } else if (500 <= salary && salary <= 649) {
            grade = "C";
        }
        System.out.printf("salary: %d, merit: %d - Grade %s", salary, merit, grade); // use formatted string to output
                                                                                     // result
        scanner.close(); // close scanner object to prevent leaks
    }
}
