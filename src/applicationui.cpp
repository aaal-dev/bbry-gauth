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

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Page>
#include <bb/cascades/Sheet>
#include <bb/cascades/LocaleHandler>

#include <bb/system/SystemDialog>

#include "applicationui.hpp"
#include "settings.hpp"
#include "database.hpp"


using namespace bb::cascades;
using namespace bb::system;

ApplicationUI :: ApplicationUI() : QObject(), m_dataModel(0) {
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    settings = new Settings(this);
    database = new Database(this);
    if (isFirstStart()) { initializeApplication(); }
    readApplicationSettings();
    readCodeList();
    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);
    Q_UNUSED(res);
    onSystemLanguageChanged();
    QmlDocument *qml = QmlDocument::create("asset:///pages/MainPage.qml").parent(this);
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
    qml->setContextProperty("_app", this);
}

void ApplicationUI :: onSystemLanguageChanged() {
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    QString locale_string = QLocale().name();
    QString file_name = QString("GoogleAuthenticator_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

bool ApplicationUI :: isFirstStart() {
    return settings->isFirstStart();
}

bool ApplicationUI :: initializeApplication() {
    bool success = false;
    if (database->initializeDatabase()){
        if (settings->initializeSettings()){
            success = true;
        }
    }
    database->createRecord();
    return success;
}

bool ApplicationUI :: readApplicationSettings() {
    bool success = false;
    return success;
}

void ApplicationUI :: initializeDataModel()
{
    m_dataModel = new GroupDataModel(this);
    m_dataModel->setSortingKeys(QStringList() << "title");
    m_dataModel->setGrouping(ItemGrouping::None);
}

bool ApplicationUI :: readCodeList() {
    bool success = false;
    initializeDataModel();
    m_dataModel->clear();
    QVariant result = database->readRecords();
    if (!result.isNull()) {
        QVariantList list = result.value<QVariantList>();
        int recordsListSize = list.size();
        for (int i = 0; i < recordsListSize; i++) {
            QVariantMap map = list.at(i).value<QVariantMap>();
            //CodeListItem *listItem = new CodeListItem();
            //m_dataModel->insert(listItem);
        }
        success = true;
    }
    return success;
}

GroupDataModel* ApplicationUI :: getDataModel() const
{
    return m_dataModel;
}

void ApplicationUI :: parseBarcodeData(const QString& data) {
    QUrl url(data);
    if (url.scheme().toAscii() == "otpauth") {
        Sheet* sheet = new Sheet;
        QmlDocument* qml = QmlDocument::create("asset:///pages/AddCodePage.qml").parent(this);
        Page *page = qml->createRootObject<Page>();


        if (url.host() == "hotp") {
            page->setProperty("authType", false);
        } else {
            page->setProperty("authType", true);
        }

        // property alias issuerTitle: issuerTitle.text
        if (url.hasQueryItem("issuer")) {
            page->setProperty("issuerTitle", url.queryItemValue("issuer"));
        }

        // property alias accountName: accountName.text
        page->setProperty("accountName", url.path());

        // property alias secretKey: secretKey.text
        page->setProperty("secretKey", url.queryItemValue("secret"));

        // property alias keyLenght
        if (url.hasQueryItem("digits")) {
            page->setProperty("keyLenght", url.queryItemValue("digits"));
        }


        // property int counterValue
        if (url.hasQueryItem("counter")) {
            //page->setProperty("counterValue", url.queryItemValue("counter"));
        }

        // property int periodTime
        if (url.hasQueryItem("period")) {
            page->setProperty("periodTime", url.queryItemValue("period"));
        }

        // property int algorithmType
        //QString algorithmType;
        //if (url.hasQueryItem("algorithm")) {
        //    algorithmType = url.queryItemValue("algorithm");
        //}

        sheet->setContent(page);
        sheet->open();
    }
}

void ApplicationUI :: alert(const QString &message) {
    SystemDialog *dialog = new SystemDialog(tr("OK"), 0);
    dialog->setTitle(tr("Alert"));
    dialog->setBody(message);
    dialog->setDismissAutomatically(true);
    bool ok = connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_ASSERT(ok);
    dialog->show();
}
