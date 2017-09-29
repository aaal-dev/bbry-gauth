/*
 * database.hpp
 *
 *  Created on: 08 нояб. 2016 г.
 *      Author: AnimeSlave
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <QObject>
#include <QMetaType>

class Database : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id               READ getId          WRITE setId             NOTIFY idValueChanged)
    Q_PROPERTY(QString title        READ getTitle       WRITE setTitle          NOTIFY titleValueChanged)
    Q_PROPERTY(QString authLogin    READ getAuthLogin   WRITE setAuthLogin      NOTIFY authLoginValueChanged)
    Q_PROPERTY(QString secretCode   READ getSecretCode  WRITE setSecretCode     NOTIFY secretCodeValueChanged)
    Q_PROPERTY(int keyLenght        READ getKeyLenght   WRITE setKeyLenght      NOTIFY keyLenghtValueChanged)
    Q_PROPERTY(int authType         READ getAuthType    WRITE setAuthType       NOTIFY authTypeValueChanged)
    Q_PROPERTY(int counter          READ getCounter     WRITE setCounter        NOTIFY counterValueChanged)
    Q_PROPERTY(QString publishDate  READ getPublishDate WRITE setPublishDate    NOTIFY publishDateValueChanged)
    Q_PROPERTY(QString editDate     READ getEditDate    WRITE setEditDate       NOTIFY editDateValueChanged)

public:
    Database(QObject *parent);
    virtual ~Database();

    Q_INVOKABLE bool createDatabase();
    Q_INVOKABLE bool deleteDatabase();

    Q_INVOKABLE bool createTable();
    Q_INVOKABLE bool dropTable();

    Q_INVOKABLE bool createRecord();
    Q_INVOKABLE bool updateData();
    Q_INVOKABLE bool deleteData();
    Q_INVOKABLE bool readData();

    int getId();
    void setId(int id);

    QString getTitle();
    void setTitle(QString title);

    QString getAuthLogin();
    void setAuthLogin(QString authLogin);

    QString getSecretCode();
    void setSecretCode(QString secretCode);

    int getKeyLenght();
    void setKeyLenght(int keyLenght);

    int getAuthType();
    void setAuthType(int authType);

    int getCounter();
    void setCounter(int counter);

    QString getPublishDate();
    void setPublishDate(QString publishDate);

    QString getEditDate();
    void setEditDate(QString editDate);

signals:
    void idValueChanged(int);
    void titleValueChanged(QString);
    void authLoginValueChanged(QString);
    void secretCodeValueChanged(QString);
    void keyLenghtValueChanged(int);
    void authTypeValueChanged(int);
    void counterValueChanged(int);
    void publishDateValueChanged(QString);
    void editDateValueChanged(QString);

private:
    QString DB_NAME;
    int m_id;
    QString m_title;
    QString m_authLogin;
    QString m_secretCode;
    int m_keyLenght;
    int m_authType;
    int m_counter;
    QString m_publishDate;
    QString m_editDate;
};

#endif /* DATABASE_HPP_ */
