#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QListView>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
using namespace std;

typedef struct Service{
    QString name;
    QString URL;
    QString username;
    QString password;
    QString comment;
    QString dateModified;
} service_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QAction *addCategory;
    QAction *addService;
    QAction *deleteCategory;
    QAction *deleteService;
    QLineEdit *commentLine;
    QLineEdit *dateModifiedLine;
    QLineEdit *passwordLine;
    QLineEdit *urlLine;
    QLineEdit *usernameLine;
    QListView *categoriesListView;
    QMenu *categoryMenu;
    QMenu *menu;
    QMenu *serviceMenu;
    QPushButton *cancelButton;
    QPushButton *copyButton;
    QPushButton *editButton;
    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *showPasswordButton;

    service_t service;
    QGridLayout *m_getDetailsButtons();
    QGridLayout *m_getDetailsLayout();
    QHBoxLayout *m_getCategoryButtons();
    QHBoxLayout *m_getServiceButtons();
    QVBoxLayout *m_getCategoriesLayout();
    QVBoxLayout *m_getServicesLayout();
    void m_createActions();
    void m_createMenus();

private slots:
    void m_editModeEnter();
    void m_editModeExit();
//    void slotCustomMenuRequested(QPoint pos);
};
#endif // MAINWINDOW_H
