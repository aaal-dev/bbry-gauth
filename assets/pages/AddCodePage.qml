import bb.cascades 1.4

NavigationPane {
    id: addCodeNavigationPane
    signal done()
    Page {
        id: addCodePage
        
        signal done()
        
        property string issuerTitleProperty
        property string accountNameProperty
        property string secretKeyProperty
        property int authTypeProperty
        property int counterValueProperty
        property int periodTimeValueProperty
        property int algorithmTypeProperty
        property int authCodeLenghtProperty
        
        onIssuerTitlePropertyChanged: {
            issuerTitleTextField.text = issuerTitleProperty
        }
        
        onAccountNamePropertyChanged: {
            accountNameTextField.text = accountNameProperty
        }
        
        onSecretKeyPropertyChanged: {
            secretKeyTextField.text = secretKeyProperty
        }
        
        onAuthTypePropertyChanged: {
            for (var index = 0; index < authTypeDropDownMenu.count(); index ++) {
                if (authTypeDropDownMenu.at(index).value == authTypeProperty) {
                    authTypeDropDownMenu.at(index).setSelected(true);
                }
            }
        
        }
        
        onCounterValuePropertyChanged: {
            counterValueTextField.text = counterValueProperty
        }
        
        onPeriodTimeValuePropertyChanged: {
            periodTimeTextField.text = periodTimeValueProperty
        }
        
        onAlgorithmTypePropertyChanged: {
            for(var index = 0; index < algorithmTypeDropDownMenu.count(); index++) {
                if (algorithmTypeDropDownMenu.at(index).value == algorithmTypeProperty) {
                    algorithmTypeDropDownMenu.at(index).setSelected(true);
                }
            }
        }
        
        onAuthCodeLenghtPropertyChanged: {
            for(var index = 0; index < keyLenghtDropDownMenu.count(); index++) {
                if (keyLenghtDropDownMenu.at(index).value == authCodeLenghtProperty) {
                    keyLenghtDropDownMenu.at(index).setSelected(true);
                }
            }
        }
        
        titleBar: TitleBar {
            title: qsTr("Add Code") + Retranslate.onLocaleOrLanguageChanged
            kind: TitleBarKind.Default
            acceptAction: ActionItem {
                title: qsTr("Create") + Retranslate.onLocaleOrLanguageChanged
                onTriggered: {
                    _app.addAccount();
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
        actions: [
            ActionItem {
                title: qsTr("Advanced")
                ActionBar.placement: ActionBarPlacement.OnBar
                imageSource: "asset:///images/icons/ic_next.png"
                onTriggered: {
                    addCodeNavigationPane.push(advancedPropertiesDefinition.createObject());
                }
            }
        ]
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
                            id: issuerTitleTextField
                            inputMode: TextFieldInputMode.Text
                            input.submitKey: SubmitKey.Next
                            hintText: qsTr("Title")
                        }
                        TextField {
                            id: accountNameTextField
                            inputMode: TextFieldInputMode.EmailAddress
                            input.submitKey: SubmitKey.Next
                            hintText: qsTr("Your login")
                        }
                        TextField {
                            id: secretKeyTextField
                            hintText: qsTr("Secret key")
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
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                }
            }
            attachedObjects: [
                ComponentDefinition {
                    id: advancedPropertiesDefinition
                    content: 
                    Page {
                        titleBar: TitleBar {
                            title: qsTr("Advanced Properties") + Retranslate.onLocaleOrLanguageChanged
                            kind: TitleBarKind.Default
                        }
                        Container {
                            Container {
                                leftPadding: ui.du(3)
                                rightPadding: ui.du(3)
                                topPadding: ui.du(2)
                                bottomPadding: ui.du(0)
                                Label {
                                    text: qsTr("Setup preferences for output key. Don't chage it, if you don't know what is for, leave it by default")
                                    multiline: true
                                }
                            }
                            Divider {}
                            Container {
                                leftPadding: ui.du(3)
                                rightPadding: ui.du(3)
                                topPadding: ui.du(0)
                                bottomPadding: ui.du(0)
                                
                                DropDown {
                                    id: authTypeDropDownMenu
                                    title: qsTr("Type:")
                                    horizontalAlignment: HorizontalAlignment.Center
                                    options: [
                                        Option {
                                            id: totpOption
                                            text: qsTr("Time based OTP")
                                            description: qsTr("TOTP")
                                            value: "totp"
                                            selected: true
                                        },
                                        Option {
                                            id: hotpOption
                                            text: qsTr("Counter based OTP")
                                            description: qsTr("HOTP")
                                            value: "hotp"
                                        }
                                    ]
                                    onCreationCompleted: {
                                        flipVisability(authTypeDropDownMenu.selectedValue);
                                    }
                                    onSelectedOptionChanged: {
                                        flipVisability(authTypeDropDownMenu.selectedValue);
                                    }
                                    function flipVisability(value){
                                        if (value == "totp"){
                                            algorithmTypeDropDownMenu.visible = true;
                                            periodTimeTextField.visible = true;
                                            counterValueTextField.visible = false;
                                        } else {
                                            for (var index = 0; index < algorithmTypeDropDownMenu.count(); index ++) {
                                                if (algorithmTypeDropDownMenu.at(index).value == "SHA1") {
                                                    algorithmTypeDropDownMenu.at(index).selected = true
                                                    algorithmTypeDropDownMenu.visible = false;
                                                }
                                            }
                                            periodTimeTextField.visible = false;
                                            counterValueTextField.visible = true;
                                        }
                                    }
                                }
                                
                                TextField {
                                    id: periodTimeTextField
                                    text: "30"
                                    hintText: qsTr("Period time (30 by default)")
                                    clearButtonVisible: false
                                    input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                                    input.submitKey: SubmitKey.Next
                                    maximumLength: 4
                                    visible: true
                                }
                                TextField {
                                    id: counterValueTextField
                                    text: "0"
                                    hintText: qsTr("Counter value (0 by default)")
                                    clearButtonVisible: false
                                    input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                                    input.submitKey: SubmitKey.Next
                                    maximumLength: 4
                                    visible: false
                                }
                                DropDown {
                                    id: algorithmTypeDropDownMenu
                                    title: qsTr("Algorithm:")
                                    horizontalAlignment: HorizontalAlignment.Center
                                    options: [
                                        Option {
                                            text: qsTr("SHA-1")
                                            description: qsTr("Secure Hash Algorithm 1")
                                            value: "SHA1"
                                            selected: true
                                        },
                                        Option {
                                            text: qsTr("SHA256")
                                            description: qsTr("Secure Hash Algorithm 2, 256 bits")
                                            value: "SHA256"
                                        },
                                        Option {
                                            text: qsTr("SHA512")
                                            description: qsTr("Secure Hash Algorithm 2, 512 bits")
                                            value: "SHA512"
                                        }
                                    ]
                                }
                                DropDown {
                                    id: keyLenghtDropDownMenu
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
                            }
                            Divider {}
                        }
                    }                    
                }
            ]
        }
    }
}