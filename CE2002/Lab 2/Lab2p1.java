import java.lang.Math;
import java.util.Scanner;

public class Lab2p1 {
    public static void main(String[] args) {
        int choice;
        Scanner sc = new Scanner(System.in);
        do {
            System.out.println("Perform the following methods:");
            System.out.println("1: multiplication test");
            System.out.println("2: quotient using division by subtraction");
            System.out.println("3: remainder using division by subtraction");
            System.out.println("4: count the number of digits");
            System.out.println("5: position of a digit");
            System.out.println("6: extract all odd digits");
            System.out.println("7: quit");
            choice = sc.nextInt();
            switch (choice) {
                case 1: /* add mulTest() call */
                    mulTest();
                    break;
                case 2: /* add divide() call */
                    System.out.print("m = ");
                    int m_divide = sc.nextInt();
                    System.out.print("n = ");
                    int n_divide = sc.nextInt();
                    int result_divide = divide(m_divide, n_divide);
                    System.out.printf("%d/%d = %d\n", m_divide, n_divide, result_divide);
                    break;
                case 3: /* add modulus() call */
                    System.out.print("m = ");
                    int m_modulus = sc.nextInt();
                    System.out.print("n = ");
                    int n_modulus = sc.nextInt();
                    int result_modulus = modulus(m_modulus, n_modulus);
                    System.out.printf("%d %s %d = %d\n", m_modulus, "%", n_modulus, result_modulus);
                    break;
                case 4: /* add countDigits() call */
                    System.out.print("n: ");
                    int n_digits = sc.nextInt();
                    if (n_digits < 0) {
                        System.out.printf("n: %d - Error input!!!\n", n_digits);
                    } else {
                        int result_digits = countDigits(n_digits);
                        System.out.printf("n: %d - count = %d\n", n_digits, result_digits);
                    }
                    break;
                case 5: /* add position() call */
                    System.out.print("n: ");
                    int n_position = sc.nextInt();
                    System.out.print("digit: ");
                    int digit_position = sc.nextInt();
                    int result_position = position(n_position, digit_position);
                    System.out.printf("position = %d\n", result_position);
                    break;
                case 6: /* add extractOddDigits() call */
                    System.out.print("n: ");
                    long n_Odd = sc.nextLong();
                    if (n_Odd < 0) {
                        System.out.println("oddDigits = Error input!!!");
                    } else {
                        long result_Odd = extractOddDigits(n_Odd);
                        System.out.printf("oddDigits = %d\n", result_Odd);
                    }
                    break;
                case 7:
                    System.out.println("Program terminating ….");
            }
        } while (choice < 7);
        sc.close();
    }

    /* add method code here */
    public static void mulTest() {
        Scanner mulsc = new Scanner(System.in);
        int score = 0;
        int user_answer;
        for (int qn = 0; qn < 5; qn++) {
            int numberone = (int) (1 + Math.random() * 10);
            int numbertwo = (int) (1 + Math.random() * 10);
            System.out.printf("How much is %d times %d? ", numberone, numbertwo);
            user_answer = mulsc.nextInt();
            if (user_answer == numberone * numbertwo) {
                score++;
            }
        }
        System.out.printf("%d out of 5 are correct\n", score);
        mulsc.close();
    }

    public static int divide(int m, int n) {
        int counter = 0;
        while (m >= n) {
            m -= n;
            counter++;
        }
        return counter;
    }

    public static int modulus(int m, int n) {
        while (m >= n) {
            m -= n;
        }
        return m;
    }

    public static int countDigits(int n) {
        int count = 0;
        while (n > 0) {
            n /= 10;
            count++;
        }
        return count;
    }

    public static int position(int n, int digit) {
        int count = 0;
        int order = 10;
        while (n * 10 > order) {
            count++;
            if (Math.floorDiv((n % order), order / 10) == digit) {
                return count;
            } else {
                order *= 10;
            }
        }
        return -1;
    }

    public static long extractOddDigits(long n) {
        long oddDigits = 0;
        long unextracted_order = 10;
        long extracted_order = 1;

        while (n * 10 > unextracted_order) {
            long current_digit = Math.floorDiv((n % unextracted_order), unextracted_order / 10);
            if (current_digit % 2 == 1) {
                oddDigits += current_digit * extracted_order;
                extracted_order *= 10;
            }
            unextracted_order *= 10;
        }

        if (oddDigits == 0) {
            return -1;
        } else {
            return oddDigits;
        }
    }
}