#include "mainwindow.h"
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    service = {
        "GitHub",
        "https://github.com/",
        "user1",
        "*****",
        "test test test",
        ""
    };

    setWindowTitle(tr("Диспетчер паролей"));

    QWidget *centralWidget = new QWidget(this);
    QGridLayout *centralWidgetLayout = new QGridLayout(centralWidget);

    QVBoxLayout *leftSection = m_getCategoriesLayout();
    QVBoxLayout *rightSection = m_getServicesLayout();
    QGridLayout *bottomSection = m_getDetailsLayout();

    centralWidgetLayout->addLayout(leftSection, 0, 0);
    centralWidgetLayout->addLayout(rightSection, 0, 1);
    centralWidgetLayout->addLayout(bottomSection, 1, 0, 1, 2);

   setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}

QVBoxLayout *MainWindow::m_getCategoriesLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *layoutLabel = new QLabel(tr("Категория:"));

    // Временная реализация модели
    QStringListModel *categoriesModel = new QStringListModel();
    QStringList list;
    list << "Работа" << "Соцсети" << "Разное";
    categoriesModel->setStringList(list);

    QListView *categoriesListView = new QListView();

    categoriesListView->setWordWrap(true);
    categoriesListView->setModel(categoriesModel);
    categoriesListView->setCurrentIndex(categoriesModel->index(0, 0));

    layout->addWidget(layoutLabel);
    layout->addWidget(categoriesListView);

    return layout;
}

QVBoxLayout *MainWindow::m_getServicesLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *layoutLabel = new QLabel(tr("Сервис:"));

    // Временная реализация модели
    QStringListModel *servicesModel = new QStringListModel();
    QStringList list;
    list << "GitHub" << "GitLab" << "Jira" << "VPN";
    servicesModel->setStringList(list);

    QListView *servicesListView = new QListView();
    servicesListView->setModel(servicesModel);

    layout->addWidget(layoutLabel);
    layout->addWidget(servicesListView);

    return layout;
}

QGridLayout *MainWindow::m_getDetailsLayout()
{
    QGridLayout *layout = new QGridLayout();

    QLabel *urlLabel = new QLabel(tr("URL:"));
    urlLine = new QLineEdit(service.URL, this);
    urlLine->setReadOnly(true);
    layout->addWidget(urlLabel, 0, 0);
    layout->addWidget(urlLine, 0, 1, 1, 2);

    QLabel *usernameLabel = new QLabel(tr("Пользователь:"));
    usernameLine = new QLineEdit(service.username, this);
    usernameLine->setReadOnly(true);
    layout->addWidget(usernameLabel, 1, 0);
    layout->addWidget(usernameLine, 1, 1, 1, 2);

    QLabel *passwordLabel = new QLabel(tr("Пароль:"));
    passwordLine = new QLineEdit(service.password, this);
    passwordLine->setReadOnly(true);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordLine, 2, 1);

    copyButton = new QPushButton(tr("Скопировать пароль в буфер"));
    layout->addWidget(copyButton, 2, 2);

    QLabel *commentLabel = new QLabel(tr("Комментарий:"));
    commentLine = new QLineEdit(service.comment, this); // QTextEdit(service.comment, this);
    commentLine->setReadOnly(true);

    layout->addWidget(commentLabel, 3, 0, Qt::AlignTop);
    layout->addWidget(commentLine, 3, 1, 1, 2);


    layout->addLayout(m_getDetailsButtons(), 4, 1, 1, 2);

    return layout;
}

QGridLayout *MainWindow::m_getDetailsButtons()
{
    QGridLayout *layout = new QGridLayout;

    showPasswordButton = new QPushButton(tr("Показать пароль"));
    editButton = new QPushButton(tr("Редактировать"));
    connect(editButton, SIGNAL(clicked()),this,SLOT(m_editModeEnter()));
    // Еще нужно копирование пароля в буфер
    layout->addWidget(showPasswordButton, 0, 0);
    layout->addWidget(editButton, 0, 1);

    generateButton = new QPushButton(tr("Сгенерировать пароль"));
    saveButton = new QPushButton(tr("Сохранить"));
    connect(saveButton, SIGNAL(clicked()),this,SLOT(m_editModeExit()));
    layout->addWidget(generateButton, 1, 0);
    layout->addWidget(saveButton, 1, 1);
    generateButton->setHidden(true);
    saveButton->setHidden(true);

    return layout;
}

void MainWindow::m_editModeEnter()
{
    copyButton->setEnabled(false);
    showPasswordButton->setHidden(true);
    editButton->setHidden(true);
    generateButton->setHidden(false);
    saveButton->setHidden(false);
}

void MainWindow::m_editModeExit()
{
    copyButton->setEnabled(true);
    showPasswordButton->setHidden(false);
    editButton->setHidden(false);
    generateButton->setHidden(true);
    saveButton->setHidden(true);
}
