import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class SectionOne {

    public static ArrayList<Integer> removeDuplicates(ArrayList<Integer> lista){
        HashSet<Integer> hset = new HashSet<>();
        hset.addAll(lista);
        return new ArrayList<>(hset);
    }

    public static int kthSmallest(ArrayList<Integer> lista, int k) {
        lista.sort((a, b) -> Integer.compare(a, b));
        return lista.get(k-1);
    }

    public static void main(String[] args) {
        int n, i, k;
        ArrayList<Integer> lista = new ArrayList<>();
        Scanner sc = new Scanner(System.in);

        n = sc.nextInt();

        for(i = 0; i<n; i++){
            lista.add(sc.nextInt());
        }
        k = sc.nextInt();

        n = kthSmallest(lista, k);

        System.out.println(n);
    }
}
