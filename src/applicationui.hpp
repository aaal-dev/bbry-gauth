/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QObject>

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/GroupDataModel>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include <bb/cascades/LocaleHandler>
#include <bb/data/XmlDataAccess>
#include <bb/system/SystemDialog>

#include "sbreturn.h"
#include "huctx.h"
#include "hugse56.h"

#include "datamodels/accounts.hpp"
#include "database.hpp"
#include "settings.hpp"

static const QString DB_PATH = QDir::homePath() + "/bbauth.db";
static const QString CONN_NAME = "bbauthdb";

namespace bb {
    namespace cascades {
        class LocaleHandler;
    }
}

class Accounts;
class Database;
class QTranslator;
class Settings;

using namespace bb::cascades;

class ApplicationUI : public QObject {
    Q_OBJECT
    Q_PROPERTY(bb::cascades::DataModel* dataModel READ getDataModel CONSTANT)

public:
    ApplicationUI();
    virtual ~ApplicationUI();

    Q_INVOKABLE void parseQRData(const QString&);
    Q_INVOKABLE void addAccount(
            const QString&,
            const QString&,
            const QString&,
            const int&,
            const int&,
            const int&,
            const int&,
            const int&);

private slots:
    void onSystemLanguageChanged();

private:
    QTranslator* m_pTranslator;
    LocaleHandler* m_pLocaleHandler;
    GroupDataModel* m_dataModel;
    Settings* settings;
    Database* database;
    sb_GlobalCtx sbCtx;

    void startApplication();
    bool connectDatabase();
    bool isFirstStart();
    bool readApplicationSettings();
    void initializeDataModel();
    bool readCodeListXML();
    bool getAccountsList();

    GroupDataModel* getDataModel() const;
    void alert(const QString&);
};

#endif /* ApplicationUI_HPP_ */
