import java.util.Scanner;

public class PhaseOnePrime {

    public static boolean isPrime(int n){
        if(n == 1) return false;
        if(n == 2) return true;
        if(n%2 == 0) return false;

        for (int i=3; i < n; i += 2){
            if(n%i == 0) return false;
        }

        return true;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        for(int i = 1; i<1000; i++){
            System.out.printf("%d: ", i);
            System.out.println(isPrime(i));
        } 
    }
}
