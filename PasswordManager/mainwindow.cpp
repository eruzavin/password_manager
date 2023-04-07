#include "mainwindow.h"
#include <QApplication>
#include <QContextMenuEvent>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStringListModel>
#include <QWidgetAction>
using namespace std;

const char* TEXT_PASSWORD_HIDDEN = "*****";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    service = {
        "GitHub",
        "https://github.com/",
        "user1",
        "1q2w3e",
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
    m_createActions();
    m_createMenus();

    clipboard = QApplication::clipboard();
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

    categoriesListView = new QListView();
    categoriesListView->setWordWrap(true);
    categoriesListView->setModel(categoriesModel);
    categoriesListView->setCurrentIndex(categoriesModel->index(0, 0));

//    connect(categoriesListView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

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
    passwordLine = new QLineEdit(tr(TEXT_PASSWORD_HIDDEN), this);
    passwordLine->setReadOnly(true);
    layout->addWidget(passwordLabel, 2, 0);
    layout->addWidget(passwordLine, 2, 1);

    copyButton = new QPushButton(tr("Скопировать пароль в буфер"));
    layout->addWidget(copyButton, 2, 2);
    connect(copyButton, SIGNAL(clicked()),this,SLOT(m_copyPasswordToClipboard()));

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

    showHidePasswordButton = new QPushButton(tr("Показать пароль"));
    connect(showHidePasswordButton, SIGNAL(clicked()),this,SLOT(m_showPassword()));

    editButton = new QPushButton(tr("Редактировать"));
    connect(editButton, SIGNAL(clicked()),this,SLOT(m_editModeEnter()));
    layout->addWidget(showHidePasswordButton, 0, 0);
    layout->addWidget(editButton, 0, 1);

    generateButton = new QPushButton(tr("Сгенерировать пароль"));

    cancelButton = new QPushButton(tr("Отменить"));
    connect(cancelButton, SIGNAL(clicked()),this,SLOT(m_editModeExit()));

    saveButton = new QPushButton(tr("Сохранить"));
    connect(saveButton, SIGNAL(clicked()),this,SLOT(m_editModeExit()));

    layout->addWidget(generateButton, 1, 0);
    layout->addWidget(cancelButton, 1, 1);
    layout->addWidget(saveButton, 1, 2);

    generateButton->setHidden(true);
    cancelButton->setHidden(true);
    saveButton->setHidden(true);

    return layout;
}

void MainWindow::m_editModeEnter()
{
    for (auto editline : {urlLine, usernameLine, passwordLine, commentLine}) {
        editline->setReadOnly(false);
    }

    copyButton->setEnabled(false);

    showHidePasswordButton->setHidden(true);
    editButton->setHidden(true);
    generateButton->setHidden(false);
    cancelButton->setHidden(false);
    saveButton->setHidden(false);
}

void MainWindow::m_editModeExit()
{
    for (auto editline : {urlLine, usernameLine, passwordLine, commentLine}) {
        editline->setReadOnly(true);
    }

    copyButton->setEnabled(true);

    showHidePasswordButton->setHidden(false);
    editButton->setHidden(false);
    generateButton->setHidden(true);
    cancelButton->setHidden(true);
    saveButton->setHidden(true);
}

void MainWindow::m_createMenus()
{
    menu = menuBar()->addMenu(tr("&Меню"));
    menu->addAction(addCategory);
    menu->addAction(deleteCategory);
    menu->addSeparator();
    menu->addAction(addService);
    menu->addAction(deleteService);
}

void MainWindow::m_createActions()
{
    addCategory = new QAction(tr("&Добавить категорию"), this);
    addCategory->setShortcuts(QKeySequence::New);
    addCategory->setStatusTip(tr("Добавить новую категорию"));

    deleteCategory = new QAction(tr("&Удалить выбранную категорию"), this);

    addService = new QAction(tr("&Добавить сервис"), this);
    deleteService = new QAction(tr("&Удалить выбранный сервис"), this);
}

void MainWindow::m_copyPasswordToClipboard() {
    clipboard->setText(service.password);
}

void MainWindow::m_showPassword() {
    passwordLine->setText(service.password);
    showHidePasswordButton->setText(tr("Скрыть пароль"));
    connect(showHidePasswordButton, SIGNAL(clicked()),this,SLOT(m_hidePassword()));
}

void MainWindow::m_hidePassword() {
    passwordLine->setText(tr(TEXT_PASSWORD_HIDDEN));
    showHidePasswordButton->setText(tr("Показать пароль"));
    connect(showHidePasswordButton, SIGNAL(clicked()),this,SLOT(m_showPassword()));
}
