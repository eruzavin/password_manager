#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <db.h>
using namespace std;

const QString DB_FILE_NAME = "pm.db";

Db::Db()
{
    m_connect();
}

void Db::m_connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbFile = QDir(QApplication::applicationDirPath()).filePath(DB_FILE_NAME);
    if (!dbFileExists(dbFile)) {
        showError("Файл базы данных " + DB_FILE_NAME + " не найден в текущей директории");
        exit(1);
    }

    db.setDatabaseName(dbFile);

    if (!db.open()) {
        qDebug() << "DB opening error\n";
        exit(1);
    }
}

QSqlQueryModel* Db::getCategories()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT name FROM categories");

    return model;
}

bool Db::dbFileExists(QString path) {
    QFileInfo checkFile(path);

    return checkFile.exists() && checkFile.isFile();
}

void Db::showError(QString errorMessage)
{
    QMessageBox msgBox;
    msgBox.setText(errorMessage);
    msgBox.exec();
}
