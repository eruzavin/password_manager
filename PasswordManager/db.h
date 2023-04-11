#ifndef DB_H
#define DB_H

#include <QSqlQueryModel>

class Db
{
public:
    Db();
    QSqlQueryModel* getCategories();

private:
    bool dbFileExists(QString path);
    void m_connect();
    void showError(QString errorMessage);
};

#endif // DB_H
