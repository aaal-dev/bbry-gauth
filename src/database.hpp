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
#include <QtSql>
#include <QDateTime>

#include "datamodels/accounts.hpp"

#include <bb/data/SqlDataAccess>

class Database : public QObject {
    Q_OBJECT

public:
    Database(QObject *parent, const QString& db_path);
    virtual ~Database();

    bool createDatabase();
    bool deleteDatabase();

    bool createTable();
    bool dropTable();

    bool createColumn(QString&, QString&, QString&);
    bool deleteColumn(QString&, QString&);

    bool createRecord();
    bool createRecord(Accounts* account);
    bool updateRecord();
    bool deleteRecord();
    QVariant getAllRecords();

    bool initializeDatabase();

    // tableColumns
    int  getId();

    QString getIssuerTitle();
    void    setIssuerTitle(QString& issuerTitle);

    QString getAccountName();
    void    setAccountName(QString& accountName);

    QString getSecretKey();
    void    setSecretKey(QString& secretKey);

    int  getAuthType();
    void setAuthType(int& authType);

    int  getCounterValue();
    void setCounterValue(int& counterValue);

    int  getPeriodTime();
    void setPeriodTime(int& periodTime);

    int  getAlgorithmType();
    void setAlgorithmType(int& algorithmType);

    int  getAuthCodeLenght();
    void setAuthCodeLenght(int& authCodeLenght);

    int  getPublishDate();
    void setPublishDate(int& publishDate);

    int  getEditDate();
    void setEditDate(int& editDate);

signals:
    void issuerTitleChanged(QString& m_issuerTitle);
    void accountNameChanged(QString& m_accountName);
    void secretKeyChanged(QString& m_secretKey);
    void authTypeChanged(int& m_authType);
    void algorithmTypeChanged(int& m_algorithmType);
    void counterValueChanged(int& m_counterValue);
    void periodTimeChanged(int& m_periodTime);
    void authCodeLenghtChanged(int& m_authCodeLenght);
    void publishDateChanged(int& m_publishDate);
    void editDateChanged(int& m_editDate);

private:
    QString DB_PATH;
    int m_id;
    QString m_issuerTitle;
    QString m_accountName;
    QString m_secretKey;
    int m_authType;
    int m_algorithmType;
    int m_counterValue;
    int m_periodTime;
    int m_authCodeLenght;
    int m_publishDate;
    int m_editDate;
};

#endif /* DATABASE_HPP_ */
