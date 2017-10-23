/*
 * authcodegenerator.hpp
 *
 *  Created on: 22 окт. 2017 г.
 *      Author: drumbox
 */

#ifndef AUTHCODEGENERATOR_HPP_
#define AUTHCODEGENERATOR_HPP_

#include "sbreturn.h"
#include "huctx.h"
#include "hugse56.h"
#include "husha1.h"

#include <QObject>

class AuthCodeGenerator : public QObject {
    Q_OBJECT

public:
    AuthCodeGenerator(QObject* parent = 0);
    AuthCodeGenerator(const sb_GlobalCtx& sbCtx, QObject* parent = 0);
    virtual ~AuthCodeGenerator(){};

    int GenerateHOTP(QString secret, long movingFactor, int codeDigits, bool addChecksum, int truncationOffset);
    int GenerateTOTP(QString secret, long movingFactor, int codeDigits, bool addChecksum, int truncationOffset);

private:
    sb_GlobalCtx m_sbCtx;
    sb_Context hmacContext;

    QByteArray* GenerateHMACSHA1(QString sharedKey, QByteArray counter);
    int CalcChecksum(long num, int digits);
    QByteArray GetMovingFactor(long counter);
    int Truncate(QByteArray *digest_ba, int truncationOffset);
    QString BinToHex(unsigned char *messageDigestHMAC);
};

#endif /* AUTHCODEGENERATOR_HPP_ */
