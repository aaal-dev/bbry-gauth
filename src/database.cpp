/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#include "database.hpp"

#include <QDebug>

Database :: Database(QObject *parent, const QString& db_path, const QString& tableName)
    : QObject(parent)
    , DB_PATH(db_path)
    , m_tableName(tableName)
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
    , m_editDate(0)
{
    createDatabase();
}

Database :: ~Database() {

}


bool Database :: createDatabase() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", m_tableName);
    database.setDatabaseName(DB_PATH);
    if  (!database.open()) {
        const QSqlError error = database.lastError();
        qDebug() << "ERROR: DATABASE: connection false." << error.text();
        return false;
    } else {
        qDebug() << "DATABASE: connection ok";
        return true;
    }
}


bool Database :: deleteDatabase() {
    QSqlDatabase database = QSqlDatabase::database();
    database.removeDatabase(database.connectionName());
    if (!database.open()) {
        qDebug() << "DATABASE: deleted.";
        return true;
    } else {
        const QSqlError error = database.lastError();
        qDebug() << "ERROR: DATABASE: not deleted." << error.text();
        return false;
    }
}

bool Database :: initializeDatabase() {
    return createTable(m_tableName);
}

bool Database :: createTable(const QString& tableName) {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare(QString("CREATE TABLE IF NOT EXISTS %1"
            "(id INTEGER PRIMARY KEY, "
            "issuer_title TEXT, "
            "account_name TEXT, "
            "secret_key TEXT, "
            "auth_type INTEGER DEFAULT 0, "
            "counter_value INTEGER DEFAULT 0, "
            "period_time INTEGER DEFAULT 30, "
            "algorithm_type INTEGER DEFAULT 0, "
            "auth_code_lenght INTEGER DEFAULT 6, "
            "publish_date INTEGER, "
            "edit_date INTEGER);").arg(tableName));
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: table creation false." << error.text();
        return false;
    } else {
        qDebug() << "DATABASE: table" << tableName << "created.";
        return true;
    }
}

bool Database :: dropTable(const QString& tableName) {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare("DROP TABLE IF EXISTS :tableName");
    query.bindValue(":tableName", tableName);
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: drop table error." << error.text();
        return false;
    } else {
        qDebug() << "DATABASE: table dropped";
        return true;
    }
}



/* ------------- */
/* ---- WIP ---- */
bool Database :: createColumn(const QString& tableName, const QString& columnName, const QString& columnParams) {
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare(QString("ALTER TABLE %1"
            "   ADD %2 %3").arg(tableName).arg(columnName).arg(columnParams));
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: column not created." << error.text();
        return false;
    } else {
        qDebug() << "DATABASE: column created.";
        return true;
    }
}

bool Database :: deleteColumn(const QString& tableName, const QString& columnName) {
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
/* !---- WIP ---- */
/* ------------- */



bool Database :: createRecord(const QString& tableName) {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    if (database.tables().contains(tableName)) {
        QSqlQuery query(database);
        query.prepare(QString(
                "INSERT INTO %1 "
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
                ).arg(tableName));
        query.bindValue(":issuer_title", m_issuerTitle);
        query.bindValue(":account_name", m_accountName);
        query.bindValue(":secret_key", m_secretKey);
        query.bindValue(":auth_type", m_authType);
        query.bindValue(":counter_value", m_counterValue);
        query.bindValue(":period_time", m_periodTime);
        query.bindValue(":algorithm_type", m_algorithmType);
        query.bindValue(":auth_code_lenght", m_authCodeLenght);
        query.bindValue(":publish_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        query.bindValue(":edit_date", m_editDate);
        if (!query.exec()) {
            const QSqlError error = query.lastError();
            qDebug() << "ERROR: DATABASE: record not created: %1" << error.text();
            return false;
        } else {
            qDebug() << "DATABASE: record created: issuer:" << m_issuerTitle << "account" << m_accountName;
            return true;
        }
    } else {
        qDebug() << "ERROR: DATABASE: create record error: table «accounts» does not exist.";
        return false;
    }
}

int Database :: createRecord(
        const QString& issuerTitle,
        const QString& accountName,
        const QString& secretKey,
        const uchar& authType,
        const uint& counterValue,
        const uint& periodTime,
        const uchar& algorithmType,
        const uchar& authCodeLenght
        ) {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare(QString(
            "INSERT INTO %1 "
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
            ).arg(m_tableName));
    query.bindValue(":issuer_title", issuerTitle);
    query.bindValue(":account_name", accountName);
    query.bindValue(":secret_key", secretKey);
    query.bindValue(":auth_type", authType);
    query.bindValue(":counter_value", counterValue);
    query.bindValue(":period_time", periodTime);
    query.bindValue(":algorithm_type", algorithmType);
    query.bindValue(":auth_code_lenght", authCodeLenght);
    query.bindValue(":publish_date", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    query.bindValue(":edit_date", 0);
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: record not created: %1" << error.text();
        return false;
    } else {
        qDebug() << "DATABASE: record created: issuer:" << issuerTitle << "account" << accountName;
        return query.lastInsertId().toInt();
    }
}

bool Database :: updateRecord() {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare(
            "UPDATE accounts "
            "SET "
            "   issuer_title=:issuer_title, "
            "   account_name=:account_name, "
            "   secret_key=:secret_key, "
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
    return query.exec();
}

bool Database :: deleteRecord() {
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare("DELETE FROM accounts WHERE id=:id");
    query.bindValue(":id", m_id);
    if (!query.exec()){
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: deleteRecord: record id" << m_id << "not exist." << error.text();
        return false;
    }
    return true;
}

bool Database :: deleteAccount(int& id) {
    m_id=id;
    return deleteRecord();
}

QVariantList* Database :: getAllRecords() {
    QVariantList* list = new QVariantList();
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare(QString("SELECT * FROM %1").arg(m_tableName));
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: record list" << error.text();
    } else {
        while (query.next()) {
            QSqlRecord rec = query.record();
            QVariantMap map = QVariantMap();
            for( int i=0; i<rec.count(); ++i )
                map.insert(rec.fieldName(i), query.value(i));
            list->append(map);
        }
        if (!list->isEmpty()){
            qDebug() << "DATABASE: got record list.";

        } else {
            qDebug() << "ERROR: DATABASE: record list empty";
        }
    }
    return list;
}

QVariantList* Database :: getRecordbyId(const int& id) {
    QVariantList* list = new QVariantList();
    QSqlDatabase database = QSqlDatabase::database(m_tableName);
    QSqlQuery query(database);
    query.prepare(QString("SELECT * FROM %1 WHERE id = :id").arg(m_tableName));
    query.bindValue(":id", id);
    if (!query.exec()) {
        const QSqlError error = query.lastError();
        qDebug() << "ERROR: DATABASE: record list" << error.text();
    } else {
        while (query.next()) {
            QSqlRecord rec = query.record();
            QVariantMap map = QVariantMap();
            for( int i=0; i<rec.count(); ++i )
                map.insert(rec.fieldName(i), query.value(i));
            list->append(map);
        }
        if (!list->isEmpty()){
            qDebug() << "DATABASE: got record by id" << id;

        } else {
            qDebug() << "ERROR: DATABASE: record with id" << id << "not exist";
        }
    }
    return list;
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

