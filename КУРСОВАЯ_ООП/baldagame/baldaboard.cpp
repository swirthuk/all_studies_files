#include "baldaboard.h"
#include <QGridLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

BaldaBoard::BaldaBoard(QWidget *parent)
    : QFrame(parent),
    curPos(-1),
    addLetter(false),
    isStarted(false),
    isPlayerTurn(true)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setEnabled(false);

    board = new QButtonGroup(this);
    board->setExclusive(false);

    QGridLayout *layout = new QGridLayout(this);

    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < colSize; ++j) {
            QPushButton *btn = new QPushButton("");
            btn->setMinimumSize(50, 50);
            btn->setStyleSheet(
                "QPushButton { font-size: 18pt; font-weight: bold; }"
                );

            int id = i * colSize + j;
            board->addButton(btn, id);
            layout->addWidget(btn, i, j);
        }
    }

    connect(board, SIGNAL(buttonClicked(int)),
            this, SLOT(onBoardClicked(int)));
    connect(&timer, SIGNAL(timeout()),
            this, SLOT(timeOutSlot()));

    loadDictionary();
}

void BaldaBoard::loadDictionary()
{
    QFile file(":/dict/word_rus.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString word = in.readLine().trimmed().toUpper();
        if (!word.isEmpty())
            dictionary.insert(word);
    }
}

void BaldaBoard::curletter(const QString &l)
{
    letter = l;
}

void BaldaBoard::start()
{
    isStarted = true;
    isPlayerTurn = true;
    addLetter = false;
    player.clear();
    usedWords.clear();
    curPos = -1;

    setEnabled(true);

    time = QTime(0, 2, 0);
    emit timeChanged(time.toString("mm:ss"));
    timer.start(1000);

    placeStartWord();
}

void BaldaBoard::placeStartWord()
{
    QString word = "БАЛДА";
    int row = rowSize / 2;

    for (int i = 0; i < word.size(); ++i)
        board->button(row * colSize + i)->setText(QString(word[i]));

    usedWords.insert(word);
}

bool BaldaBoard::checkWord(const QString &word)
{
    return dictionary.contains(word) && !usedWords.contains(word);
}

void BaldaBoard::apply()
{
    if (!isPlayerTurn || playerWord.isEmpty())
        return;

    if (!checkWord(playerWord)) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Слова \"" + playerWord + "\" нет в словаре"
            );

        return;
    }

    usedWords.insert(playerWord);
    emit pl_addWord(playerWord);

    player.clear();
    playerWord.clear();
    addLetter = false;
    curPos = -1;

    for (auto *b : board->buttons())
        b->setStyleSheet("QPushButton { font-size: 18pt; font-weight: bold; }");

    isPlayerTurn = false;
    computerMove();
}

void BaldaBoard::computerMove()
{
    // ищем пустую клетку рядом с любой буквой
    for (int id = 0; id < rowSize * colSize; ++id) {
        QPushButton *cell =
            qobject_cast<QPushButton*>(board->button(id));

        if (!cell || !cell->text().isEmpty())
            continue;

        // проверяем соседей
        QVector<int> neighbors = {
            id - 1,
            id + 1,
            id - colSize,
            id + colSize
        };

        for (int n : neighbors) {
            if (n < 0 || n >= rowSize * colSize)
                continue;

            QPushButton *nb =
                qobject_cast<QPushButton*>(board->button(n));

            if (!nb || nb->text().isEmpty())
                continue;

            // пробуем все буквы алфавита
            QString alphabet = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

            for (QChar c : alphabet) {
                QString word;
                word += c;
                word += nb->text();

                if (checkWord(word)) {
                    // ✔ нашли слово

                    cell->setText(QString(c));
                    usedWords.insert(word);
                    emit comp_addWord(word);

                    // передаём ход игроку
                    isPlayerTurn = true;
                    time = QTime(0, 2, 0);
                    emit timeChanged(time.toString("mm:ss"));
                    timer.start(1000);
                    return;
                }
            }
        }
    }

    // если вообще ничего не нашли — просто передаём ход
    isPlayerTurn = true;
    time = QTime(0, 2, 0);
    emit timeChanged(time.toString("mm:ss"));
    timer.start(1000);
}


void BaldaBoard::onBoardClicked(int id)
{
    if (!isStarted || !isPlayerTurn)
        return;

    QPushButton *btn =
        qobject_cast<QPushButton*>(board->button(id));

    if (!btn)
        return;

    // постановка новой буквы
    if (!addLetter && btn->text().isEmpty()) {
        if (letter.isEmpty())
            return;

        btn->setText(letter);
        btn->setStyleSheet("QPushButton { color: red; font-size: 18pt; }");

        addLetter = true;
        player << btn;
        playerWord = letter;
        curPos = id;
        return;
    }

    if (btn->text().isEmpty())
        return;

    // отмена
    if (!player.isEmpty() && btn == player.last()) {
        btn->setStyleSheet("QPushButton { font-size: 18pt; font-weight: bold; }");
        player.pop_back();
        playerWord.chop(1);
        return;
    }

    // добавление буквы
    if (!player.contains(btn)) {
        player << btn;
        playerWord += btn->text();
        btn->setStyleSheet("QPushButton { color: red; font-size: 18pt; }");
    }
}

void BaldaBoard::timeOutSlot()
{
    time = time.addSecs(-1);
    emit timeChanged(time.toString("mm:ss"));

    if (time.minute() == 0 && time.second() == 0) {
        timer.stop();
        if (isPlayerTurn)
            computerMove();
    }
}

void BaldaBoard::pause()
{
    timer.isActive() ? timer.stop() : timer.start(1000);
}
