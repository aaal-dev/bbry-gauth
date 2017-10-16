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
#include <bb/cascades/GroupDataModel>


namespace bb {
    namespace cascades {
        class LocaleHandler;
    }
}

class QTranslator;
class Settings;
class Database;

using namespace bb::cascades;

class ApplicationUI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DataModel* dataModel READ getDataModel CONSTANT)

public:
    ApplicationUI();
    virtual ~ApplicationUI() {}

    Q_INVOKABLE void parseBarcodeData(const QString&);

private slots:
    void onSystemLanguageChanged();

private:
    QTranslator* m_pTranslator;
    LocaleHandler* m_pLocaleHandler;
    GroupDataModel* m_dataModel;
    Settings* settings;
    Database* database;

    bool isFirstStart();
    bool initializeApplication();
    bool readApplicationSettings();
    void initializeDataModel();
    bool readCodeList();

    GroupDataModel* getDataModel() const;
    void alert(const QString&);
};

#endif /* ApplicationUI_HPP_ */
