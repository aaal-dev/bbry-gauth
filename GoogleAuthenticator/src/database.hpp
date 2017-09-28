/*
 * database.hpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: ArAkinin
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <QObject>

class Database : public QObject {
    Q_OBJECT

public:
    QString DB_NAME;
    Database(QObject *parent);
    virtual ~Database();
    bool initialization();
    bool readData();
    bool writeData();
    bool updateData();
    bool deleteData();
};

#endif /* DATABASE_HPP_ */
