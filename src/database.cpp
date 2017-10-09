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

using namespace bb::system;


Database :: Database (QObject *parent) : QObject(parent), DB_PATH("./data/bbauth.db") {
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
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_PATH);
    bool success = database.open();
    if (success) {
        alert(tr("Database created/registered."));
        database.close();
    } else {
        const QSqlError error = database.lastError();
        alert(tr("Error opening connection to the database: %1").arg(error.text()));
        qDebug() << "\nDatabase NOT opened.";
    }
    return success;
}

bool Database :: deleteDatabase () {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        database.removeDatabase(database.connectionName());
        alert(tr("Database deleted"));
    }else{
        alert(tr("Sql database might not yet created or it is already deleted"));
    }
    database.close();
    return success;
}

bool Database :: createTable () {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
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
            alert(tr("Table creation query execute successfully"));
        } else {
            const QSqlError error = query.lastError();
            alert(tr("Create table error: %1").arg(error.text()));
            success = false;
        }
        database.close();
    }
    return success;
}

bool Database :: dropTable () {
    QSqlDatabase database = QSqlDatabase::database();
    bool success = database.open();
    if(success){
        QSqlQuery query(database);
        query.prepare("DROP TABLE IF EXISTS accounts");
        if (query.exec()) {
            alert(tr("Table drop query execute successfully"));
        } else {
            const QSqlError error = query.lastError();
            alert(tr("Drop table error: %1").arg(error.text()));
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

bool Database :: updateRecord () {
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

bool Database :: deleteRecord () {
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

QVariant Database :: readRecords () {
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

bool Database :: getDatafromURLString (QString& url) {
    bool success = false;
    QString s = url;
    return success;
}



void Database :: alert(const QString &message) {
    SystemDialog *dialog;
    dialog = new SystemDialog(tr("OK"), 0);
    dialog->setTitle(tr("Alert"));
    dialog->setBody(message);
    dialog->setDismissAutomatically(true);
    bool ok = connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_ASSERT(ok);
    dialog->show();
}
