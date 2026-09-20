import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class First {
    // Конструкторы
    // геттеры и сеттеры

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
        System.out.println("Minimal string is " + minWord + "\nIts length is " + minLen);
    }

    public void repetitionOfWords(String text) {
        String[] words = text.trim().split("[\\s.,?!]+");
        Map<String, Integer> wordAndCount = new HashMap<>();

        for (String word : words) {
            if (wordAndCount.containsKey(word)) {
                int count = wordAndCount.get(word);
                wordAndCount.put(word, count + 1);
            } else {
                wordAndCount.put(word, 1);
            }
        }

        for (String word : wordAndCount.keySet()) {
            System.out.println(word + " - " + wordAndCount.get(word));
        }
    }
}