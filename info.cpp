#include "info.h"

info::info(QDialog *parent) : QDialog(parent)
{

    QVBoxLayout *vertBox = new QVBoxLayout(this); // создание вертикального компоновщика
    QFormLayout *flayout = new QFormLayout(this); // создание компоновщика для Описание-QLabel

    mainmenu = new QPushButton("Вернуться в меню", this); // Создание кнопки для возврата в главное окно
    mainmenu->setFixedSize(180,30); // Установка фиксированного размера кнопки

    // -------------------------------------------------------

    QString kernel = QSysInfo::kernelType(); // Информация о типе ядра
    QString typeOS = QSysInfo::prettyProductName(); // Информация об ОС

    // -------------------------------------------------------

    infotext = new QLabel(this); // Создание виджета дял текстового описания
    infotext->setText("Morning Star - Zero\n"); // установка текста

    infodev = new QLabel(this); // Создание виджета для текстового описания
    infodev->setText("Рарработчик:  Eixini Software"); //устанвока текста

    labkernel = new QLabel(kernel);
    labtypeos = new QLabel(typeOS);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ Настройка кнопки ~~~~~~~~~~~~~~~~~~~~~~~~~~

    connect(mainmenu,&QPushButton::clicked, this, &QDialog::accept); // сигнал Нажатие кнопки - принятие и возврат к главному окну

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    flayout->setLabelAlignment(Qt::AlignRight | Qt::AlignVCenter); // Выравнивание описания

    flayout->addRow("Тип ядра: ", labkernel);          // создание компоновки описание - текст
    flayout->addRow("ОС: ", labtypeos);                // создание компоновки описание - текст


    // Добавление виджетов в вертикальный компоновщик , а так же редактирование расположения в компоновщике
    vertBox->addWidget(infotext,1, Qt::AlignHCenter);
    vertBox->addWidget(infodev,1,Qt::AlignLeft);
    vertBox->addLayout(flayout, Qt::AlignHCenter);
    vertBox->addWidget(mainmenu,1, Qt::AlignHCenter);

    setLayout(vertBox); // установка компоновщика в качестве главного
}

info::~info()
{
}
