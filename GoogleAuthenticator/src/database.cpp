/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: ArAkinin
 */

#include "database.hpp"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>


Database :: Database (QObject *parent) : QObject(parent), DB_NAME("./data/gauth.db") {

}

Database :: ~Database () {

}

bool Database :: initialization(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_NAME);

    if (db.isValid() == false) {
        qDebug() << db.isValid();
        return false;
    }

    if (db.open() == false) {
        qDebug() << "\nDatabase NOT opened." ;
        return false;
    }

    qDebug() << "Database created" << db.open();

    QSqlQuery query(db);

    query.prepare(
        "CREATE TABLE IF NOT EXISTS accounts"
        "   (id INTEGER PRIMARY KEY, "
        "   title TEXT NOT NULL, "
        "   auth_login TEXT NOT NULL, "
        "   secret_code TEXT NOT NULL,"
        "   key_lenght INTEGER DEFAULT 6, "
        "   auth_type INTEGER DEFAULT 0, "
        "   counter INTEGER DEFAULT 0, "
        "   publish_date TEXT NOT NULL, "
        "   edit_date TEXT)"
    );
    bool success = query.exec();
    return success;
}

bool Database :: readData(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.prepare("SELECT * FROM accounts");

    if(query.exec()){
        while(query.next()){

        }
        return true;
    }else{
        return false;
    }
}

bool Database :: writeData(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.prepare(
            "INSERT INTO accounts "
            "(title, auth_login, secret_code, key_lenght, auth_type, publish_date) "
            "VALUES (:title, :auth_login, :secret_code, :key_lenght, :auth_type, :publish_date)"
    );

    //query.bindValue(":title", title);
    //query.bindValue(":auth_login", auth_login);
    //query.bindValue(":secret_code", secret_code);
    //query.bindValue(":key_lenght", key_lenght);
    //query.bindValue(":auth_type", auth_type);
    query.bindValue(":publish_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    bool success = query.exec();
    return success;
}

bool Database :: updateData(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.prepare(
            "UPDATE accounts "
            "SET "
            "   title=:title, "
            "   auth_login=:auth_login, "
            "   secret_code=:secret_code, "
            "   key_lenght=:key_lenght, "
            "   auth_type=:auth_type, "
            "   publish_date=:publish_date, "
            "   edit_date=:edit_date "
            "WHERE id=:id"
    );

    //query.bindValue(":id", id);
    //query.bindValue(":auth_login", auth_login);
    //query.bindValue(":secret_code", secret_code);
    //query.bindValue(":key_lenght", key_lenght);
    //query.bindValue(":auth_type", auth_type);
    //query.bindValue(":publish_date", publish_date);
    query.bindValue(":edit_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    bool success = query.exec();
    return success;
}

bool Database :: deleteData(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM accounts WHERE id=:id");
    //query.bindValue(":id", id);
    bool success = query.exec();
    db.close();
    return success;
}
