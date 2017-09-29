import bb.cascades 1.4

Page {
    id: settingsPage
    signal done()
    
    titleBar: TitleBar {
        title: qsTr("Settings") + Retranslate.onLocaleOrLanguageChanged
    }
    ScrollView {
        Container {
            Header {
                title: qsTr("Theme") + Retranslate.onLocaleOrLanguageChanged
            }
            
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                
                }
                topPadding: ui.du(2)
                leftPadding: topPadding
                rightPadding: leftPadding
                bottomPadding: rightPadding
                Label {
                    horizontalAlignment: HorizontalAlignment.Center
                    text: qsTr("Dark theme") + Retranslate.onLocaleOrLanguageChanged
                    verticalAlignment: VerticalAlignment.Center
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0
                    
                    }
                    textStyle.fontSize: FontSize.Medium
                }
                ToggleButton {
                    onCheckedChanged: {
                        if (checked) {
                            _settings.visualStyle = VisualStyle.Dark;
                        }       
                        else {
                            _settings.visualStyle = VisualStyle.Bright;
                        }
                    }
                }
            }
            
            Container {
                topPadding: ui.du(0)
                leftPadding: ui.du(2)
                rightPadding: leftPadding
                bottomPadding: rightPadding
                
                DropDown {
                    title: qsTr("Color") + Retranslate.onLocaleOrLanguageChanged
                    
                }
            }
        }
    }
}

    
