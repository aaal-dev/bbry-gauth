/*
 * accounts.cpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#include "accounts.hpp"

Accounts :: Accounts(QObject *parent) : QObject(parent) {}

Accounts :: Accounts(
        const int id,
        const QString& issuerTitle,
        const QString& accountName,
        const QString& secretKey,
        const QString& keyLenght,
        const QString& algorithmType,
        const QString& authType,
        const QString& counterValue,
        const QString& periodTime,
        const QString& publishDate,
        const QString& editDate,
        QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_issuerTitle(issuerTitle)
    , m_accountName(accountName)
    , m_secretKey(secretKey)
    , m_keyLenght(keyLenght)
    , m_algorithmType(algorithmType)
    , m_authType(authType)
    , m_counterValue(counterValue)
    , m_periodTime(periodTime)
    , m_publishDate(publishDate)
    , m_editDate(editDate) {}


//id
int Accounts :: getId() const { return m_id; }
void Accounts :: setId(int id){
    if (id != m_id) {
        m_id = id;
        emit idChanged(id);
    }
}


//issuerTitle
QString Accounts :: getIssuerTitle() const { return m_issuerTitle; }
void Accounts :: setIssuerTitle(const QString& issuerTitle) {
    if (issuerTitle != m_issuerTitle) {
        m_issuerTitle = issuerTitle;
        emit issuerTitleChanged(issuerTitle);
    }
}


//accountName
QString Accounts :: getAccountName() const { return m_accountName; }
void Accounts :: setAccountName(const QString& accountName) {
    if (accountName != m_accountName) {
        m_accountName = accountName;
        emit accountNameChanged(accountName);
    }
}


//secretKey
QString Accounts :: getSecretKey() const { return m_secretKey; }
void Accounts :: setSecretKey(const QString& secretKey) {
    if (secretKey != m_secretKey) {
        m_secretKey = secretKey;
        emit secretKeyChanged(secretKey);
    }
}


//keyLenght
QString Accounts :: getKeyLenght() const { return m_keyLenght; }
void Accounts :: setKeyLenght(const QString& keyLenght) {
    if (keyLenght != m_keyLenght) {
        m_keyLenght = keyLenght;
        emit keyLenghtChanged(keyLenght);
    }
}


//algorithmType
QString Accounts :: getAlgorithmType() const { return m_algorithmType; }
void Accounts :: setAlgorithmType(const QString& algorithmType) {
    if (algorithmType != m_algorithmType) {
        m_algorithmType = algorithmType;
        emit algorithmTypeChanged(algorithmType);
    }
}


//authType
QString Accounts :: getAuthType() const { return m_authType; }
void Accounts :: setAuthType(const QString& authType) {
    if (authType != m_authType) {
        m_authType = authType;
        emit authTypeChanged(authType);
    }
}


//counterValue
QString Accounts :: getCounterValue() const { return m_counterValue; }
void Accounts :: setCounterValue(const QString& counterValue) {
    if (counterValue != m_counterValue) {
        m_counterValue = counterValue;
        emit counterValueChanged(counterValue);
    }
}


//periodTime
QString Accounts :: getPeriodTime() const { return m_periodTime; }
void Accounts :: setPeriodTime(const QString& periodTime) {
    if (periodTime != m_periodTime) {
        m_periodTime = periodTime;
        emit periodTimeChanged(periodTime);
    }
}


//publishDate
QString Accounts :: getPublishDate() const { return m_publishDate; }
void Accounts :: setPublishDate(const QString& publishDate) {
    if (publishDate != m_publishDate) {
        m_publishDate = publishDate;
        emit publishDateChanged(publishDate);
    }
}


//editDate
QString Accounts :: getEditDate() const { return m_editDate; }
void Accounts :: setEditDate(const QString& editDate) {
    if (editDate != m_editDate) {
        m_editDate = editDate;
        emit editDateChanged(editDate);
    }
}
