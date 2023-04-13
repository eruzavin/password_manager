#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H
#include <QSqlQueryModel>

class storageInterface {
    virtual QSqlQueryModel* getCategories() = 0;
};

#endif // STORAGEINTERFACE_H
