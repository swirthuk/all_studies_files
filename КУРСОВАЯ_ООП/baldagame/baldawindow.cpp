#include "baldawindow.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>

BaldaWindow::BaldaWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // ===== ИГРОВОЕ ПОЛЕ =====
    board = new BaldaBoard(this);

    // ===== КНОПКИ =====
    startBtn = new QPushButton("Start");
    pauseBtn = new QPushButton("Pause");
    applyBtn = new QPushButton("Apply");

    // ===== МЕТКИ =====
    timeLabel = new QLabel("02:00");
    letterLabel = new QLabel("Буква: —");

    // ===== СПИСКИ СЛОВ =====
    playerWords = new QListWidget;
    computerWords = new QListWidget;

    // ===== ЛЕЙАУТЫ =====
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *centerLayout = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    // верхняя панель
    topLayout->addWidget(startBtn);
    topLayout->addWidget(pauseBtn);
    topLayout->addWidget(applyBtn);
    topLayout->addStretch();
    topLayout->addWidget(new QLabel("Время:"));
    topLayout->addWidget(timeLabel);

    // правая панель
    rightLayout->addWidget(new QLabel("Игрок"));
    rightLayout->addWidget(playerWords);
    rightLayout->addWidget(new QLabel("Компьютер"));
    rightLayout->addWidget(computerWords);
    rightLayout->addWidget(letterLabel);

    // центр
    centerLayout->addWidget(board, 1);
    centerLayout->addLayout(rightLayout);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(centerLayout);

    // кнопки букв
    createLetterButtons(mainLayout);

    central->setLayout(mainLayout);

    // ===== CONNECT =====
    connect(startBtn, SIGNAL(clicked()),
            this, SLOT(onStartClicked()));

    connect(pauseBtn, SIGNAL(clicked()),
            board, SLOT(pause()));

    connect(applyBtn, SIGNAL(clicked()),
            board, SLOT(apply()));

    connect(board, SIGNAL(timeChanged(QString)),
            timeLabel, SLOT(setText(QString)));

    connect(board, &BaldaBoard::pl_addWord,
            this, [this](const QString &word){
                playerWords->addItem(word);
            });

    connect(board, &BaldaBoard::comp_addWord,
            this, [this](const QString &word){
                computerWords->addItem(word);
            });


}

void BaldaWindow::createLetterButtons(QVBoxLayout *parentLayout)
{
    letterGroup = new QButtonGroup(this);
    letterGroup->setExclusive(true);

    QGridLayout *grid = new QGridLayout;
    QString letters = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

    int row = 0;
    int col = 0;

    for (int i = 0; i < letters.size(); ++i) {
        QPushButton *btn = new QPushButton(QString(letters[i]));
        btn->setCheckable(true);
        btn->setMinimumSize(30, 30);

        letterGroup->addButton(btn);
        grid->addWidget(btn, row, col);

        col++;
        if (col == 8) {
            col = 0;
            row++;
        }
    }

    parentLayout->addLayout(grid);

    connect(letterGroup,
            SIGNAL(buttonClicked(QAbstractButton*)),
            this,
            SLOT(onLetterClicked(QAbstractButton*)));
}

void BaldaWindow::onLetterClicked(QAbstractButton *button)
{
    board->curletter(button->text());
    letterLabel->setText("Буква: " + button->text());
}
void BaldaWindow::onStartClicked()
{
    playerWords->clear();
    computerWords->clear();
    board->start();
}
