import java.util.ArrayList;
import java.util.Collections;
import java.util.InputMismatchException;
import java.util.Scanner;

class NotEnoughDataException extends Exception {
    public NotEnoughDataException(String message) {
        super(message);
    }
}

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

    public ArrayList<Integer> enterDigits() throws NotEnoughDataException {
        ArrayList<Integer> result = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        while (true) {
            try {
                System.out.print("""
                        Вводите положительные числа.
                        Чтобы закончить ввод впишите -1""");
                if (scanner.hasNextInt()) {
                    int num = scanner.nextInt();
                    if (num == -1 || num < 0)
                        break;
                    result.add(num);
                } else {
                    scanner.next();
                    System.out.println("Это не число, попробуй ещё раз.");
                }
            } catch (InputMismatchException e) {
                System.out.println("Ошибка ввода: " + e.getMessage());
                scanner.next();
            }
        }
        if (result.size() < 2) {
            throw new NotEnoughDataException("Нужно минимум 2 числа для сортировки.");
        }
        this.lst = result;
        return result;
    }

    public void sortAsc() {
        Collections.sort(this.lst);
    }

    public void sortDesc() {
        sortAsc();
        Collections.reverse(this.lst);
    }

    private boolean hasEnoughData() {
        return this.lst.size() > 1;
    }

    public void menu() {
        int choice;
        Scanner input = new Scanner(System.in);
        while (true) {
            System.out.print("""
                    Введите число (1 - 5):
                    0. Заполнить массив числами;
                    1. Показать массив;
                    2. Ввести числа;
                    3. Сортировка по убыванию;
                    4. Сортировка по возрастанию;
                    5. Выход.
                    Выбор: """);
            choice = input.nextInt();
            switch (choice) {
                case 0:
                    try {
                        enterDigits();
                    } catch (NotEnoughDataException e) {
                        System.out.println("Ошибка: " + e.getMessage());
                    }
                    break;
                case 1:
                    if (hasEnoughData()) {
                        coutArray();
                    } else {
                        System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                    }
                    break;
                case 3:
                    if (hasEnoughData()) {
                        sortDesc();
                    } else {
                        System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                    }
                    break;
                case 4:
                    if (hasEnoughData()) {
                        sortAsc();
                    } else {
                        System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                    }
                    break;
                case 5:
                    return;
                default:
                    System.out.println("Нет такого пункта.");
            }
        }
    }

    public void coutArray() {
        for (int num : this.lst) {
            System.out.print(num + " ");
        }
    }
}