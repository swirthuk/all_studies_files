import java.util.ArrayList;
import java.util.Scanner;

class Zero {

    private ArrayList<Integer> lst;

    public Zero() {
        this.lst = new ArrayList<>();
    }

    public Zero(ArrayList<Integer> lst) {
        this.lst = lst;
    }

    public Zero(Zero other) {
        this.lst = new ArrayList<>(other.lst);
    }

    public ArrayList<Integer> getLst() {
        return lst;
    }

    public void setLst(ArrayList<Integer> lst) {
        this.lst = lst;
    }

    public ArrayList<Integer> enterDigits() {
        ArrayList<Integer> list = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            int num = scanner.nextInt();
            if (num == -1) break;
            list.add(num);
        }
        return list;
    }

    public void bubbleSort(ArrayList<Integer> lst) {
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

    public void coutArray(ArrayList<Integer> lst) {
        int n = lst.size();
        for (int i = 0; i < n; i++) {
            System.out.print(lst.get(i) + " ");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Zero lab = new Zero();
        ArrayList<Integer> lst = lab.enterDigits();
        lab.setLst(lst);
        lab.bubbleSort(lab.getLst());
        lab.coutArray(lab.getLst());
    }
}