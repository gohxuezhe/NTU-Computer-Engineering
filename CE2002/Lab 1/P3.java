// import java library classes
// google "java api spec" to view available classes in JDK
// Scanner class is most commonly used class to get console input and others..(check API Spec)
import java.util.Scanner;

class P3 // class name - file name must be same as class name
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
        Scanner scanner = new Scanner(System.in); // create instance of scanner object
        System.out.println("Starting value:"); // print question for user
        Integer start = scanner.nextInt(); // prompt user for starting value

        System.out.println("Ending value:"); // print question for user
        Integer end = scanner.nextInt(); // prompt user for ending value

        System.out.println("Increment:"); // print question for user
        Integer increment = scanner.nextInt(); // prompt user for increment

        if (start > end || increment < 0) { // make sure user does not try to break code
            System.out.println("Error input!!");
        } else { // user did not try to break code
            System.out.println("US$          S$"); // table formatting
            System.out.println("---------------");

            for (int i = start; i <= end; i += increment) { // using for loop
                System.out.printf("%d           %5.2f\n", i, (i * 1.82)); // print table contents
            }

            System.out.println("US$          S$");
            System.out.println("---------------");
            int i = start; // instantiating variable to use as counter
            while (i <= end) { // using while loop
                System.out.printf("%d           %5.2f\n", i, (i * 1.82));
                i += increment; // incrementing counter
            }

            System.out.println("US$          S$");
            System.out.println("---------------");
            int j = start;
            do { // using do while loop
                System.out.printf("%d           %5.2f\n", j, (j * 1.82));
                j += increment;
            } while (j <= end);
        }
        scanner.close(); // close scanner to prevent leaks
    }
}