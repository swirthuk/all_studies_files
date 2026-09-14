import java.util.Scanner;

public class First {
    // Конструкторы
    //геттеры и сеттеры

    public void theShortestString(int n) {
        int minLen = 10000000;
        String minWord = "";
        Scanner scanner = new Scanner(System.in);
        String[] arr = new String[n];
        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextLine();
            if (arr[i].length() < minLen) {
                minLen = arr[i].length();
                minWord = arr[i];
            }
        }
        scanner.close();
        System.out.println("Minimal string is" + minWord + "\nIts length is " + minLen);
    }
}
