/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#include "database.hpp"

#include <QDebug>

using namespace bb::system;

Database :: Database(QObject *parent) : QObject(parent), DB_PATH("./data/bbauth.db") {
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

Database :: ~Database() {

}

bool Database :: createDatabase() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_PATH);
    bool success = database.open();
    if (success) {
        qDebug() << "Database created/registered.";
        database.close();
    } else {
        const QSqlError error = database.lastError();
        qDebug() << "\nDatabase NOT opened.";
        qDebug() << "Error opening connection to the database: %1" << error.text();
    }
    return success;
}

bool Database :: deleteDatabase() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        database.removeDatabase(database.connectionName());
        qDebug() << "Database deleted";
        database.close();
    }else{
        qDebug() << "Sql database might not yet created or it is already deleted";
    }
    return success;
}

bool Database :: createTable() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        QSqlQuery query(database);
        query.prepare(
                "CREATE TABLE IF NOT EXISTS accounts"
                "   (id INTEGER PRIMARY KEY, "
                "   issuer_title TEXT, "
                "   account_name TEXT, "
                "   secret_key TEXT,"
                "   auth_type INTEGER DEFAULT 0, "
                "   algorithm_type INTEGER DEFAULT 0, "
                "   counter_value INTEGER DEFAULT 0, "
                "   period_time INTEGER DEFAULT 30, "
                "   auth_code_lenght INTEGER DEFAULT 6, "
                "   publish_date INTEGER, "
                "   edit_date INTEGER)"
                );
        if (query.exec()) {
            qDebug() << "Table creation query execute successfully";
        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Create table error: %1" << error.text();
            success = false;
        }
        database.close();
    }
    return success;
}

bool Database :: dropTable() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        QSqlQuery query(database);
        query.prepare("DROP TABLE IF EXISTS accounts");
        if (query.exec()) {
            qDebug() << "Table drop query execute successfully";
        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Drop table error: %1" << error.text();
            success = false;
        }
        database.close();
    }
    return success;
}

// wip
bool Database :: createColumn(QString& tableName, QString& columnName, QString& columnParams) {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        QSqlQuery query(database);
        query.prepare(
                "ALTER TABLE :tableName"
                "   ADD :columnName :columnParams");
        query.bindValue(":tableName", tableName);
        query.bindValue(":columnName", columnName);
        query.bindValue(":columnParams", columnParams);
        if (query.exec()) {
            qDebug() << "Column creation query execute successfully";
        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Create table error: %1" << error.text();
            success = false;
        }
        database.close();
    }
    return success;
}

// wip
bool Database :: deleteColumn(QString& tableName, QString& columnName) {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        QSqlQuery query(database);
        query.prepare(
                "ALTER TABLE :tableName"
                "   RENAME TO :tableName + '_old'");
        query.bindValue(":tableName", tableName);
        query.bindValue(":columnName", columnName);
        if (query.exec()) {
            alert(tr("Column creation query execute successfully"));
        } else {
            const QSqlError error = query.lastError();
            alert(tr("Create table error: %1").arg(error.text()));
            success = false;
        }
        database.close();
    }
    return success;
}

bool Database :: createRecord () {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        if (database.tables().contains("accounts")) {
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
                alert(tr("Record created"));
            } else {
                const QSqlError error = query.lastError();
                alert(tr("Create record error: %1").arg(error.text()));
                success = false;
            }
        } else {
            alert(tr("Create record error: customers table does not exist."));
            return false;
        }
        database.close();
    }
    return success;
}

bool Database :: updateRecord() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if (success) {
        QSqlQuery query(database);
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
        if (query.exec()) {
            alert(tr("Record updated"));
        } else {
            const QSqlError error = query.lastError();
            alert(tr("Update record error: %1").arg(error.text()));
            success = false;
        }
        database.close();
    }
    return success;
}

bool Database :: deleteRecord() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if (success) {
        QSqlQuery query(database);
        query.prepare("DELETE FROM accounts WHERE id=:id");
        query.bindValue(":id", m_id);
        if (query.exec()) {
            alert(tr("Record deleted"));
        } else {
            const QSqlError error = query.lastError();
            alert(tr("Delete record error: %1").arg(error.text()));
            success = false;
        }
        database.close();
    }
    return success;
}

QVariant Database :: readRecords() {
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare("SELECT * FROM accounts");
    if(query.exec()){
        return query.result();
    }else{
        return false;
    }
}


bool Database :: initializeDatabase() {
    bool success = false;
    if (createDatabase()) {
        if (createTable()) {
            success = true;
        }
    }
    return success;
}


// id
int  Database :: getId() { return m_id; }


// issuerTitle
QString Database :: getIssuerTitle() { return m_issuerTitle; }
void    Database :: setIssuerTitle(QString issuerTitle) {
    m_issuerTitle = issuerTitle;
    emit issuerTitleChanged(m_issuerTitle);
}


// accountName
QString Database :: getAccountName() { return m_accountName; }
void    Database :: setAccountName(QString accountName) {
    m_accountName = accountName;
    emit accountNameChanged(m_accountName);
}


// secretKey
QString Database :: getSecretKey() { return m_secretKey;}
void    Database :: setSecretKey(QString secretKey) {
    m_secretKey = secretKey;
    emit secretKeyChanged(m_secretKey);
}


// algorithmType
int  Database :: getAlgorithmType() { return m_algorithmType; }
void Database :: setAlgorithmType(int algorithmType) {
    m_algorithmType = algorithmType;
    emit algorithmTypeChanged(m_algorithmType);
}


// authType
int  Database :: getAuthType() { return m_authType; }
void Database :: setAuthType(int authType) {
    m_authType = authType;
    emit authTypeChanged(m_authType);
}


// counterValue
int  Database :: getCounterValue(){ return m_counterValue; }
void Database :: setCounterValue(int counterValue) {
    m_counterValue = counterValue;
    emit counterValueChanged(m_counterValue);
}


// periodTime
int  Database :: getPeriodTime() { return m_periodTime; }
void Database :: setPeriodTime(int periodTime) {
    m_periodTime = periodTime;
    emit periodTimeChanged(m_periodTime);
}


// authCodeLenght
int  Database :: getAuthCodeLenght() { return m_authCodeLenght; }
void Database :: setAuthCodeLenght(int authCodeLenght) {
    m_authCodeLenght = authCodeLenght;
    emit authCodeLenghtChanged(m_authCodeLenght);
}


// publishDate
int  Database :: getPublishDate() { return m_publishDate; }
void Database :: setPublishDate(int publishDate) {
    m_publishDate = publishDate;
    emit publishDateChanged(m_publishDate);
}


// editDate
int  Database :: getEditDate() { return m_editDate; }
void Database :: setEditDate(int editDate) {
    m_editDate = editDate;
    emit editDateChanged(m_editDate);
}

