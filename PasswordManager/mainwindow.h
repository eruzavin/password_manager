#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
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
    QLineEdit *commentLine;
    QLineEdit *dateModifiedLine;
    QLineEdit *passwordLine;
    QLineEdit *urlLine;
    QLineEdit *usernameLine;
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


private slots:
    void m_editModeEnter();
    void m_editModeExit();
};
#endif // MAINWINDOW_H
