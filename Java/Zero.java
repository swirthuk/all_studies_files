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
        ArrayList<Integer> lst = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            if (scanner.hasNextInt()) {
                int num = scanner.nextInt();
                if (num == -1) break;
                lst.add(num);
            }
            else scanner.next();
        }
        return lst;
    }

    public void bubbleSort() {
        int n = this.lst.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (this.lst.get(j) > this.lst.get(j + 1)) {
                    int temp = this.lst.get(j);
                    this.lst.set(j, this.lst.get(j+1));
                    this.lst.set(j+1, temp);
                }
            }
        }
    }

    public void coutArray() {
        int n = this.lst.size();
        for (int i = 0; i < n; i++) {
            System.out.print(this.lst.get(i) + " ");
        }
    }
}