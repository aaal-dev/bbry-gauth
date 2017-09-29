/*
 * settings.hpp
 *
 *  Created on: 28 сент. 2017 г.
 *      Author: drumbox
 */

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <QObject>
#include <bb/cascades/VisualStyle>



class Settings : public QObject {
    Q_OBJECT
    Q_PROPERTY(bb::cascades::VisualStyle::Type visualStyle READ getVisualStyle WRITE setVisualStyle NOTIFY visualStyleValueChanged FINAL)

public:
    Settings(QObject *parent);
    virtual ~Settings();

    bb::cascades::VisualStyle::Type getVisualStyle();
    void setVisualStyle(bb::cascades::VisualStyle::Type visualStyle);

signals:
    void visualStyleValueChanged(bb::cascades::VisualStyle::Type);

private:
    static const QString APP_NAME;
    static const QString APP_ORGANIZATION;
    static const QString VISUALSTYLE_KEY;

    bb::cascades::VisualStyle::Type m_visualStyle;
};

#endif /* SETTINGS_HPP_ */
