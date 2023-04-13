#ifndef DB_H
#define DB_H

#include <QSqlQueryModel>
#include "storageInterface.h"

class Db : storageInterface
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
