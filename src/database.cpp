/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#include "database.hpp"

#include <QDebug>

Database :: Database(QObject *parent, const QString& db_path)
    : QObject(parent)
    , DB_PATH(db_path)
    , m_id(0)
    , m_issuerTitle("")
    , m_accountName("")
    , m_secretKey("")
    , m_authType(0)
    , m_algorithmType(0)
    , m_counterValue(0)
    , m_periodTime(0)
    , m_authCodeLenght(6)
    , m_publishDate(0)
    , m_editDate(0) {}

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
                "   counter_value INTEGER DEFAULT 0, "
                "   period_time INTEGER DEFAULT 30, "
                "   algorithm_type INTEGER DEFAULT 0, "
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

bool Database :: createRecord () {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = true;//database.open();
    if(success){
        if (database.tables().contains("accounts")) {
            QSqlQuery query(database);
            query.prepare(
                    "INSERT INTO accounts "
                    "   (issuer_title, "
                    "   account_name, "
                    "   secret_key, "
                    "   auth_type, "
                    "   algorithm_type, "
                    "   counter_value, "
                    "   period_time, "
                    "   auth_code_lenght, "
                    "   publish_date, "
                    "   edit_date) "
                    "VALUES "
                    "   (:issuer_title, "
                    "   :account_name, "
                    "   :secret_key, "
                    "   :auth_type, "
                    "   :algorithm_type, "
                    "   :counter_value, "
                    "   :period_time, "
                    "   :auth_code_lenght, "
                    "   :publish_date, "
                    "   :edit_date) "
                    );
            query.bindValue(":issuer_title", m_issuerTitle);
            query.bindValue(":account_name", m_accountName);
            query.bindValue(":secret_key", m_secretKey);
            query.bindValue(":auth_type", m_authType);
            query.bindValue(":algorithm_type", m_algorithmType);
            query.bindValue(":counter_value", m_counterValue);
            query.bindValue(":period_time", m_periodTime);
            query.bindValue(":auth_code_lenght", m_authCodeLenght);
            query.bindValue(":publish_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query.bindValue(":edit_date", m_editDate);

            if (query.exec()) {
                qDebug() << "Record created";
            } else {
                const QSqlError error = query.lastError();
                qDebug() << "Create record error: %1" << error.text();
                success = false;
            }
        } else {
            qDebug() << "Create record error: customers table does not exist.";
            return false;
        }
        //database.close();
    }
    return success;
}

bool Database :: createRecord (Accounts* account) {
    m_issuerTitle = account->getIssuerTitle();
    m_accountName = account->getAccountName();
    m_secretKey = account->getSecretKey();
    m_authType = account->getAuthType();
    m_algorithmType = account->getCounterValue();
    m_counterValue = account->getPeriodTime();
    m_periodTime = account->getAlgorithmType();
    m_authCodeLenght = account->getAuthCodeLenght();
    return createRecord();
}

bool Database :: updateRecord() {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if (success) {
        QSqlQuery query(database);
        query.prepare(
                "UPDATE accounts "
                "SET "
                "   issuer_title=:issuer_title, "
                "   account_name=:account_name, "
                "   secret_key=:secsecret_keyret_code, "
                "   auth_type=:auth_type, "
                "   algorithm_type=:algorithm_type, "
                "   counter_value=:counter_value, "
                "   period_time=:period_time "
                "   algorithm_type=:algorithm_type, "
                "   auth_code_lenght=:auth_code_lenght, "
                "   publish_date=:publish_date "
                "   edit_date=:edit_date "
                "WHERE id=:id"
                );
        query.bindValue(":id", m_id);
        query.bindValue(":issuer_title", m_issuerTitle);
        query.bindValue(":account_name", m_accountName);
        query.bindValue(":secret_key", m_secretKey);
        query.bindValue(":auth_type", m_authType);
        query.bindValue(":counter_value", m_counterValue);
        query.bindValue(":period_time", m_periodTime);
        query.bindValue(":algorithm_type", m_algorithmType);
        query.bindValue(":auth_code_lenght", m_authCodeLenght);
        query.bindValue(":publish_date", m_publishDate);
        query.bindValue(":edit_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        if (query.exec()) {
            qDebug() << "Record updated";
        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Update record error: %1" << error.text();
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
            qDebug() << "Record deleted";
        } else {
            const QSqlError error = query.lastError();
            qDebug() << "Delete record error: %1" << error.text();
            success = false;
        }
        database.close();
    }
    return success;
}

QVariant Database :: getAllRecords() {
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare("SELECT * FROM accounts");
    if(query.exec()) {
        return query.result();
    }
    return false;

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
void    Database :: setIssuerTitle(QString& issuerTitle) {
    m_issuerTitle = issuerTitle;
    emit issuerTitleChanged(m_issuerTitle);
}


// accountName
QString Database :: getAccountName() { return m_accountName; }
void    Database :: setAccountName(QString& accountName) {
    m_accountName = accountName;
    emit accountNameChanged(m_accountName);
}


// secretKey
QString Database :: getSecretKey() { return m_secretKey;}
void    Database :: setSecretKey(QString& secretKey) {
    m_secretKey = secretKey;
    emit secretKeyChanged(m_secretKey);
}


// algorithmType
int  Database :: getAlgorithmType() { return m_algorithmType; }
void Database :: setAlgorithmType(int& algorithmType) {
    m_algorithmType = algorithmType;
    emit algorithmTypeChanged(m_algorithmType);
}


// authType
int  Database :: getAuthType() { return m_authType; }
void Database :: setAuthType(int& authType) {
    m_authType = authType;
    emit authTypeChanged(m_authType);
}


// counterValue
int  Database :: getCounterValue(){ return m_counterValue; }
void Database :: setCounterValue(int& counterValue) {
    m_counterValue = counterValue;
    emit counterValueChanged(m_counterValue);
}


// periodTime
int  Database :: getPeriodTime() { return m_periodTime; }
void Database :: setPeriodTime(int& periodTime) {
    m_periodTime = periodTime;
    emit periodTimeChanged(m_periodTime);
}


// authCodeLenght
int  Database :: getAuthCodeLenght() { return m_authCodeLenght; }
void Database :: setAuthCodeLenght(int& authCodeLenght) {
    m_authCodeLenght = authCodeLenght;
    emit authCodeLenghtChanged(m_authCodeLenght);
}


// publishDate
int  Database :: getPublishDate() { return m_publishDate; }
void Database :: setPublishDate(int& publishDate) {
    m_publishDate = publishDate;
    emit publishDateChanged(m_publishDate);
}


// editDate
int  Database :: getEditDate() { return m_editDate; }
void Database :: setEditDate(int& editDate) {
    m_editDate = editDate;
    emit editDateChanged(m_editDate);
}

