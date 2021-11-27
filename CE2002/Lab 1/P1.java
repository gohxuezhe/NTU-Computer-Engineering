// import java library classes
// google "java api spec" to view available classes in JDK
// Scanner class is most commonly used class to get console input and others..(check API Spec)
import java.util.Scanner;

class P1 // class name - file name must be same as class name
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

        System.out.println("Please enter your choice:"); // generate question
        Scanner scanner = new Scanner(System.in); // create instance of Scanner class
        String choice = scanner.nextLine(); // prompt user for choice

        switch (choice.toLowerCase()) { // accept both lowercase and uppercase inputs
            case ("a"): // based on user's input, use switch to output print
                System.out.println("Action movie fan\n");
                break;
            case ("c"):
                System.out.println("Comedy movie fan\n");
                break;
            case ("d"):
                System.out.println("Drama movie fan\n");
                break;
            default:
                System.out.println("Invalid choice\n");
                break;
        }
        scanner.close(); // close scanner to avoid leaks
    }
}