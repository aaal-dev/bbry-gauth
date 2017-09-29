/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#include "database.hpp"

#include <bb/system/SystemDialog>

#include <QDebug>
#include <QtSql>
#include <QDateTime>



Database :: Database (QObject *parent) : QObject(parent), DB_NAME("./data/gauth.db") {
    m_id = 0;
    m_title = "";
    m_authLogin = "";
    m_secretCode = "";
    m_keyLenght = 6;
    m_authType = 0;
    m_counter = 0;
    m_publishDate = "";
    m_editDate = "";
}

Database :: ~Database () {

}

bool Database :: createDatabase () {
    bool success = false;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_NAME);
    if (database.open()) {
        //alert(tr("Database created/registered."));
        success = true;
    } else {
        // If the database fails to open, error information can be accessed via
        // the lastError function.
        const QSqlError error = database.lastError();
        //alert(tr("Error opening connection to the database: %1").arg(error.text()));
    }
    database.close();
    return success;
}

bool Database :: deleteDatabase () {
    bool success = false;
    QSqlDatabase database=QSqlDatabase::database();
    QString connectionName=database.connectionName();
    if(database.open()){
        database.removeDatabase(connectionName);
        //alert(tr("Database deleted"));
        success = true;
    }else{
        //alert(tr("Sql database might not yet created or it is already deleted"));
    }
    database.close();
    return success;
}

bool Database :: createTable () {
    bool success = false;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        qDebug() << database.isValid();
        return success;
    }
    if (!database.open()) {
        qDebug() << "\nDatabase NOT opened." ;
        return success;
    }
    QSqlQuery query(database);
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
    if (query.exec()) {
        //alert(tr("Table creation query execute successfully"));
        success = true;
    } else {
        const QSqlError error = query.lastError();
        //alert(tr("Create table error: %1").arg(error.text()));
    }
    database.close();
    return success;
}

bool Database :: dropTable () {
    bool success = false;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        qDebug() << database.isValid();
        return success;
    }
    if (!database.open()) {
        qDebug() << "\nDatabase NOT opened." ;
        return success;
    }
    QSqlQuery query(database);
    query.prepare("DROP TABLE IF EXISTS accounts");
    if (query.exec()) {
        //alert(tr("Table drop query execute successfully"));
        success = true;
    } else {
        const QSqlError error = query.lastError();
        //alert(tr("Drop table error: %1").arg(error.text()));
    }
    database.close();
    return success;
}

bool Database :: createRecord () {
    bool success = false;
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.tables().contains("customers")) {
        //alert(tr("Create record error: customers table does not exist."));
        return success;
    }
    QSqlQuery query(database);
    query.prepare(
            "INSERT INTO accounts "
            "(title, auth_login, secret_code, key_lenght, auth_type, publish_date) "
            "VALUES (:title, :auth_login, :secret_code, :key_lenght, :auth_type, :publish_date)"
    );
    query.bindValue(":title", m_title);
    query.bindValue(":auth_login", m_authLogin);
    query.bindValue(":secret_code", m_secretCode);
    query.bindValue(":key_lenght", m_keyLenght);
    query.bindValue(":auth_type", m_authType);
    query.bindValue(":publish_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if (query.exec()) {
        //alert(tr("Record created"));
        success = true;
    } else {
        const QSqlError error = query.lastError();
        //alert(tr("Create record error: %1").arg(error.text()));
    }
    database.close();
    return success;
}

bool Database :: updateData () {
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

    query.bindValue(":id", m_id);
    query.bindValue(":auth_login", m_authLogin);
    query.bindValue(":secret_code", m_secretCode);
    query.bindValue(":key_lenght", m_keyLenght);
    query.bindValue(":auth_type", m_authType);
    query.bindValue(":publish_date", m_publishDate);
    query.bindValue(":edit_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    bool success = query.exec();
    return success;
}

bool Database :: deleteData () {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM accounts WHERE id=:id");
    query.bindValue(":id", m_id);
    bool success = query.exec();
    db.close();
    return success;
}

bool Database :: readData () {
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);

    query.prepare("SELECT * FROM accounts");

    if(query.exec()){
        while(query.next()){

        }
        return true;
    }else{
        return false;
    }
}



int Database :: getId () {
    return m_id;
}

void Database :: setId (int id) {
    m_id = id;
    emit idValueChanged(m_id);
}



QString Database :: getTitle () {
    return m_title;
}

void Database :: setTitle (QString title) {
    m_title = title;
    emit titleValueChanged(m_title);
}



QString Database :: getAuthLogin () {
    return m_authLogin;
}

void Database :: setAuthLogin (QString authLogin) {
    m_authLogin = authLogin;
    emit authLoginValueChanged(m_authLogin);
}



QString Database :: getSecretCode () {
    return m_secretCode;
}

void Database :: setSecretCode (QString secretCode) {
    m_secretCode = secretCode;
    emit secretCodeValueChanged(m_secretCode);
}



int Database :: getKeyLenght () {
    return m_keyLenght;
}

void Database :: setKeyLenght (int keyLenght) {
    m_keyLenght = keyLenght;
    emit keyLenghtValueChanged(m_keyLenght);
}



int Database :: getAuthType () {
    return m_authType;
}

void Database :: setAuthType (int authType) {
    m_authType = authType;
    emit authTypeValueChanged(m_authType);
}



int Database :: getCounter(){
    return m_counter;
}

void Database :: setCounter (int counter) {
    m_counter = counter;
    emit counterValueChanged(m_counter);
}



QString Database :: getPublishDate () {
    return m_publishDate;
}

void Database :: setPublishDate (QString publishDate) {
    m_publishDate = publishDate;
    emit publishDateValueChanged(m_publishDate);
}



QString Database :: getEditDate () {
    return m_editDate;
}

void Database :: setEditDate (QString editDate) {
    m_editDate = editDate;
    emit editDateValueChanged(m_editDate);
}



