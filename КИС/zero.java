import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static ArrayList<Integer> enterDigits() {
        ArrayList<Integer> list = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            int num = scanner.nextInt();
            if (num == -1) break;
            list.add(num);
        }
        return list;
    }

    public static void bubbleSort(ArrayList<Integer> lst) {
        int n = lst.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (lst.get(j) > lst.get(j + 1)) {
                    int temp = lst.get(j);
                    lst.set(j, lst.get(j+1));
                    lst.set(j+1, temp);
                }
            }
        }
    }

    public static void coutArray(ArrayList<Integer> lst) {
        int n = lst.size();
        for (int i = 0; i < n; i++) {
            System.out.print(lst.get(i) + " ");
        }
    }

    public static void main(String[] args) {
        ArrayList<Integer> lst = enterDigits();
        bubbleSort(lst);
        coutArray(lst);
    }
}