/*
 * settings.cpp
 *
 *  Created on: 28 сент. 2017 г.
 *      Author: drumbox
 */

#include "settings.hpp"

#include <QCoreApplication>


#include <bb/cascades/Application>
#include <bb/cascades/ColorTheme>
#include <bb/cascades/Theme>
#include <bb/cascades/ThemeSupport>
#include <bb/cascades/VisualStyle>

const QString Settings::APP_NAME("BBAuth");
const QString Settings::APP_ORGANIZATION("None");
const QString Settings::FIRST_START("firstStart");
const QString Settings::VISUALSTYLE_KEY("visualStyle");

using namespace bb::cascades;

Settings :: Settings(QObject *parent) : QObject(parent) {
    QCoreApplication::setOrganizationName(APP_ORGANIZATION);
    QCoreApplication::setApplicationName(APP_NAME);

    if (settings.value(FIRST_START).isNull()) {
        settings.setValue(FIRST_START, true);
    }
}

Settings :: ~Settings() {

}


bb::cascades::VisualStyle::Type Settings :: getVisualStyle(){
    return m_visualStyle;
}

void Settings :: setVisualStyle(bb::cascades::VisualStyle::Type visualStyle){
    m_visualStyle = visualStyle;
    settings.setValue(VISUALSTYLE_KEY, QVariant((uint)m_visualStyle));
    emit visualStyleValueChanged(m_visualStyle);
}

bool Settings :: isFirstStart() {
    return settings.value(FIRST_START).toBool();
}

bool Settings :: initializeSettings() {
    bool success = false;
    settings.setValue(FIRST_START, false);
    setVisualStyle(Application::instance()->themeSupport()->theme()->colorTheme()->style());

    return success;
}
