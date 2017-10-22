/*
 * accounts.hpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#ifndef ACCOUNTS_HPP_
#define ACCOUNTS_HPP_

#include <stdint.h>

#include <QObject>

class Accounts : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QString issuerTitle READ getIssuerTitle WRITE setIssuerTitle NOTIFY issuerTitleChanged FINAL)
    Q_PROPERTY(QString accountName READ getAccountName WRITE setAccountName NOTIFY accountNameChanged FINAL)
    Q_PROPERTY(uchar keyLenght READ getKeyLenght WRITE setKeyLenght NOTIFY secretKeyChanged FINAL)
    Q_PROPERTY(QString algorithmType READ getAlgorithmType WRITE setAlgorithmType NOTIFY algorithmTypeChanged FINAL)
    Q_PROPERTY(QString authType READ getAuthType WRITE setAuthType NOTIFY authTypeChanged FINAL)
    Q_PROPERTY(QString counterValue READ getCounterValue WRITE setCounterValue NOTIFY counterValueChanged FINAL)
    Q_PROPERTY(QString periodTime READ getPeriodTime WRITE setPeriodTime NOTIFY periodTimeChanged FINAL)
    Q_PROPERTY(QString publishDate READ getPublishDate WRITE setPublishDate NOTIFY publishDateChanged FINAL)
    Q_PROPERTY(QString editDate READ getEditDate WRITE setEditDate NOTIFY editDateChanged FINAL)
    Q_PROPERTY(QString authCode READ getAuthCode NOTIFY authCodeChanged FINAL)
    Q_PROPERTY(int elapsedTime READ getElapsedTime NOTIFY elapsedTimeChanged FINAL)

public:
    Accounts(QObject* parent = 0);
    Accounts(
            const int id,
            const QString& issuerTitle,
            const QString& accountName,
            const QString& secretKey,
            const uchar& keyLenght,
            const QString& algorithmType,
            const QString& authType,
            const QString& counterValue,
            const QString& periodTime,
            const QString& publishDate,
            const QString& editDate,
            QObject *parent = 0);

    int getId() const;

    QString getIssuerTitle() const;
    void setIssuerTitle(const QString& issuerTitle);

    QString getAccountName() const;
    void setAccountName(const QString& accountName);

    QString getSecretKey() const;
    void setSecretKey(const QString& secretKey);

    uchar getKeyLenght() const;
    void setKeyLenght(const uchar& keyLenght);

    QString getAlgorithmType() const;
    void setAlgorithmType(const QString& algorithmType);

    QString getAuthType() const;
    void setAuthType(const QString& authType);

    QString getCounterValue() const;
    void setCounterValue(const QString& counterValue);

    QString getPeriodTime() const;
    void setPeriodTime(const QString& periodTime);

    QString getPublishDate() const;
    void setPublishDate(const QString& publishDate);

    QString getEditDate() const;
    void setEditDate(const QString& editDate);

    QString getAuthCode() const;
    int getElapsedTime();

signals:
    void issuerTitleChanged(const QString&);
    void accountNameChanged(const QString&);
    void secretKeyChanged(const QString&);
    void keyLenghtChanged(const uchar&);
    void algorithmTypeChanged(const QString&);
    void authTypeChanged(const QString&);
    void counterValueChanged(const QString&);
    void periodTimeChanged(const QString&);
    void publishDateChanged(const QString&);
    void editDateChanged(const QString&);
    void authCodeChanged(const QString&);
    void elapsedTimeChanged(int);

private:
    int m_id;
    QString m_issuerTitle;
    QString m_accountName;
    uint8_t* m_secretKey;
    size_t m_secretKeyLenght;
    uchar m_keyLenght;
    QString m_algorithmType;
    QString m_authType;
    QString m_counterValue;
    QString m_periodTime;
    QString m_publishDate;
    QString m_editDate;
    QString m_authCode;
    int m_elapsedTime;

    int Base32Decode(const uint8_t *encoded, uint8_t *result, int bufSize);
    int GetHotpCode(const uint8_t* secret, int secretLen, ulong step, uchar digits);
    int GetTotpCode(const uint8_t *secret, int secretLen, int digits);
    int PowerOf10(int digits);

private slots:
    void UpdateTime();
    void NextAuthCode();
};

#endif /* ACCOUNTS_HPP_ */
