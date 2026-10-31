import java.util.Scanner;

class Second {
    private String password;

    private static final String COLOR_GREEN = "\u001B[32m";
    private static final String COLOR_RESET = "\u001B[0m";
    private static final int MIN_PASSWORD_LENGTH = 8;
    private static final int CONSOLE_WIDTH = 80;

    public Second() {
        this.password = "";
    }

    public Second(String password) {
        this.password = password;
    }

    public Second(Second other) {
        this.password = other.password;
    }

    private void inputPassword(Scanner scanner) {
        System.out.print("Введите пароль: ");
        this.password = scanner.nextLine();
    }

    private void printPassword() {
        System.out.println("Текущий пароль: " + (password.isEmpty() ? "(не задан)" : password));
    }

    private boolean checkLength() {
        return password != null && password.length() >= MIN_PASSWORD_LENGTH;
    }

    private boolean checkAllowedCharacters() {
        return password != null && password.matches("\\w+");
    }

    private boolean checkUppercase() {
        return password != null && password.matches(".*[A-Z].*");
    }

    private boolean checkLowercase() {
        return password != null && password.matches(".*[a-z].*");
    }

    private boolean checkDigit() {
        return password != null && password.matches(".*\\d.*");
    }

    private boolean isSecure() {
        if (password == null || password.isEmpty()) {
            return false;
        }
        
        return checkLength() && checkAllowedCharacters() && checkUppercase() && checkLowercase() && checkDigit();
    }

    private void displayResult() {
        if (password.isEmpty()) {
            System.out.println("Пароль не задан. Сначала введите пароль.");
            return;
        }
        
        if (isSecure()) {
            System.out.println("Результат: Пароль НАДЕЖНЫЙ.");
        } else {
            System.out.println("Результат: Пароль НЕнадежный (не соответствует требованиям).");
            System.out.println("1. Английские символы.");
            System.out.println("2. Должен содержать как минимум одну заглавную и маленькую буквы.");
            System.out.println("3. Должен содержать цифру.");
        }
    }

    private void printCentered(String text, boolean isHeader) {
        int consoleWidth = CONSOLE_WIDTH;
        int spacesNeeded = (consoleWidth - text.length()) / 2;
        
        String indent = "";
        for (int i = 0; i < Math.max(0, spacesNeeded); i++) {
            indent += " ";
        }
        
        if (isHeader) {
            System.out.println(indent + COLOR_GREEN + text + COLOR_RESET);
        } else {
            System.out.println(indent + text);
        }
    }

    public void menu() {
        Scanner scanner = new Scanner(System.in);
        boolean isRunning = true;

        while (isRunning) {
            System.out.println();
            printCentered("МЕНЮ УПРАВЛЕНИЯ", true);
            printCentered("1. Ввести пароль", false);
            printCentered("2. Проверить надежность введенного пароля", false);
            printCentered("3. Показать введенный пароль", false);
            printCentered("0. Выход", false);
            System.out.println();
            
            System.out.print("Ваш выбор: ");
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    inputPassword(scanner);
                    break;
                case "2":
                    displayResult();
                    break;
                case "3":
                    printPassword();
                    break;
                case "0":
                    isRunning = false;
                    System.out.println("Завершение работы программы...");
                    break;
                default:
                    System.out.println("Неверный ввод. Выберите пункт меню от 0 до 3.");
            }
        }
        
        scanner.close();
    }
}