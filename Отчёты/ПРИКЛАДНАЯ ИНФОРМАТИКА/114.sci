// Запись
A = 'Firms and government finance R&D activities';
file1 = mopen('myexample.bin', 'wb');
mput(ascii(A), 'uc', file1);
mclose(file1);
// Чтение
file2 = mopen('myexample.bin', 'rb');
data = mget(length(A), 'uc', file2);
mclose(file2);
readStr = ascii(data);
mprintf("Прочитано из бинарного файла:\n%s\n", readStr);
// Запись
B = ['Firms and government';
     'finance            ';
     'R&D activities     '];
file3 = mopen('myexample.txt', 'wt');
for i = 1:size(B, 1)
    mfprintf(file3, '%s\n', strsubst(B(i), '''', ''));

end
mclose(file3);

//Открытие текстового файла
file4 = mopen('myexample.txt', 'rt');
firstLine = mgetl(file4, 1);
mprintf("\nПервая строка:\n%s\n", firstLine);

// Чтение 3 символов функцией mgetstr
threeChars = mgetstr(3, file4);
mprintf("\nПервые 3 символа после первой строки:\n%s\n", threeChars);

// Чтение оставшихся символов
remainingChars = mgetstr(-1, file4);
mprintf("\nОставшиеся символы:\n%s\n", remainingChars);

// Перевод указателя на начало файла
mseek(0, file4);

// Чтение 5 слов в переменные
[word1, word2, word3, word4, word5] = mfscanf(file4, '%s %s %s %s %s');
mclose(file4);

// Вывод a = 15 и b = -15 в формате:
a = 15;
b = -15;
mprintf("\n  -->a\n      %d\n  -->b\n     %d\n", a, b);
