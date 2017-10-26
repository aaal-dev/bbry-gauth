import bb.cascades 1.4

NavigationPane {
    id: addCodeNavigationPane
    
    signal done()
    
    property string issuerTitleProperty
    property string accountNameProperty
    property string secretKeyProperty
    property int authTypeProperty
    property int counterValueProperty
    property int periodTimeProperty
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
    
    onPeriodTimePropertyChanged: {
        periodTimeTextField.text = periodTimeProperty
    }
    
    onAlgorithmTypePropertyChanged: {
        for(var index = 0; index < algorithmTypeDropDownMenu.count(); index++) {
            if (algorithmTypeDropDownMenu.at(index).value == algorithmTypeProperty) {
                algorithmTypeDropDownMenu.at(index).setSelected(true);
            }
        }
    }
    
    onAuthCodeLenghtPropertyChanged: {
        for(var index = 0; index < authCodeLenghtDropDownMenu.count(); index++) {
            if (authCodeLenghtDropDownMenu.at(index).value == authCodeLenghtProperty) {
                authCodeLenghtDropDownMenu.at(index).setSelected(true);
            }
        }
    }
    
    Page {
        id: addCodePage
        
        titleBar: TitleBar {
            title: qsTr("Add Code") + Retranslate.onLocaleOrLanguageChanged
            kind: TitleBarKind.Default
            acceptAction: ActionItem {
                id: acceptAction
                title: qsTr("Create") + Retranslate.onLocaleOrLanguageChanged
                onTriggered: {
                    addCodeNavigationPane.done();
                    Qt.app.addAccount(
                        issuerTitleProperty, 
                        accountNameProperty, 
                        secretKeyProperty, 
                        authTypeProperty, 
                        counterValueProperty, 
                        periodTimeProperty, 
                        algorithmTypeProperty, 
                        authCodeLenghtProperty);
                    
                }
                enabled: false
            }
            dismissAction: ActionItem {
                id: dismissAction
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
                    Divider {}
                    Container {
                        leftPadding: ui.du(3)
                        rightPadding: ui.du(3)
                        topPadding: ui.du(0)
                        bottomPadding: ui.du(0)
                        Label {
                            text: qsTr("Title")
                        }
                        TextField {
                            id: issuerTitleTextField
                            textFormat: TextFormat.Plain
                            inputMode: TextFieldInputMode.Text
                            input.submitKey: SubmitKey.Next
                            hintText: qsTr("Name your account")
                            onTextChanged: {
                                issuerTitleProperty = issuerTitleTextField.text
                            }
                            validator: Validator {
                                mode: ValidationMode.Immediate
                                onValidate: {
                                    if (issuerTitleTextField.text.length > 0) {
                                        state = ValidationState.Valid;
                                        acceptAction.setEnabled(true)
                                    } else {
                                        state = ValidationState.Invalid;
                                        errorMessage = "Title must be at least 1 character long."
                                        acceptAction.setEnabled(false)
                                    }
                                    
                                }
                            }
                        }
                        Label {
                            text: qsTr("Account login")
                        }
                        TextField {
                            id: accountNameTextField
                            inputMode: TextFieldInputMode.EmailAddress
                            input.submitKey: SubmitKey.Next
                            hintText: qsTr("Place your login")
                            onTextChanged: {
                                accountNameProperty = accountNameTextField.text
                            }
                            validator: Validator {
                                mode: ValidationMode.Immediate
                                errorMessage: "Account login must be at least 1 character long."
                                
                                onValidate: {
                                    if (accountNameTextField.text.length > 0) {
                                        state = ValidationState.Valid;
                                        acceptAction.setEnabled(true)
                                    } else {
                                        state = ValidationState.Invalid;
                                        acceptAction.setEnabled(false)
                                    }
                                    
                                        
                                }

                            }
                            textFormat: TextFormat.Plain
                        }
                        Label {
                            text: qsTr("Secret key")
                        }
                        TextField {
                            id: secretKeyTextField
                            hintText: qsTr("Insert the key")
                            input.flags: TextInputFlag.AutoCapitalizationOff | TextInputFlag.AutoCorrectionOff | TextInputFlag.AutoPeriodOff | TextInputFlag.PredictionOff | TextInputFlag.SpellCheckOff | TextInputFlag.WordSubstitutionOff
                            input.submitKey: SubmitKey.Next
                            textFormat: TextFormat.Plain
                            input.masking: TextInputMasking.MaskedNotTogglable
                            inputMode: TextFieldInputMode.Password
                            validator: Validator {
                                mode: ValidationMode.Immediate
                                errorMessage: "Your secret key must be at least 1 character long."
                                
                                onValidate: {
                                    if (secretKeyTextField.text.length > 0) {
                                        state = ValidationState.Valid;
                                        acceptAction.setEnabled(true)
                                    } else {
                                        state = ValidationState.Invalid;
                                        acceptAction.setEnabled(false)
                                    }
                                }                            
                            }
                            onTextChanged: {
                                secretKeyProperty = secretKeyTextField.text
                            }
                        }
                    }
                    Divider {}
                    Container {
                        leftPadding: ui.du(3)
                        rightPadding: ui.du(3)
                        topPadding: ui.du(0)
                        bottomPadding: ui.du(0)
                        Label {
                            text: qsTr("All three fields must be filled by information. «Secret Key» field is necessary. But other two you can fill that you want in you choice.")
                            multiline: true
                        }
                    }
                }
            }
            attachedObjects: [
                ComponentDefinition {
                    id: advancedPropertiesDefinition
                    content: Page {
                        onCreationCompleted: {
                            for (var index = 0; index < authTypeDropDownMenu.count(); index ++) {
                                if (authTypeDropDownMenu.at(index).value == authTypeProperty) {
                                    authTypeDropDownMenu.at(index).setSelected(true);
                                }
                            }
                            counterValueTextField.text = counterValueProperty
                            periodTimeTextField.text = periodTimeProperty
                            for (var index = 0; index < algorithmTypeDropDownMenu.count(); index ++) {
                                if (algorithmTypeDropDownMenu.at(index).value == algorithmTypeProperty) {
                                    algorithmTypeDropDownMenu.at(index).setSelected(true);
                                }
                            }
                            for (var index = 0; index < authCodeLenghtDropDownMenu.count(); index ++) {
                                if (authCodeLenghtDropDownMenu.at(index).value == authCodeLenghtProperty) {
                                    authCodeLenghtDropDownMenu.at(index).setSelected(true);
                                }
                            }
                        }
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
                                            id: hotpOption
                                            text: qsTr("Counter based OTP")
                                            description: qsTr("HOTP")
                                            value: 0
                                            selected: true
                                        },
                                        Option {
                                            id: totpOption
                                            text: qsTr("Time based OTP")
                                            description: qsTr("TOTP")
                                            value: 1
                                        }
                                    ]
                                    onCreationCompleted: {
                                        flipVisability(authTypeDropDownMenu.selectedValue);
                                    }
                                    onSelectedOptionChanged: {
                                        authTypeProperty = authTypeDropDownMenu.selectedValue;
                                        flipVisability(authTypeProperty);
                                        
                                    }
                                    function flipVisability(value){
                                        if (value == 0) {
                                            for (var index = 0; index < algorithmTypeDropDownMenu.count(); index ++) {
                                                if (algorithmTypeDropDownMenu.at(index).value == 0) {
                                                    algorithmTypeDropDownMenu.at(index).selected = true
                                                    algorithmTypeDropDownMenu.visible = false;
                                                }
                                            }
                                            periodTimeTextField.visible = false;
                                            counterValueTextField.visible = true;
                                        }
                                        if (value == 1){
                                            algorithmTypeDropDownMenu.visible = true;
                                            periodTimeTextField.visible = true;
                                            counterValueTextField.visible = false;
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
                                    onTextChanged: {
                                        periodTimeProperty = periodTimeTextField.text
                                    }
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
                                    onTextChanged: {
                                        counterValueProperty = counterValueTextField.text
                                    }
                                }
                                DropDown {
                                    id: algorithmTypeDropDownMenu
                                    title: qsTr("Algorithm:")
                                    horizontalAlignment: HorizontalAlignment.Center
                                    options: [
                                        Option {
                                            text: qsTr("SHA-1")
                                            description: qsTr("Secure Hash Algorithm 1")
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
                                            selected: true
                                        }
                                    ]
                                    onSelectedOptionChanged: {
                                        algorithmTypeProperty = algorithmTypeDropDownMenu.selectedValue;
                                    }
                                }
                                DropDown {
                                    id: authCodeLenghtDropDownMenu
                                    title: qsTr("Key Length:")
                                    options: [
                                        Option {
                                            text: "6"
                                            value: 6
                                        },
                                        Option {
                                            text: "7"
                                            value: 7
                                        },
                                        Option {
                                            text: "8"
                                            value: 8
                                            selected: true
                                        },
                                        Option {
                                            text: "9"
                                            value: 9
                                        }
                                    ]
                                    onSelectedOptionChanged: {
                                        authCodeLenghtProperty = authCodeLenghtDropDownMenu.selectedValue;
                                    }
                                }
                            }
                            Divider {}
                        }
                    }                    
                }
            ]
        }
    }
    onCreationCompleted: {
        Qt.app = _app;
    }
}