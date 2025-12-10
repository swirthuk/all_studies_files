A = 'GNP measures the total income of the economy';
file1 = mopen('myexample.bin', 'wb');
mput(ascii(A), 'uc', file1);
mclose(file1);
file2 = mopen('myexample.bin', 'rb');
data = mget(length(A), 'uc', file2);
mclose(file2);
readStr = ascii(data);
mprintf("Данные:"); disp(readStr);
B = ['GNP measures'; 'the total income'; 'of the economy'];
file3 = mopen('myexample.txt', 'w');
for i = 1:size(B, 1)
    mfprintf(file3, '%s\n', B(i));
end
mclose(file3);
file4 = mopen('myexample.txt', 'r');
firstLine = mgetl(file4, 1);
mprintf("Первая строка:"); disp(firstLine);
threeChars = mgetstr(3, file4);
mprintf("Первые 3 символа:"); disp(threeChars);
remainingChars = mgetstr(-1, file4);
mprintf("Оставшиеся символы:"); disp(remainingChars);
mseek(0, file4);
words = mfscanf(4, '%s %s %s %s %s');
mclose(file4);
mprintf("Пять слов из файла:"); disp(words);
a = 15; b = -15;
mprintf("Значения %.f и %.f:",a,b);
