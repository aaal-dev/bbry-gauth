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


#include "applicationui.hpp"

using namespace bb::data;
using namespace bb::system;

ApplicationUI :: ApplicationUI() : QObject(), m_dataModel(0) {
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    Q_ASSERT(res);
    Q_UNUSED(res);
    onSystemLanguageChanged();

    settings = new Settings(this);
    database = new Database(this, DB_PATH, "accounts");

    int rc = SB_SUCCESS;
    rc = hu_GlobalCtxCreateDefault(&sbCtx);
    rc = hu_RegisterSbg56(sbCtx);
    rc = hu_InitSbg56(sbCtx);
    Q_UNUSED(rc);

    startApplication();
    QmlDocument *qml = QmlDocument::create("asset:///pages/MainPage.qml").parent(this);
    qml->setContextProperty("app", this);
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(root);
}

ApplicationUI :: ~ApplicationUI() {
    hu_GlobalCtxDestroy(&sbCtx);
}

void ApplicationUI :: onSystemLanguageChanged() {
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    QString locale_string = QLocale().name();
    QString file_name = QString("GoogleAuthenticator_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

void ApplicationUI :: startApplication(){
    initializeDataModel();
    if (isFirstStart()) {
        settings->initializeSettings();
        database->initializeDatabase();
        readCodeListXML();
    }
    readApplicationSettings();
    getAccountsList(database->getAllRecords());
}

bool ApplicationUI :: isFirstStart() {
    return settings->isFirstStart();
}

bool ApplicationUI :: readApplicationSettings() {
    bool success = false;
    return success;
}

void ApplicationUI :: initializeDataModel() {
    m_dataModel = new GroupDataModel(this);
    m_dataModel->setSortingKeys(QStringList() << "id");
    m_dataModel->setGrouping(ItemGrouping::None);
}

GroupDataModel* ApplicationUI :: getDataModel() const { return m_dataModel; }

bool ApplicationUI :: readCodeListXML() {
    bool success = false;
    XmlDataAccess xda;
    QFile dataFileSpeaker(QDir::currentPath() + "/app/native/assets/model.xml");
    bool ok = dataFileSpeaker.open(QIODevice::ReadOnly);
    QVariant result = xda.loadFromBuffer(dataFileSpeaker.readAll(), "/model/item");
    dataFileSpeaker.close();
    if (!result.isNull() && ok) {
        QVariantList list = result.value<QVariantList>();
        int recordsRead = list.size();
        for(int i = 0; i < recordsRead; i++) {
            QVariantMap map = list.at(i).value<QVariantMap>();
            database->createRecord(
                    map["issuerTitle"].toString(),
                    map["accountName"].toString(),
                    map["secretKey"].toString(),
                    map["authType"].toInt(),
                    map["counterValue"].toInt(),
                    map["periodTime"].toInt(),
                    map["algorithmType"].toInt(),
                    map["keyLenght"].toInt()
                    );
        }
        success = true;
    }
    return success;
}

void ApplicationUI :: parseQRData(const QString& data) {
    QUrl url(data);
    if (url.scheme().toAscii() == "otpauth") {
        Sheet* sheet = new Sheet;
        QmlDocument* qml = QmlDocument::create("asset:///pages/AddCodePage.qml").parent(this);
        AbstractPane* page = qml->createRootObject<AbstractPane>();
        if (url.path().contains(":")) {
            if (url.hasQueryItem("issuer")) {
                page->setProperty("issuerTitleProperty", QUrl::fromPercentEncoding(url.queryItemValue("issuer").toAscii()));
            } else {
                page->setProperty("issuerTitleProperty", QUrl::fromPercentEncoding(url.path().mid(1).section(":", 0).toAscii()));
            }
            page->setProperty("accountNameProperty", QUrl::fromPercentEncoding(url.path().mid(1).section(":", 1).toAscii()));
        } else {
            page->setProperty("accountNameProperty", QUrl::fromPercentEncoding(url.path().mid(1).toAscii()));
        }
        page->setProperty("secretKeyProperty", url.queryItemValue("secret").toAscii());
        if (url.host().toAscii() == "hotp"){
            page->setProperty("authTypeProperty", 0);
        }
        if (url.host().toAscii() == "totp"){
            page->setProperty("authTypeProperty", 1);
        }
        if (url.hasQueryItem("counter")) {
            page->setProperty("counterValueProperty", url.queryItemValue("counter").toUInt());
        } else {
            page->setProperty("counterValueProperty", 0);
        }
        if (url.hasQueryItem("period")) {
            page->setProperty("periodTimeProperty", url.queryItemValue("period").toUInt());
        } else {
            page->setProperty("periodTimeProperty", 30);
        }
        if (url.hasQueryItem("algorithm")) {
            QString algorithm = url.queryItemValue("algorithm").toAscii();
            if (algorithm == "SHA1") {
                page->setProperty("algorithmTypeProperty", 0);
            }
            if (algorithm == "SHA256") {
                page->setProperty("algorithmTypeProperty", 1);
            }
            if (algorithm == "SHA512") {
                page->setProperty("algorithmTypeProperty", 2);
            }
        } else {
            page->setProperty("algorithmTypeProperty", 0);
        }
        if (url.hasQueryItem("digits")) {
            page->setProperty("authCodeLenghtProperty", url.queryItemValue("digits").toUInt());
        }
        bool res = QObject::connect(page, SIGNAL(done()), sheet, SLOT(close()));
        Q_ASSERT(res);
        Q_UNUSED(res);

        sheet->setContent(page);
        sheet->open();
    } else {
        alert("Не подходящий QR код");
    }
}

void ApplicationUI :: addNewAccount
(
        const QString& issuerTitle,
        const QString& accountName,
        const QString& secretKey,
        const int& authType,
        const int& counterValue,
        const int& periodTime,
        const int& algorithmType,
        const int& authCodeLenght
) {
    int id = database->createRecord(
            issuerTitle,
            accountName,
            secretKey,
            authType,
            counterValue,
            periodTime,
            algorithmType,
            authCodeLenght
            );
    getAccountsList(database->getRecordbyId(id));
}

void ApplicationUI :: deleteAccount(QVariantList indexPath) {
    if (!indexPath.isEmpty()) {
        QObject* object = qvariant_cast<QObject*>(m_dataModel->data(indexPath));
        Accounts* account = qobject_cast<Accounts*>(object);
        int id = account->getId();
        if (database->deleteAccount(id)) {
            m_dataModel->remove(account);
        }
    }
}

bool ApplicationUI :: getAccountsList(QVariantList* list) {
    if (!list->isEmpty()) {
        for(int i = 0; i < list->size(); i++) {
            QVariantMap map = list->at(i).value<QVariantMap>();
            Accounts *account = new Accounts(
                    map["id"].toInt(),
                    map["issuer_title"].toString(),
                    map["account_name"].toString(),
                    map["secret_key"].toString(),
                    map["auth_type"].toInt(),
                    map["counter_value"].toInt(),
                    map["period_time"].toInt(),
                    map["algorithm_type"].toInt(),
                    map["auth_code_lenght"].toInt(),
                    map["publish_date"].toInt(),
                    map["edit_date"].toInt(),
                    this);
            Q_UNUSED(account);
            m_dataModel->insert(account);
        }
        return true;
    }
    return false;
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
