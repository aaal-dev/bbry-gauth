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
    // Определяем соответвие строки, убирая ошибочные
    if (url.scheme().toAscii() == "otpauth") {

        Sheet* sheet = new Sheet;
        QmlDocument* qml = QmlDocument::create("asset:///pages/AddCodePage.qml").parent(this);
        Page *page = qml->createRootObject<Page>();

        // Выделяю метод генерации кода, Периодический (TOTP) или по Счетчику (HOTP)
        page->setProperty("authTypeProperty", url.host().toAscii());

        // Выделяю Название и Логин
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

        // Выделяю секретный код
        page->setProperty("secretKeyProperty", url.queryItemValue("secret").toAscii());

        // Выделяю количество цифр конечного кода
        if (url.hasQueryItem("digits")) {
            page->setProperty("keyLenghtProperty", url.queryItemValue("digits").toAscii());
        }

        // property int counterValue
        if (url.hasQueryItem("counter")) {
            page->setProperty("counterValueProperty", url.queryItemValue("counter").toUInt());
        } else {
            page->setProperty("counterValueProperty", 0);
        }

        // property int periodTime
        if (url.hasQueryItem("period")) {
            page->setProperty("periodTimeValueProperty", url.queryItemValue("period").toUInt());
        } else {
            page->setProperty("periodTimeValueProperty", 30);
        }

        // property int algorithmType
        if (url.hasQueryItem("algorithm")) {
            page->setProperty("algorithmTypeProperty", url.queryItemValue("algorithm").toAscii());
        } else {
            page->setProperty("algorithmTypeProperty", "SHA1");
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

void ApplicationUI :: alert(const QString &message) {
    SystemDialog *dialog = new SystemDialog(tr("OK"), 0);
    dialog->setTitle(tr("Alert"));
    dialog->setBody(message);
    dialog->setDismissAutomatically(true);
    bool ok = connect(dialog, SIGNAL(finished(bb::system::SystemUiResult::Type)), dialog, SLOT(deleteLater()));
    Q_ASSERT(ok);
    dialog->show();
}
