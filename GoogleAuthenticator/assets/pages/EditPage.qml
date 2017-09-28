import bb.cascades 1.4

Page {
    id: addManualyPage;
    signal done()
    
    titleBar: TitleBar {
        title: qsTr("Manual edit") + Retranslate.onLocaleOrLanguageChanged
        kind: TitleBarKind.Default
        acceptAction: ActionItem {
            title: qsTr("Create") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                database.title = title.text;
                database.auth_login = auth_login.text;
                database.secret_code = secret_code_part1.text + secret_code_part2.text + secret_code_part3.text + secret_code_part4.text;
                database.key_lenght = key_lenght.selectedOption;
                database.auth_type = auth_type.selectedOption;
                database.WriteData();
                addManualyPage.done();
            }
        }
        dismissAction: ActionItem {
            title: qsTr("Cancel") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                addManualyPage.done()
            }
        }
    }
        
    content: Container {
        leftPadding: 20.0
        rightPadding: 20.0
        topPadding: 20.0
        bottomPadding: 20.0
        layout: DockLayout {}
        
        Container {
            layout: StackLayout {}
                        
            Label {
                text: qsTr("Enter web-service title, auth login and secret key from the 2-step authentication setup page")
                multiline: true
            }
            Label {}
            TextField {
                id: title
                inputMode: TextFieldInputMode.Text
                input.submitKey: SubmitKey.Next
                hintText: qsTr("Title")
            }
            TextField {
                id: auth_login
                inputMode: TextFieldInputMode.EmailAddress
                input.submitKey: SubmitKey.Next
                hintText: qsTr("Your login")
            }
            Label {}
            
            Container {
                background: Color.create("#ffa5dae4")
                topPadding: 20.0
                leftPadding: 20.0
                rightPadding: 20.0
                bottomPadding: 20.0
                Label {
                    text: qsTr("Two factor authentication code")
                    textStyle.textAlign: TextAlign.Center
                    horizontalAlignment: HorizontalAlignment.Center
                }
                Container {
                    id: secret_key
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    
                    }
                    layoutProperties: StackLayoutProperties {
                    
                    }
                    
                    TextField {
                        id: secret_key_part1
                        hintText: qsTr("")
                        clearButtonVisible: true
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                    }
                    TextField {
                        id: secret_key_part2
                        hintText: qsTr("")
                        clearButtonVisible: true
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                    }
                    TextField {
                        id: secret_key_part3
                        hintText: qsTr("")
                        clearButtonVisible: true
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                    }
                    TextField {
                        id: secret_key_part4
                        hintText: qsTr("")
                        clearButtonVisible: true
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                    }
                }                
            }       
            Label {}
            
            Divider {}
            Label {
                text: qsTr("Setup preferences for output key. If you don't know, leave it by default")
                multiline: true
            }
            DropDown {
                id: key_lenght
                title: qsTr("Key Length:")
                options: [
                    Option {
                        text: "6"
                        value: 6
                        selected: true
                    },
                    Option {
                        text: "7"
                        value: 7
                    },
                    Option {
                        text: "8"
                        value: 8
                    },
                    Option {
                        text: "9"
                        value: 9
                    }
                ]
            }
            DropDown {
                id: auth_type
                title: qsTr("Type:")
                horizontalAlignment: HorizontalAlignment.Center
                options: [
                    Option {
                        text: qsTr("Time based OTP")
                        description: qsTr("Time based OTP")
                        selected: true
                    },
                    Option {
                        text: qsTr("Counter based OTP")
                        description: qsTr("Counter based OTP")
                    }
                ]
            }
        }
        
    }
}
