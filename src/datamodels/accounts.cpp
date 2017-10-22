/*
 * accounts.cpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#include "accounts.hpp"
#include "../oath/hmac.hpp"
#include "../oath/sha1.hpp"

#include <time.h>
#include <QTime>
#include <QTimer>

ulong timeStamp;

Accounts :: Accounts(QObject *parent) : QObject(parent) {}

Accounts :: Accounts(
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
        QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_issuerTitle(issuerTitle)
    , m_accountName(accountName)
    , m_secretKeyLenght(0)
    , m_keyLenght(keyLenght)
    , m_algorithmType(algorithmType)
    , m_authType(authType)
    , m_counterValue(counterValue)
    , m_periodTime(periodTime)
    , m_publishDate(publishDate)
    , m_editDate(editDate)
    , m_authCode("")
    , m_elapsedTime(0)
{
    timer_t t = time(NULL);
    timeStamp = t / 30;

    QTimer* pCountDownTimer = new QTimer(this);
    connect(pCountDownTimer, SIGNAL(timeout()), this, SLOT(UpdateTime()));

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(NextAuthCode()));

    m_elapsedTime = (t % 30) * 10 + QTime::currentTime().msec() / 100;
    pCountDownTimer->start(100);
    pTimer->start(30000);


    uint8_t* pTmp = new uint8_t[100];
    m_secretKeyLenght = Base32Decode((const uint8_t*) secretKey.toAscii().constData(), pTmp, 100);
    m_secretKey = new uint8_t[m_secretKeyLenght];
    memcpy(m_secretKey, pTmp, m_secretKeyLenght);
    delete pTmp;
    int code = GetTotpCode(m_secretKey, m_secretKeyLenght, m_keyLenght);
    switch (m_keyLenght) {
        case 6:
            m_authCode.sprintf("%06d", code);
            break;
        case 7:
            m_authCode.sprintf("%07d", code);
            break;
        case 8:
            m_authCode.sprintf("%08d", code);
            break;
        case 9:
            m_authCode.sprintf("%09d", code);
            break;
        default:
            m_authCode.sprintf("%06d", code);
            break;
    }
    authCodeChanged(m_authCode);
}


//id
int Accounts :: getId() const { return m_id; }



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


//keyLenght
uchar Accounts :: getKeyLenght() const { return m_keyLenght; }
void Accounts :: setKeyLenght(const uchar& keyLenght) {
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

QString Accounts :: getAuthCode() const { return m_authCode; }
int Accounts :: getElapsedTime() { return m_elapsedTime; }

int Accounts :: Base32Decode(const uint8_t *encoded, uint8_t *result, int bufSize) {
  int buffer = 0;
  int bitsLeft = 0;
  int count = 0;
  for (const uint8_t *ptr = encoded; count < bufSize && *ptr; ++ptr) {
    uint8_t ch = *ptr;
    if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '-') {
      continue;
    }
    buffer <<= 5;

    // Deal with commonly mistyped characters
    if (ch == '0') {
      ch = 'O';
    } else if (ch == '1') {
      ch = 'L';
    } else if (ch == '8') {
      ch = 'B';
    }

    // Look up one base32 digit
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
      ch = (ch & 0x1F) - 1;
    } else if (ch >= '2' && ch <= '7') {
      ch -= '2' - 26;
    } else {
      return -1;
    }

    buffer |= ch;
    bitsLeft += 5;
    if (bitsLeft >= 8) {
      result[count++] = buffer >> (bitsLeft - 8);
      bitsLeft -= 8;
    }
  }
  if (count < bufSize) {
    result[count] = '\000';
  }
  return count;
}

int Accounts :: GetHotpCode(const uint8_t* secretKey, int secretKeyLenght, ulong /*value*/ step, uchar keyLenght) {
    uint8_t val[8];
    for (int i = 8; i--; step >>= 8) {
        val[i] = step;
    }
    uint8_t hash[SHA1_DIGEST_LENGTH];
    hmac_sha1(secretKey, secretKeyLenght, val, 8, hash, SHA1_DIGEST_LENGTH);
    // memset(val, 0, sizeof(val));
    int offset = hash[SHA1_DIGEST_LENGTH - 1] & 0xF;
    unsigned int truncatedHash = 0;
    for (int i = 0; i < 4; ++i) {
        truncatedHash <<= 8;
        truncatedHash |= hash[offset + i];
    }
    // memset(hash, 0, sizeof(hash));
    truncatedHash &= 0x7FFFFFFF;
    truncatedHash %= PowerOf10(keyLenght);
    return truncatedHash;
}

int Accounts :: GetTotpCode(const uint8_t *secretKey, int secretKeyLenght, int keyLenght){
    return GetHotpCode(secretKey, secretKeyLenght, timeStamp, keyLenght);
}

int Accounts :: PowerOf10(int keyLenght) {
    switch (keyLenght) {
        case 6: return 1000000;
        case 7: return 10000000;
        case 8: return 100000000;
        case 9: return 1000000000;
        default: return 1000000;
    }
}

void Accounts :: UpdateTime() {
    ++m_elapsedTime;
    elapsedTimeChanged(m_elapsedTime);
}

void Accounts :: NextAuthCode() {
    m_elapsedTime = 0;
    elapsedTimeChanged(0);
    ++timeStamp;
    int code = GetTotpCode(m_secretKey, m_secretKeyLenght, m_keyLenght);
    switch (m_keyLenght) {
        case 6:
            m_authCode.sprintf("%06d", code);
            break;
        case 7:
            m_authCode.sprintf("%07d", code);
            break;
        case 8:
            m_authCode.sprintf("%08d", code);
            break;
        case 9:
            m_authCode.sprintf("%09d", code);
            break;
        default:
            m_authCode.sprintf("%06d", code);
            break;
    }
    authCodeChanged(m_authCode);
}
