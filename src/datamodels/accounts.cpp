/*
 * accounts.cpp
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: drumbox
 */

#include "accounts.hpp"

ulong timeStamp;

Accounts :: Accounts(QObject *parent) : QObject(parent) {}

// Для базы данных
Accounts :: Accounts(
        const QString& issuerTitle,
        const QString& accountName,
        const QString& secretKey,
        const uchar& authType,
        const uint& counterValue,
        const uint& periodTime,
        const uchar& algorithmType,
        const uchar& authCodeLenght,
        QObject *parent)
    : QObject(parent)
    , m_id(0)
    , m_issuerTitle(issuerTitle)
    , m_accountName(accountName)
    , m_secretKey(secretKey)
    , m_authType(authType)
    , m_counterValue(counterValue)
    , m_periodTime(periodTime)
    , m_algorithmType(algorithmType)
    , m_authCodeLenght(authCodeLenght)
    , m_publishDate(0)
    , m_editDate(0)
    , m_authCode("")
    , m_elapsedTime(0)
{

}

// Для отображения
Accounts :: Accounts(
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
        QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_issuerTitle(issuerTitle)
    , m_accountName(accountName)
    , m_secretKey(secretKey)
    , m_authType(authType)
    , m_counterValue(counterValue)
    , m_periodTime(periodTime)
    , m_algorithmType(algorithmType)
    , m_authCodeLenght(authCodeLenght)
    , m_publishDate(publishDate)
    , m_editDate(editDate)
    , m_authCode("")
    , m_elapsedTime(0)
{
    authCodeGenerator = new AuthCodeGenerator(sbCtx, this);
    timer_t t = time(NULL);
    timeStamp = t / m_periodTime;

    QTimer* pCountDownTimer = new QTimer(this);
    connect(pCountDownTimer, SIGNAL(timeout()), this, SLOT(UpdateTime()));

    QTimer* pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(NextAuthCode()));

    m_elapsedTime = (t % m_periodTime) * 10 + QTime::currentTime().msec() / 100;
    pCountDownTimer->start(100);
    pTimer->start(m_periodTime * 1000);


    uint8_t* pTmp = new uint8_t[100];
    m_secretKeyLenght = Base32Decode((const uint8_t*) m_secretKey.toAscii().constData(), pTmp, 100);
    m_secretKeyTmp = new uint8_t[m_secretKeyLenght];
    memcpy(m_secretKeyTmp, pTmp, m_secretKeyLenght);
    delete pTmp;
    int code = GetTotpCode(m_secretKeyTmp, m_secretKeyLenght, m_authCodeLenght);
    switch (m_authCodeLenght) {
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

QString Accounts :: getSecretKey() const { return m_secretKey; }
void Accounts :: setSecretKey(const QString& secretKey) {
    if (secretKey != m_secretKey) {
        m_secretKey = secretKey;
        emit secretKeyChanged(secretKey);
    }
}


//authType
uchar Accounts :: getAuthType() const { return m_authType; }
void Accounts :: setAuthType(const uchar& authType) {
    if (authType != m_authType) {
        m_authType = authType;
        emit authTypeChanged(authType);
    }
}


//counterValue
uint Accounts :: getCounterValue() const { return m_counterValue; }
void Accounts :: setCounterValue(const uint& counterValue) {
    if (counterValue != m_counterValue) {
        m_counterValue = counterValue;
        emit counterValueChanged(counterValue);
    }
}


//periodTime
uint Accounts :: getPeriodTime() const { return m_periodTime; }
void Accounts :: setPeriodTime(const uint& periodTime) {
    if (periodTime != m_periodTime) {
        m_periodTime = periodTime;
        emit periodTimeChanged(periodTime);
    }
}


//algorithmType
uchar Accounts :: getAlgorithmType() const { return m_algorithmType; }
void Accounts :: setAlgorithmType(const uchar& algorithmType) {
    if (algorithmType != m_algorithmType) {
        m_algorithmType = algorithmType;
        emit algorithmTypeChanged(algorithmType);
    }
}


//keyLenght
uchar Accounts :: getAuthCodeLenght() const { return m_authCodeLenght; }
void Accounts :: setAuthCodeLenght(const uchar& authCodeLenght) {
    if (authCodeLenght != m_authCodeLenght) {
        m_authCodeLenght = authCodeLenght;
        emit authCodeLenghtChanged(authCodeLenght);
    }
}


//publishDate
ulong Accounts :: getPublishDate() const { return m_publishDate; }
void Accounts :: setPublishDate(const ulong& publishDate) {
    if (publishDate != m_publishDate) {
        m_publishDate = publishDate;
        emit publishDateChanged(publishDate);
    }
}


//editDate
ulong Accounts :: getEditDate() const { return m_editDate; }
void Accounts :: setEditDate(const ulong& editDate) {
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
    int powerOf10[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    truncatedHash &= 0x7FFFFFFF;
    truncatedHash %= powerOf10[keyLenght];
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
    int code = GetTotpCode(m_secretKeyTmp, m_secretKeyLenght, m_authCodeLenght);
    switch (m_authCodeLenght) {
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
