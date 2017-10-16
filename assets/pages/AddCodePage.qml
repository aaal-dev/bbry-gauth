import bb.cascades 1.4

Page {
    id: addCodePage
    
    signal done()
    
    property alias issuerTitle: issuerTitle.text
    property alias accountName: accountName.text
    property alias secretKey: secretKey.text
    //property string keyLenght
    property int authType
    property int counterValue
    property int periodTime
    property int algorithmType
    
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
    ScrollView {
        content: Container {
            
            layout: DockLayout {}
            
            Container {
                layout: StackLayout {}
                
                Container {
                    leftPadding: ui.du(3)
                    rightPadding: ui.du(3)
                    topPadding: ui.du(2)
                    bottomPadding: ui.du(0)
                    Label {
                        text: qsTr("Enter title, login and secret key from the 2-step authentication setup page")
                        multiline: true
                    }
                }            
                Divider {
                
                }
                Container {
                    leftPadding: ui.du(3)
                    rightPadding: ui.du(3)
                    topPadding: ui.du(0)
                    bottomPadding: ui.du(0)
                    TextField {
                        id: issuerTitle
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
                        id: accountName
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
                    }
                }
                
                Divider {}
                Container {
                    leftPadding: ui.du(3)
                    rightPadding: ui.du(3)
                    topPadding: ui.du(0)
                    bottomPadding: ui.du(0)
                    Label {
                        text: qsTr("Setup preferences for output key. Don't chage it, if you don't know what is for, leave it by default")
                        multiline: true
                    }
                }
                Container {
                    leftPadding: ui.du(3)
                    rightPadding: ui.du(3)
                    topPadding: ui.du(2)
                    bottomPadding: ui.du(0)
                    
                    DropDown {
                        id: keyLenghtDropDownMenu
                        title: qsTr("Key Length:")
                        options: [
                            Option {
                                text: "6"
                                value: 6
                            },
                            Option {
                                text: "7"
                                value: 7
                                selected: true
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
                                id: totpOption
                                text: qsTr("TOTP")
                                description: qsTr("Time based OTP")
                                value: 0
                                onSelectedChanged: {
                                }
                            },
                            Option {
                                id: hotpOption
                                text: qsTr("HOTP")
                                description: qsTr("Counter based OTP")
                                selected: true
                                value: 1
                            }
                        ]
                        onSelectedOptionChanged: {
                            flipVisability();
                        }
                        function flipVisability(){
                            periodTime.visible = !periodTime.visible;
                            counterValue.visible = !counterValue.visible;
                        }
                    }
                    TextField {
                        id: periodTime
                        text: "30"
                        hintText: qsTr("Period time (30 by default)")
                        clearButtonVisible: false
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                        visible: true
                    }
                    TextField {
                        id: counterValue
                        text: "0"
                        hintText: qsTr("Counter value (0 by default)")
                        clearButtonVisible: false
                        input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                        input.submitKey: SubmitKey.Next
                        maximumLength: 4
                        visible: false
                    }
                    DropDown {
                        id: algorithmType
                        title: qsTr("Algorithm:")
                        horizontalAlignment: HorizontalAlignment.Center
                        options: [
                            Option {
                                text: qsTr("SHA-1")
                                description: qsTr("Secure Hash Algorithm 1")
                                selected: true
                                value: 0
                            },
                            Option {
                                text: qsTr("SHA256")
                                description: qsTr("Secure Hash Algorithm 2, 256 bits")
                                value: 1
                            },
                            Option {
                                text: qsTr("SHA512")
                                description: qsTr("Secure Hash Algorithm 2, 512 bits")
                                value: 2
                            }
                        ]
                    }
                }
            }
        }
    }
}