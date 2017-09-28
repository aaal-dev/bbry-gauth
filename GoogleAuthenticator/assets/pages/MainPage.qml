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

NavigationPane {
    id: navigationPane
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                settingsSheet.open();
            }
        }
        helpAction: HelpActionItem {
        }
    }
    Page {
        id: mainPage

        content: Container {
            layout: DockLayout {

            }

            ListView {
                id: listView

                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill

                //dataModel: GroupDataModel {
                //    id: gAuthListModel
                //    sortingKeys: ["title"]
                //
                //}

                dataModel: XmlDataModel {
                    source: "asset:///model.xml"
                }

                listItemComponents: [
                    ListItemComponent {
                        type: "item"

                        content: Container {
                            preferredHeight: 100.0
                            
                            Divider {}
                            Container {
                                
                                layout: StackLayout {
                                    orientation: LayoutOrientation.LeftToRight
                                }

                                leftPadding: 20.0
                                rightPadding: 20.0
                                Container {
                                    preferredHeight: 100.0
                                    
                                    layout: AbsoluteLayout {

                                    }

                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 4.0
                                    
                                    }
                                    
                                    Label {
                                        text: ListItemData.title
                                        textStyle.fontSize: FontSize.Medium
                                    }
                                    Label {
                                        text: ListItemData.auth_login
                                        textStyle.fontSize: FontSize.XSmall
                                        textStyle.color: Color.LightGray
                                        layoutProperties: AbsoluteLayoutProperties {
                                            positionY: 40.0

                                        }
                                    }
                                
                                }
                                
                                Container {
                                    preferredHeight: 100.0
                                    
                                    layoutProperties: StackLayoutProperties {
                                        spaceQuota: 3.0
                                    
                                    }

                                    Label {
                                        text: ListItemData.auth_code
                                        textStyle.fontSize: FontSize.XLarge
                                        onTouch: {
                                            if (event.isUp()) {
                                                //Qt.app.insertToClipboard(ListItemData.code)
                                            }
                                        }
                                        textFit.mode: LabelTextFitMode.FitToBounds
                                        textStyle.textAlign: TextAlign.Center
                                        horizontalAlignment: HorizontalAlignment.Right
                                    }
                                }
                                
                                contextActions: [
                                    ActionSet {
                                        title: qsTr("Authenticator Code")
                                        subtitle: ListItemData.title
                                        MultiSelectActionItem {
                                        }
                                        DeleteActionItem {
                                            title: qsTr("Delete This Entry")
                                            onTriggered: {
                                                //Qt.dlg.body = qsTr("Are you sure to delete account: %0?").arg(ListItemData.email)
                                                //Qt.dlg.show()
                                            }
                                        }
                                    }
                                ]
                            }
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

            contextActions: [
                ActionSet {
                    title: qsTr("Authenticator Code")
                    subtitle: ListItemData.title
                    MultiSelectActionItem {
                    }
                    DeleteActionItem {
                        title: qsTr("Delete This Entry")
                        onTriggered: {
                            //Qt.dlg.body = qsTr("Are you sure to delete account: %0?").arg(ListItemData.email)
                            //Qt.dlg.show()
                        }
                    }
                }
            ]

        }

        actions: [
            ActionItem {
                id: scanQRCodeButton
                title: qsTr("Scan QR") + Retranslate.onLocaleOrLanguageChanged
                imageSource: "asset:///images/icons/ic_scan_barcode.png"
                ActionBar.placement: ActionBarPlacement.Signature
                shortcuts: Shortcut {
                    key: "S"
                }
                onTriggered: {
                    navigationPane.push(scanQRCodePage.createObject());
                }
                attachedObjects: ComponentDefinition {
                    id: scanQRCodePage
                    source: "ScanQRCodePage.qml"
                }
            },
            
            MultiSelectActionItem {}
        ]

        attachedObjects: [
            Sheet {
                id: settingsSheet
                content: SettingsPage {
                    onDone: {
                        settingsSheet.close();
                    }
                }
            }
        ]
    }
    
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            onTriggered: { navigationPane.pop(); }
        }
    }
    onCreationCompleted: {
        //Application.themeSupport.setVisualStyle(_settings.visualStyle);
    }
}
