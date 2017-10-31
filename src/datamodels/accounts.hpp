/*
 * accounts.hpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#ifndef ACCOUNTS_HPP_
#define ACCOUNTS_HPP_

#include <QObject>

#include "huctx.h"
#include <stdint.h>
#include <time.h>


#include <QTime>
#include <QTimer>

#include "../oath/hmac.hpp"
#include "../oath/sha1.hpp"
#include "../oath/authcodegenerator.hpp"

class Accounts : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QString issuerTitle READ getIssuerTitle WRITE setIssuerTitle NOTIFY issuerTitleChanged FINAL)
    Q_PROPERTY(QString accountName READ getAccountName WRITE setAccountName NOTIFY accountNameChanged FINAL)
    Q_PROPERTY(QString secretKey READ getSecretKey WRITE setSecretKey NOTIFY secretKeyChanged FINAL)
    Q_PROPERTY(uchar authType READ getAuthType WRITE setAuthType NOTIFY authTypeChanged FINAL)
    Q_PROPERTY(uint counterValue READ getCounterValue WRITE setCounterValue NOTIFY counterValueChanged FINAL)
    Q_PROPERTY(uint periodTime READ getPeriodTime WRITE setPeriodTime NOTIFY periodTimeChanged FINAL)
    Q_PROPERTY(uchar algorithmType READ getAlgorithmType WRITE setAlgorithmType NOTIFY algorithmTypeChanged FINAL)
    Q_PROPERTY(uchar authCodeLenght READ getAuthCodeLenght WRITE setAuthCodeLenght NOTIFY authCodeLenghtChanged FINAL)
    Q_PROPERTY(ulong publishDate READ getPublishDate WRITE setPublishDate NOTIFY publishDateChanged FINAL)
    Q_PROPERTY(ulong editDate READ getEditDate WRITE setEditDate NOTIFY editDateChanged FINAL)
    Q_PROPERTY(QString authCode READ getAuthCode NOTIFY authCodeChanged FINAL)
    Q_PROPERTY(uint elapsedTime READ getElapsedTime NOTIFY elapsedTimeChanged FINAL)
    Q_PROPERTY(uint elapsedTimeOffset READ getElapsedTimeOffset NOTIFY elapsedTimeOffsetChanged FINAL)

public:
    Accounts(QObject* parent = 0);
    Accounts(
            const QString& issuerTitle,
            const QString& accountName,
            const QString& secretKey,
            const uchar& authType,
            const uint& counterValue,
            const uint& periodTime,
            const uchar& algorithmType,
            const uchar& authCodeLenght,
            QObject *parent = 0);
    Accounts(
            const sb_GlobalCtx& sbCtx,
            const int id,
            const QString& issuerTitle,
            const QString& accountName,
            const QString& secretKey,
            const uchar& authType,
            const uint& counterValue,
            const uint& periodTime,
            const uchar& algorithmType,
            const uchar& authCodeLenght,
            const ulong& publishDate,
            const ulong& editDate,
            QObject *parent = 0);

    int getId() const;

    QString getIssuerTitle() const;
    void setIssuerTitle(const QString& issuerTitle);

    QString getAccountName() const;
    void setAccountName(const QString& accountName);

    QString getSecretKey() const;
    void setSecretKey(const QString& secretKey);

    uchar getAuthType() const;
    void setAuthType(const uchar& authType);

    uint getCounterValue() const;
    void setCounterValue(const uint& counterValue);

    uint getPeriodTime() const;
    void setPeriodTime(const uint& periodTime);

    uchar getAlgorithmType() const;
    void setAlgorithmType(const uchar& algorithmType);

    uchar getAuthCodeLenght() const;
    void setAuthCodeLenght(const uchar& authCodeLenght);

    ulong getPublishDate() const;
    void setPublishDate(const ulong& publishDate);

    ulong getEditDate() const;
    void setEditDate(const ulong& editDate);

    QString getAuthCode() const;
    int getElapsedTime();
    int getElapsedTimeOffset();

signals:
    void issuerTitleChanged(const QString&);
    void accountNameChanged(const QString&);
    void secretKeyChanged(const QString&);
    void authTypeChanged(const uchar&);
    void counterValueChanged(const uint&);
    void periodTimeChanged(const uint&);
    void algorithmTypeChanged(const uchar&);
    void authCodeLenghtChanged(const uchar&);
    void publishDateChanged(const ulong&);
    void editDateChanged(const ulong&);
    void authCodeChanged(const QString&);
    void elapsedTimeChanged(int);
    void elapsedTimeOffsetChanged(int);

private:
    int m_id;
    QString m_issuerTitle;
    QString m_accountName;
    QString m_secretKey;
    uchar m_authType;
    uint m_counterValue;
    uint m_periodTime;
    uchar m_algorithmType;
    uchar m_authCodeLenght;
    ulong m_publishDate;
    ulong m_editDate;
    uint8_t* m_secretKeyTmp;
    size_t m_secretKeyLenght;
    QString m_authCode;
    uint m_elapsedTime;
    int m_elapsedTimeOffset;
    AuthCodeGenerator* authCodeGenerator;

    int Base32Decode(const uint8_t *encoded, uint8_t *result, int bufSize);
    int GetHotpCode(const uint8_t* secret, int secretLen, ulong step, uchar digits);
    int GetTotpCode(const uint8_t *secret, int secretLen, int digits);
    int PowerOf10(int digits);

private slots:
    void UpdateTime();
};

#endif /* ACCOUNTS_HPP_ */
