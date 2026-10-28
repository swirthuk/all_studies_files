import java.util.*;
import java.util.regex.*;

public class First {
    //private static final Pattern WORD =
    //Pattern.compile("[\\p{L}\\p{N}]+(?:[-'’][\\p{L}\\p{N}]+)*");
    // Это определённый паттерн, который решает определенную задачу

    private String text;
    private Map<String, Integer> wordAndCount;
    // в чём преимущество перед ArrayList

    public First() {
        this("");
    }

    public First(String text) {
        this.text = (text == null) ? "" : text;
        this.wordAndCount = new LinkedHashMap<>();
    }

    public First(First other) {
        this.text = other.text;
        this.wordAndCount = new LinkedHashMap<>(other.wordAndCount);
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = (text == null) ? "" : text;
        this.wordAndCount.clear();
    }

    public Map<String, Integer> getWordAndCount() {
        return Collections.unmodifiableMap(wordAndCount);
    }

    public void setWordAndCount(Map<String, Integer> wordAndCount) {
        this.wordAndCount = (wordAndCount == null)
                ? new LinkedHashMap<>()
                : new LinkedHashMap<>(wordAndCount);
    }

    public String prepareText(String rawText) {
        return (rawText == null) ? "" : rawText.trim().toLowerCase();
    }

public String[] splitIntoWords(String preparedText) {
    List<String> words = new ArrayList<>();
    if (preparedText == null || preparedText.isEmpty()) {
        return new String[0];
    }

    StringBuilder currentWord = new StringBuilder();
    int length = preparedText.length();

    for (int i = 0; i < length; i++) {
        char ch = preparedText.charAt(i);

        if (Character.isLetter(ch) || Character.isDigit(ch)) {
            currentWord.append(ch);
        } 
        else if ((ch == '-' || ch == '\'' || ch == '’') 
                && currentWord.length() > 0 
                && i + 1 < length 
                && (Character.isLetter(preparedText.charAt(i + 1)) 
                    || Character.isDigit(preparedText.charAt(i + 1)))) {
            currentWord.append(ch);
        } 
        else {
            if (currentWord.length() > 0) {
                words.add(currentWord.toString());
                currentWord.setLength(0);
            }
        }
    }

    if (currentWord.length() > 0) {
        words.add(currentWord.toString());
    }

    return words.toArray(new String[0]);
}


    public void countWords(String[] words) {
        wordAndCount.clear();
        for (String word : words) {
            wordAndCount.merge(word, 1, Integer::sum);
        }
    }

    public void analyze() {
        String prepared = prepareText(text);
        String[] words = splitIntoWords(prepared);
        countWords(words);
    }

    public void menu() {
        Scanner scanner = new Scanner(System.in);
        boolean running = true;
        int stringLength = 80;

        while (running) {
            System.out.println();
            printCenteredWordsRainbow("1 - Ввести текст", stringLength);
            printCenteredWordsRainbow("2 - Подсчитать слова", stringLength);
            printCenteredWordsRainbow("3 - Вывести результат", stringLength);
            printCenteredWordsRainbow("0 - Выход", stringLength);

            int choiceSpaces = (stringLength - "Выбор: ".length()) / 2;
            System.out.print(" ".repeat(Math.max(0, choiceSpaces)) + "Выбор: ");

            String choice = scanner.nextLine().trim();

            switch (choice) {
                case "1":
                    System.out.println("Введите текст:");
                    setText(scanner.nextLine());
                    break;
                case "2":
                    if (text == null || text.isEmpty()) {
                        printCenteredWordsRainbow("Сначала введите текст", stringLength);
                    } else {
                        analyze();
                        printCenteredWordsRainbow("Подсчёт выполнен", stringLength);
                    }
                    break;
                case "3":
                    printResult();
                    break;
                case "0":
                    running = false;
                    break;
                default:
                    printCenteredWordsRainbow("Неверный пункт меню", stringLength);
            }
        }
    }

    private void printCenteredWordsRainbow(String text, int consoleWidth) {
        int spacesNeeded = (consoleWidth - text.length()) / 2;
        if (spacesNeeded < 0) spacesNeeded = 0;

        System.out.print(" ".repeat(spacesNeeded));

        String[] words = text.split("\\s+");

        String[] rainbow = {
            "\u001B[31m", // Красный
            "\u001B[33m", // Желтый
            "\u001B[32m", // Зеленый
            "\u001B[36m", // Циан
            "\u001B[34m", // Синий
            "\u001B[35m"  // Пурпурный
        };
        String reset = "\u001B[0m";

        for (int i = 0; i < words.length; i++) {
            String color = rainbow[i % rainbow.length];
            System.out.print(color + words[i] + reset + " ");
        }
        
        System.out.println();
    }

    public void printResult() {
        if (wordAndCount.isEmpty()) {
            System.out.println("Слов в тексте нет");
            return;
        }
        for (Map.Entry<String, Integer> entry : wordAndCount.entrySet()) {
            String word = entry.getKey();
            Integer count = entry.getValue();
            System.out.println(word + " - " + count);
        }
    }
}
