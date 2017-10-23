/*
 * authcodegenerator.cpp
 *
 *  Created on: 22 окт. 2017 г.
 *      Author: drumbox
 */

#include "authcodegenerator.hpp"

#include <QDebug>

AuthCodeGenerator :: AuthCodeGenerator(QObject *parent)
    : QObject(parent)
    , m_sbCtx(NULL)
    , hmacContext(NULL) {}

AuthCodeGenerator :: AuthCodeGenerator(const sb_GlobalCtx& sbCtx, QObject *parent) : QObject(parent), m_sbCtx(sbCtx) {
    hmacContext = NULL;
}


QByteArray AuthCodeGenerator :: GetMovingFactor(long counter) {
    QByteArray text;
    int size = 8;
    text.resize(size);
    for (int i = size - 1; i >= 0; i--) {
        text[i] = counter & 0xff;
        counter >>= 8;
    }
    return text;
}

int AuthCodeGenerator :: Truncate(QByteArray *digest, int truncationOffset) {
    int digestLen = digest->capacity();
    int offset = digest->at(digestLen - 1) & 0xf;
    if ((0 <= truncationOffset) && (truncationOffset < (digestLen - 4))) {
        offset = truncationOffset;
    }
    return (digest->at(offset) & 0x7f) << 24 | (digest->at(offset+1) & 0xff) << 16 | (digest->at(offset+2) & 0xff) << 8 | (digest->at(offset+3) & 0xff);
}

QByteArray* AuthCodeGenerator :: GenerateHMACSHA1(QString sharedKey, QByteArray counter) {
    int rc = SB_SUCCESS;
    QByteArray key_ba = sharedKey.toUtf8();
    const unsigned char *key = reinterpret_cast<const unsigned char *>(key_ba.data());
    unsigned char *counter_blk = reinterpret_cast<unsigned char *>(counter.data());
    unsigned char messageDigestHMAC[SB_HMAC_SHA1_160_TAG_LEN];
    rc = hu_HMACSHA1Begin((size_t)key_ba.length(), key, NULL, &hmacContext, m_sbCtx);  //Initialize HMAC-SHA1 with key and context
    rc = hu_HMACSHA1Hash(hmacContext, counter.length(), counter_blk, m_sbCtx);  //Provide the input message
    rc = hu_HMACSHA1End(&hmacContext, SB_HMAC_SHA1_160_TAG_LEN, messageDigestHMAC, m_sbCtx);  //Generate the digest
    Q_UNUSED(rc);
    return new QByteArray(reinterpret_cast<const char *>(messageDigestHMAC), SB_HMAC_SHA1_160_TAG_LEN);
}

int AuthCodeGenerator :: CalcChecksum(long num, int digits) {
    int doubleDigits[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    bool doubleDigit = true;
    int total = 0;
    while (0 < digits--) {
        int digit = (int) (num % 10);
        num /= 10;
        if (doubleDigit) {
            digit = doubleDigits[digit];
        }
        total += digit;
        doubleDigit = !doubleDigit;
    }
    int result = total % 10;
    if (result > 0) {
        result = 10 - result;
    }
    return result;
}

QString AuthCodeGenerator :: BinToHex(unsigned char *message) {
    QString digest;
    for (int i = 0; i < SB_HMAC_SHA1_160_TAG_LEN; ++i) {
        digest.append(QString("%1").arg(QString::number((uint)message[i], 16), 2, QChar('0')));
    }
    qDebug() << digest;
    return digest;
}

int AuthCodeGenerator :: GenerateHOTP(QString secret, long movingFactor, int codeDigits, bool addChecksum, int truncationOffset) {
    int digitsPower[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    QByteArray counter = GetMovingFactor(movingFactor);
    QByteArray* digest = GenerateHMACSHA1(secret, counter);
    int snum = Truncate(digest, truncationOffset);
    int otp = snum % digitsPower[codeDigits];
    int hotp = addChecksum ? (otp * 10) + CalcChecksum(otp, codeDigits) : otp;
    return hotp;
}
