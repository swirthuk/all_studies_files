import java.util.*;
import java.util.regex.*;

public class First {
    // слово: буквы/цифры, внутри допускаются дефис и апостроф
    private static final Pattern WORD =
            Pattern.compile("[\\p{L}\\p{N}]+(?:[-'’][\\p{L}\\p{N}]+)*");

    private String text;
    private Map<String, Integer> wordAndCount;

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
        return (rawText == null) ? "" : rawText.trim().toLowerCase(Locale.ROOT);
    }

    public String[] splitIntoWords(String preparedText) {
        List<String> words = new ArrayList<>();
        if (preparedText != null) {
            Matcher m = WORD.matcher(preparedText);
            while (m.find()) {
                words.add(m.group());
            }
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

    while (running) {
        System.out.println();
        System.out.println("1 - Ввести текст");
        System.out.println("2 - Подсчитать слова");
        System.out.println("3 - Вывести результат");
        System.out.println("0 - Выход");
        System.out.print("Выбор: ");

        String choice = scanner.nextLine().trim();

        switch (choice) {
            case "1":
                System.out.println("Введите текст:");
                setText(scanner.nextLine());
                break;
            case "2":
                if (text.isEmpty()) {
                    System.out.println("Сначала введите текст");
                } else {
                    analyze();
                    System.out.println("Подсчёт выполнен");
                }
                break;
            case "3":
                printResult();
                break;
            case "0":
                running = false;
                break;
            default:
                System.out.println("Неверный пункт меню");
        }
    }
}

    public void printResult() {
        if (wordAndCount.isEmpty()) {
            System.out.println("Слов в тексте нет");
            return;
        }
        wordAndCount.forEach((w, c) -> System.out.println(w + " - " + c));
    }
}