import java.util.Scanner;

public class PhaseOneFB {
    public static void main(String[] args) {
        boolean b_fizz, b_buzz;
        int n;
        Scanner sc = new Scanner(System.in);
        String fizz = "Fizz";
        String buzz = "Buzz";

        n = sc.nextInt();
        for (int i = 1; i < n; i++) {
            b_fizz = (i % 3 == 0);
            b_buzz = (i % 5 == 0);

            if(b_fizz){
                System.out.print(fizz);
            }
            if(b_buzz){
                System.out.print(buzz);
            }

            if (!(b_fizz || b_buzz)){
                System.out.print(i);
            }
            System.out.print('\n');
        }
    }
}