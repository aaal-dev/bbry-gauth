/*
 * database.cpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#include "database.hpp"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
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

bool Database :: init(){
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

    query.bindValue(":title", m_title);
    query.bindValue(":auth_login", m_authLogin);
    query.bindValue(":secret_code", m_secretCode);
    query.bindValue(":key_lenght", m_keyLenght);
    query.bindValue(":auth_type", m_authType);
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

bool Database :: deleteData(){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("DELETE FROM accounts WHERE id=:id");
    query.bindValue(":id", m_id);
    bool success = query.exec();
    db.close();
    return success;
}



int Database :: getId(){
    return m_id;
}

void Database :: setId(int id){
    m_id = id;
    emit idValueChanged(m_id);
}



QString Database :: getTitle(){
    return m_title;
}

void Database :: setTitle(QString title){
    m_title = title;
    emit titleValueChanged(m_title);
}



QString Database :: getAuthLogin(){
    return m_authLogin;
}

void Database :: setAuthLogin(QString authLogin){
    m_authLogin = authLogin;
    emit authLoginValueChanged(m_authLogin);
}



QString Database :: getSecretCode(){
    return m_secretCode;
}

void Database :: setSecretCode(QString secretCode){
    m_secretCode = secretCode;
    emit secretCodeValueChanged(m_secretCode);
}



int Database :: getKeyLenght(){
    return m_keyLenght;
}

void Database :: setKeyLenght(int keyLenght){
    m_keyLenght = keyLenght;
    emit keyLenghtValueChanged(m_keyLenght);
}



int Database :: getAuthType(){
    return m_authType;
}

void Database :: setAuthType(int authType){
    m_authType = authType;
    emit authTypeValueChanged(m_authType);
}



int Database :: getCounter(){
    return m_counter;
}

void Database :: setCounter(int counter){
    m_counter = counter;
    emit counterValueChanged(m_counter);
}



QString Database :: getPublishDate(){
    return m_publishDate;
}

void Database :: setPublishDate(QString publishDate){
    m_publishDate = publishDate;
    emit publishDateValueChanged(m_publishDate);
}



QString Database :: getEditDate(){
    return m_editDate;
}

void Database :: setEditDate(QString editDate){
    m_editDate = editDate;
    emit editDateValueChanged(m_editDate);
}



