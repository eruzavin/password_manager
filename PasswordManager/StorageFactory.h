#ifndef STORAGEFACTORY_H
#define STORAGEFACTORY_H
#include "db.h"

class StorageFactory
{
public:
    Db *createStorage()
    {
        return new Db();
    };
};

#endif // STORAGEFACTORY_H
