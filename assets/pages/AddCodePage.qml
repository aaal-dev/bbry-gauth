import bb.cascades 1.4

Page {
    id: addCodePage
    
    signal done()
    
    property string url
    
    titleBar: TitleBar {
        title: qsTr("Add code") + Retranslate.onLocaleOrLanguageChanged
        kind: TitleBarKind.Default
        acceptAction: ActionItem {
            title: qsTr("Create") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                //_database.title = title.text;
                //_database.authLogin = authLogin.text;
                //_database.secretCode = secretKeyPart1.text + secretKeyPart2.text + secretKeyPart3.text + secretKeyPart4.text;
                //_database.keyLenght = keyLenght.selectedOption.value;
                //_database.authType = authType.selectedOption.value;
                //_database.writeData();
                done();
            }
            enabled: false
        }
        dismissAction: ActionItem {
            title: qsTr("Cancel") + Retranslate.onLocaleOrLanguageChanged
            onTriggered: {
                done()
            }
        }
    }
    
    content: Container {
        
        layout: DockLayout {}
        
        Container {
            layout: StackLayout {}
            
            Container {
                leftPadding: ui.du(2)
                rightPadding: ui.du(2)
                topPadding: ui.du(2)
                bottomPadding: ui.du(0)
                Label {
                    text: qsTr("Enter web-service title, auth login and secret key from the 2-step authentication setup page")
                    multiline: true
                }
            }            
            Divider {
            
            }
            Container {
                leftPadding: ui.du(2)
                rightPadding: ui.du(2)
                topPadding: ui.du(0)
                bottomPadding: ui.du(2)
                TextField {
                    id: title
                    inputMode: TextFieldInputMode.Text
                    input.submitKey: SubmitKey.Next
                    hintText: qsTr("Title")
                    validator: Validator {
                        mode: ValidationMode.Immediate
                        errorMessage: "Name title"
                        onValidate: {
                            if (title.text.length < 1)
                                state = ValidationState.Valid;
                            else
                                state = ValidationState.Invalid;
                        }
                    }
                }
                TextField {
                    id: authLogin
                    inputMode: TextFieldInputMode.EmailAddress
                    input.submitKey: SubmitKey.Next
                    hintText: qsTr("Your login")
                    validator: Validator {
                        mode: ValidationMode.Immediate
                        errorMessage: "Enter your login"
                        onValidate: {
                            if (authLogin.text.length < 1)
                                state = ValidationState.Valid;
                            else
                                state = ValidationState.Invalid;
                        }
                    }
                }
                TextField {
                    id: secretKey
                    hintText: qsTr("Authentication code")
                    clearButtonVisible: true
                    input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                    input.submitKey: SubmitKey.Next
                    maximumLength: 4
                }
            }
            
            Divider {}
            Container {
                leftPadding: ui.du(2)
                rightPadding: ui.du(2)
                topPadding: ui.du(0)
                bottomPadding: ui.du(0)
                Label {
                    text: qsTr("Setup preferences for output key. If you don't know, leave it by default")
                    multiline: true
                }
            }
            Container {
                leftPadding: ui.du(2)
                rightPadding: ui.du(2)
                topPadding: ui.du(2)
                bottomPadding: ui.du(0)
                DropDown {
                    id: keyLenght
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
                    id: authType
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
    onCreationCompleted: {
        if (url) {
            _database.getDatafromURLString(url)
        }
    }
}