import bb.cascades 1.4

Page {
    id: settingsPage
    signal done()
    
    titleBar: TitleBar {
        title: qsTr("Settings") + Retranslate.onLocaleOrLanguageChanged
        kind: TitleBarKind.Default
        acceptAction: ActionItem {
            title: qsTr("OK") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                settingsPage.done()
            }
        }
        dismissAction: ActionItem {
            title: qsTr("Cancel") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                settingsPage.done()
            }
        }
        
    }
    Container {
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            
            }
            topPadding: 10.0
            leftPadding: 10.0
            rightPadding: 10.0
            bottomPadding: 10.0
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
                        Application.themeSupport.setVisualStyle(VisualStyle.Dark);
                    }       
                    else {
                        Application.themeSupport.setVisualStyle(VisualStyle.Bright);
                    }
                }
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            
            }
            topPadding: 10.0
            leftPadding: 10.0
            rightPadding: 10.0
            bottomPadding: 10.0
            Label {
                horizontalAlignment: HorizontalAlignment.Center
                text: qsTr("Secure connection") + Retranslate.onLocaleOrLanguageChanged
                verticalAlignment: VerticalAlignment.Center
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0
                
                }
                textStyle.fontSize: FontSize.Medium
            }
            ToggleButton {
                onCheckedChanged: {

                }
            }
        }
    }
}

    
