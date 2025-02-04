#include "note.h"

note::note(QDialog *parent) : QDialog(parent)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~  ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное меню
    addButton = new QPushButton("Добавить заметку", this); // Создание кнопки для добавления новой заметки
    editButton = new QPushButton("Редактировать заметку", this); // Создание кнопки для редактирования существующей заметки
    removeButton = new QPushButton("Удалить заметку" ,this); // Создание кнопки для удаления заметки

    hbox = new QHBoxLayout(this); // Создание горизонтального компоновщика
    vbox = new QVBoxLayout(); // Создание вертикального компоновщика

    notelist = new QListWidget(this); // Создание списка

    // ***********************  ПОДКЛЮЧЕНИЕ СИГНАЛОВ К СЛОТАМ  **************************

    connect(mainmenu, &QPushButton::clicked, this, &note::saveNote); // При нажатии на кнопку, перед возвратом в главное меню будет происходить сохр. заметок
    connect(mainmenu, &QPushButton::clicked, this, &QDialog::accept); // При нажатии на кнопку, будет произведен возврат в главное меню 
    connect(addButton, &QPushButton::clicked, this, &note::addNote); // При нажатии на кнопку, появляется окно для создания новой заметки
    connect(editButton, &QPushButton::clicked,this, &note::editNote); // При нажатии на кнопку, появляется окно для редактирования заметки
    connect(removeButton, &QPushButton::clicked, this, &note::removeNote); // При нажатии на кнопку, выбранная заметка удаляется

    // ^^^^^^^^^^^^^^^^^^^^^^^^     УПРАВЛЕНИЕ КОМПОНОВКОЙ     ^^^^^^^^^^^^^^^^^^^^^^^^^^

    // Настройка компоновки кнопок
    vbox->addSpacing(5); // Установка расстояния между кнопками
    vbox->addStretch(1); // Добавление коэффициента растяжения сверху
    vbox->addWidget(addButton);
    vbox->addWidget(editButton);
    vbox->addWidget(removeButton);
    vbox->addStretch(1); // Добавление коэффициента растяжения снизу
    vbox->addWidget(mainmenu);

    hbox->addWidget(notelist);
    hbox->addLayout(vbox);

    setLayout(hbox); // Установка виджета в качестве основного

}

void note::addNote() // Добавление новой заметки
{   notelist->addItem("New Note");  }

void note::editNote()
{
// Редактирвоание существующей заметки

    editNoteWin = new QDialog(this);
    editNoteWin->show();

    editTitleNote = new QLineEdit(this); // Создание текстовой строки для названия заметки
    editNoteVBox = new QVBoxLayout(editNoteWin); // Создание компоновщика
    formLineEdit = new QFormLayout(); // СОздание компоновщика для подписи текста
    hint = new QLabel("Введите строку. Нажмите Enter. Закройте окно.", this);

    // ------------------  Настройка элементов  -------------------------

    editNoteWin->setWindowTitle("Редактирование заметки");
    editNoteWin->setMinimumWidth(500); // Установка минимальной ширины
    editNoteWin->setFixedHeight(90); // Установка фиксированной высоты

    // +++++++++++++++++++ Работа с Сигналами ++++++++++++++++++++++++++++

    connect(editTitleNote, &QLineEdit::editingFinished,this,&note::setNoteNameText);

    // ======================== Компноновка ==============================

    formLineEdit->addRow("Название: ",editTitleNote);
    editNoteVBox->addLayout(formLineEdit);
    editNoteVBox->addWidget(hint);

}

void note::removeNote() // Удаление заметки
{

    if(notelist)
    {
               QList< QListWidgetItem* > items = notelist->selectedItems();
               foreach( QListWidgetItem* item, items )
               {
                   int row = notelist->row( item );
                   notelist->takeItem( row );
                   delete item;
               }
    }

}

void note::setNoteNameText()
{
    notelist->selectedItems()[0]->setText(editTitleNote->text()); // Установка текста в элемент QListWidget
}

void note::note_read() // Слот для считывания заметок из файла и запись их в объект класса QListWidget
{
    QMessageBox::warning(this, "Информация","Идет проверка данных."); // Пока что нужно для отладки

    // Проверка, существует ли файл

    QString path = QStandardPaths::locate(QStandardPaths::ConfigLocation , "note_morningstar.txt");
    QString loc = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);

    if(path != "")
     {
        QMessageBox::warning(this, "Информация", "Файл найден!");
        QFile noteTxt(path); // Создание объекта для работы с файлом

        noteTxt.open(QIODevice::ReadOnly); // Открытие файла (и установка режима - только чтение)

        if(noteTxt.isOpen())        {   QMessageBox::warning(this, "Инфо",  "Файл успешно открыт!"); }
        else                        {   QMessageBox::warning(this, "Ошибка","Файл не открыт!");      }

        // -------------------------- СЧИТЫВАНИЕ ДАННЫХ ИЗ ТЕКСТОВОГО ФАЙЛА И ЗАПИСЬ В СПИСОК ------------------------------

        while(!noteTxt.atEnd())
        {
            notelist->addItem(noteTxt.readLine().trimmed()); // Создание объекта QListWidget при открытии окна
        }

        noteTxt.close(); // Закрытие файла
     }
    else
    {
        QMessageBox::warning(this, "Информация", "Файл не найден! Создается новый!");
        QString loc = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
        QFile note_file(loc + "/note_morningstar.txt");
        note_file.open(QIODevice::WriteOnly);
        note_file.close();
    }

}

void note::saveNote() // слот для сохранение изменений в файл перед закрытием окна заметок
{
    // Проверка, существует ли файл , открыт ли файл, доступен ли он для считывание информации и т.д
        QString path = QStandardPaths::locate(QStandardPaths::ConfigLocation , "note_morningstar.txt");
        QFile noteTxt(path); // Создание объекта для работы с файлом
        noteTxt.open(QIODevice::WriteOnly); // Открытие файла (и установка режима - только чтение)

        // Запись в файл конечный результата работы (что имеется в списке QListWidget)

        if(notelist)
        {
            for (int i = 0; i < notelist->count(); ++i)
            {
              QListWidgetItem* item = notelist->item(i);
              noteTxt.write(item->text().toUtf8());
              noteTxt.write("\n");
            }
        }
        noteTxt.close(); // Закрытие файла
}

note::~note() {}
