/*
 * accounts.hpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#ifndef ACCOUNTS_HPP_
#define ACCOUNTS_HPP_

#include <QObject>

class Accounts : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged CONSTANT)
    Q_PROPERTY(QString issuerTitle READ getIssuerTitle WRITE setIssuerTitle NOTIFY idChanged FINAL)
    Q_PROPERTY(QString accountName READ getAccountName WRITE setAccountName NOTIFY issuerTitleChanged FINAL)
    Q_PROPERTY(QString secretKey READ getSecretKey WRITE setSecretKey NOTIFY accountNameChanged FINAL)
    Q_PROPERTY(QString keyLenght READ getKeyLenght WRITE setKeyLenght NOTIFY secretKeyChanged FINAL)
    Q_PROPERTY(QString algorithmType READ getAlgorithmType WRITE setAlgorithmType NOTIFY algorithmTypeChanged FINAL)
    Q_PROPERTY(QString authType READ getAuthType WRITE setAuthType NOTIFY authTypeChanged FINAL)
    Q_PROPERTY(QString counterValue READ getCounterValue WRITE setCounterValue NOTIFY counterValueChanged FINAL)
    Q_PROPERTY(QString periodTime READ getPeriodTime WRITE setPeriodTime NOTIFY periodTimeChanged FINAL)
    Q_PROPERTY(QString publishDate READ getPublishDate WRITE setPublishDate NOTIFY publishDateChanged FINAL)
    Q_PROPERTY(QString editDate READ getEditDate WRITE setEditDate NOTIFY editDateChanged FINAL)

public:
    Accounts(QObject* parent = 0);
    Accounts(
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
            QObject *parent = 0);

    int getId() const;
    void setId(int id);

    QString getIssuerTitle() const;
    void setIssuerTitle(const QString& issuerTitle);

    QString getAccountName() const;
    void setAccountName(const QString& accountName);

    QString getSecretKey() const;
    void setSecretKey(const QString& secretKey);

    QString getKeyLenght() const;
    void setKeyLenght(const QString& keyLenght);

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

Q_SIGNALS:
    void idChanged(const int id);
    void issuerTitleChanged(const QString&);
    void accountNameChanged(const QString&);
    void secretKeyChanged(const QString&);
    void keyLenghtChanged(const QString&);
    void algorithmTypeChanged(const QString&);
    void authTypeChanged(const QString&);
    void counterValueChanged(const QString&);
    void periodTimeChanged(const QString&);
    void publishDateChanged(const QString&);
    void editDateChanged(const QString&);

private:
    int m_id;
    QString m_issuerTitle;
    QString m_accountName;
    QString m_secretKey;
    QString m_keyLenght;
    QString m_algorithmType;
    QString m_authType;
    QString m_counterValue;
    QString m_periodTime;
    QString m_publishDate;
    QString m_editDate;
};

#endif /* ACCOUNTS_HPP_ */
