/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.4
import bb.system 1.2

NavigationPane {
    id: navigationPane
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                navigationPane.push(settingsPageDefinition.createObject());
            }
        }
        helpAction: HelpActionItem {
            title: qsTr("Information") + Retranslate.onLocaleOrLanguageChanged
            imageSource: "asset:///images/icons/ic_info.png"
            onTriggered: {
                navigationPane.push(informationPageDefinition.createObject());
            }
        }
        actions: [
            ActionItem {
                id: shareMenuItem
                title: qsTr("Share") + Retranslate.onLocaleOrLanguageChanged
                imageSource: "asset:///images/icons/ic_share.png"
                onTriggered: {
                    
                }
            }
        ]
    }
    Page {
        id: mainPage
        content: Container {
            layout: DockLayout {
            }
            ListView {
                id: accountListView
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill
                dataModel: app.dataModel
                //dataModel: XmlDataModel { source: "asset:///model.xml" }
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        content: Container {
                            id: listItem
                            Container {
                                Container {
                                    Container {
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 1.0

                                        }
                                        verticalAlignment: VerticalAlignment.Center
                                        Container {
                                            Label {
                                                text: ListItemData.issuerTitle
                                                textStyle.fontSize: FontSize.Medium
                                            }
                                        }
                                        Container {
                                            Label {
                                                text: ListItemData.accountName
                                                textStyle.fontSize: FontSize.XSmall
                                                textStyle.color: Color.DarkGray
                                                textStyle.fontWeight: FontWeight.W300
                                            }
                                        }
                                    }
                                    Container {
                                        preferredWidth: ui.du(32)
                                        verticalAlignment: VerticalAlignment.Center
                                        layout: StackLayout {

                                        }
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: -1.0

                                        }
                                        horizontalAlignment: HorizontalAlignment.Right
                                        Label {
                                            text: ListItemData.authCode
                                            horizontalAlignment: HorizontalAlignment.Right
                                            textStyle.fontSize: FontSize.XLarge

                                        }
                                        ProgressIndicator {
                                            verticalAlignment: VerticalAlignment.Bottom
                                            fromValue: 0
                                            toValue: ListItemData.periodTime * 10
                                            value: ListItemData.elapsedTime
                                        }
                                        gestureHandlers: [
                                            TapHandler {
                                                onTapped: {
                                                    onInfo("Copy code")
                                                }
                                            }
                                        ]
                                    }
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    leftPadding: ui.du(2)
                                    rightPadding: leftPadding
                                    topPadding: ui.du(1.6)
                                }
                                Container {
                                    topPadding: ui.du(2)
                                    
                                    Divider{
                                        
                                    }
                                }
                            }
                            contextActions: [
                                ActionSet {
                                    title: qsTr("Authenticator Code")
                                    subtitle: ListItemData.issuerTitle + ListItemData.accountName
                                    actions: [
                                        ActionItem {
                                            title: qsTr("Edit data")
                                        },
                                        ActionItem {
                                            title: qsTr("Copy code")
                                        }
                                    ]
                                    MultiSelectActionItem {
                                    }
                                    DeleteActionItem {
                                        title: qsTr("Delete This Entry")
                                        onTriggered: {
                                            Qt.app.deleteAccount(listItem.ListItem.view.selected());
                                            
                                        }
                                    }
                                }
                            ]
                        }
                        
                    }
                ]
                property variant activeItem: undefined
                onActivationChanged: {
                    if (active) activeItem = indexPath; //[0]
                }
                snapMode: SnapMode.LeadingEdge
            }
            ProgressIndicator {
                verticalAlignment: VerticalAlignment.Bottom
            }
        }
        actions: [
            ActionItem {
                id: scanQRCodeButton
                title: qsTr("Scan QR Code") + Retranslate.onLocaleOrLanguageChanged
                imageSource: "asset:///images/icons/ic_scan_barcode.png"
                ActionBar.placement: ActionBarPlacement.Signature
                shortcuts: Shortcut {
                    key: "S"
                }
                onTriggered: {
                    navigationPane.push(scanQRCodePageDef.createObject());
                }
            },
            ActionItem {
                id: addCodeButton
                title: qsTr("Add manualy") + Retranslate.onLocaleOrLanguageChanged
                imageSource: "asset:///images/icons/ic_add_code.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                shortcuts: Shortcut {
                    key: "A"
                }
                onTriggered: {
                    addCodeSheet.open();
                }
            },
            MultiSelectActionItem {}
        ]
    }
    attachedObjects: [
        ComponentDefinition {
            id: settingsPageDefinition
            source: "SettingsPage.qml"
        },
        ComponentDefinition {
            id: informationPageDefinition
            source: "InformationPage.qml"
        },
        ComponentDefinition {
            id: scanQRCodePageDef
            source: "ScanQRCodePage.qml"
        },
        Sheet {
            id: addCodeSheet
            peekEnabled: false
            AddCodePage {
                onDone: {
                    addCodeSheet.close()
                }
            }
        },
        SystemToast {
            id: mainPageToast
            button.label: qsTr("Close")
        }
    ]
    
    // Самописные функции
    function onError(errorString)
    {
        mainPageToast.body = errorString;
        mainPageToast.show();
    }
    
    function onInfo(infoString)
    {
        mainPageToast.body = infoString;
        mainPageToast.show();
    }
    
    // Функции слоты
    onPushTransitionEnded: {
        if (count() > 1) {
            Application.menuEnabled = false;
        }
    }
    onPopTransitionEnded: {
        page.destroy();
        if (count() == 1)
            Application.menuEnabled = true;
    }
    onCreationCompleted: {
        Qt.app = app;
    }
}