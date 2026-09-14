import java.util.ArrayList;

public class Main {
    public static void main(String args[]) {
        Zero lab = new Zero();
        ArrayList<Integer> lst = lab.enterDigits();
        lab.setLst(lst);
        lab.bubbleSort();
        lab.coutArray();
    }
}
