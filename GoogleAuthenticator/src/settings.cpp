/*
 * settings.cpp
 *
 *  Created on: 28 сент. 2017 г.
 *      Author: drumbox
 */

#include "settings.hpp"

#include <QCoreApplication>
#include <QSettings>

#include <bb/cascades/Application>
#include <bb/cascades/ColorTheme>
#include <bb/cascades/Theme>
#include <bb/cascades/ThemeSupport>
#include <bb/cascades/VisualStyle>

const QString Settings::APP_NAME("BBAuth");
const QString Settings::APP_ORGANIZATION("None");
const QString Settings::VISUALSTYLE_KEY("visualStyle");

using namespace bb::cascades;

Settings :: Settings (QObject *parent) : QObject(parent) {
    QCoreApplication::setOrganizationName(APP_ORGANIZATION);
    QCoreApplication::setApplicationName(APP_NAME);
    QSettings settings;

    if (settings.value(VISUALSTYLE_KEY).isNull()) {
        VisualStyle::Type appVisualStyle = Application::instance()->themeSupport()->theme()->colorTheme()->style();
        setVisualStyle(appVisualStyle);
    } else {
        VisualStyle::Type storedStyle = static_cast<VisualStyle::Type>(settings.value(VISUALSTYLE_KEY).toUInt());
        setVisualStyle(storedStyle);
    }
}

Settings :: ~Settings () {

}


bb::cascades::VisualStyle::Type Settings :: getVisualStyle(){
    return m_visualStyle;
}

void Settings :: setVisualStyle(bb::cascades::VisualStyle::Type visualStyle){
    m_visualStyle = visualStyle;
    emit visualStyleValueChanged(m_visualStyle);
    QSettings().setValue(VISUALSTYLE_KEY, QVariant((uint)m_visualStyle));
}
