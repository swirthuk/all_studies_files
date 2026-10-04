import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Zero {
    private ArrayList<Integer> lst;
    // static final, чтобы он был один и не пересоздавался
    private static final Scanner scanner = new Scanner(System.in);

    public Zero() {
        this.lst = new ArrayList<>();
    }

    public Zero(ArrayList<Integer> lst) {
        this.lst = new ArrayList<>(lst); // Если кто-то удалит из старого, то в новом ничего не изменится 
    }

    public Zero(Zero other) {
        this.lst = new ArrayList<>(other.lst);
    }

    public ArrayList<Integer> getLst() {
        return new ArrayList<>(lst);
    }

    public void setLst(ArrayList<Integer> lst) {
        this.lst = new ArrayList<>(lst);
    }

    public void enterDigits() {
        ArrayList<Integer> result = new ArrayList<>();
        
        do {
            System.out.println("Вводите положительные числа (минимум 2).");
            System.out.println("Чтобы закончить ввод, впишите -1.");
            boolean flag = true;
            while (flag) {
                System.out.print("-> ");
                if (scanner.hasNextInt()) {
                    int num = scanner.nextInt();
                    if (num == -1) {
                        flag = false;
                    } else if (num < 0) {
                        System.out.println("Число должно быть положительным. Попробуйте ещё раз.");
                    } else {
                        result.add(num);
                    }
                } else {
                    scanner.next(); 
                    System.out.println("Это не число, попробуй ещё раз.");
                }
            }

            if (result.size() < 2) {
                System.out.println("\nОшибка: Вы ввели менее 2-х чисел. Давайте начнем заново.\n");
            }

        } while (result.size() < 2);

        this.lst = result;
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
        int choice = 0;

        do {
            System.out.print("""
                    
                    Введите число (1 - 5):
                    1. Показать массив в прямом порядке;
                    2. Показать массив в противоположном порядке;
                    3. Ввести числа;
                    4. Сортировка по убыванию;
                    5. Сортировка по возрастанию;
                    6. Выход.
                    Выбор: """);
                    
            if (scanner.hasNextInt()) {
                choice = scanner.nextInt();
                switch (choice) {
                    case 1:
                        if (hasEnoughData()) {
                            coutArrayForward();
                        } else {
                            System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                        }
                        break;
                    case 2:
                        if (hasEnoughData()) {
                            coutArrayBack();
                        } else {
                            System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                        }
                        break;
                    case 3:
                        enterDigits();
                        break;
                    case 4:
                        if (hasEnoughData()) {
                            sortDesc();
                            System.out.println("Массив отсортирован по убыванию.");
                        } else {
                            System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                        }
                        break;
                    case 5:
                        if (hasEnoughData()) {
                            sortAsc();
                            System.out.println("Массив отсортирован по возрастанию.");
                        } else {
                            System.out.println("Недостаточно данных. Сначала заполните массив (минимум 2 числа).");
                        }
                        break;
                    case 6:
                        System.out.println("Завершение работы.");
                        break;
                    default:
                        System.out.println("Нет такого пункта.");
                }
            } else {
                scanner.next();
                System.out.println("Введите корректное число.");
            }
        } while (choice != 6);
    }

    public void coutArrayForward() {
        for (int num : this.lst) {
            System.out.print(num + " ");
        }
        System.out.println();
    }

    public void coutArrayBack() {
        for (int i = this.lst.size() - 1; i >= 0; i--) {
            System.out.print(this.lst.get(i) + " ");
        }
        System.out.println();
    }
}