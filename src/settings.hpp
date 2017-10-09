/*
 * settings.hpp
 *
 *  Created on: 28 сент. 2017 г.
 *      Author: drumbox
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <QObject>
#include <QSettings>
#include <bb/cascades/VisualStyle>



class Settings : public QObject {
    Q_OBJECT
    Q_PROPERTY(bb::cascades::VisualStyle::Type visualStyle READ getVisualStyle WRITE setVisualStyle NOTIFY visualStyleValueChanged FINAL)

public:
    Settings(QObject *parent);
    virtual ~Settings();

    bb::cascades::VisualStyle::Type getVisualStyle();
    void setVisualStyle(bb::cascades::VisualStyle::Type visualStyle);

    bool isFirstStart();
    bool initializeSettings();

signals:
    void visualStyleValueChanged(bb::cascades::VisualStyle::Type);

public slots:
    void onVisualStyleChanged();

private:
    static const QString APP_NAME;
    static const QString APP_ORGANIZATION;
    static const QString FIRST_START;
    static const QString VISUALSTYLE_KEY;

    QSettings settings;

    bb::cascades::VisualStyle::Type m_visualStyle;
};

#endif /* SETTINGS_HPP_ */
