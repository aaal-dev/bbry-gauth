import bb.cascades 1.4

Page {
    titleBar: TitleBar {
        title: qsTr("Information") + Retranslate.onLocaleOrLanguageChanged
    }
    
    ScrollView {
        Container {
            Container {
                topPadding: ui.du(2)
                rightPadding: topPadding
                leftPadding: topPadding
                bottomPadding: topPadding
                
                Label {
                    multiline: true
                    text: qsTr("<html>Welcome to Rundgång! This manual contain some information" + 
                    "on how to use this application. First up the name, Rundgång is swedish for" +
                    " feedback. Well actually the word refers to the kind of feedback one gets" +
                    " when the sound guy is not doing his job properly.\n</html>")
                }
                
                Label {
                    multiline: true
                    text: qsTr("<html><span style='font-size:x-large'>Feedback</span> \n" + 
                    "On the start screen you have three different actions, these are different" +
                    " ways of record data that you want to feedback to a group of people.\n</html>")
                }
                
                Label {
                    
                    multiline: true
                    text: qsTr("<html><span style='font-size:x-large'>People &amp; Topic</span> \n" + 
                    "The group of people and the topic of the feedback that are currently selected is" + 
                    " presented on the home screen and a list of different topics is available either pressing the item" + 
                    " or going action item overflow." + "\n\nHappy feedbacking.</html>")
                }
            }
            
            Divider {
            }
            Container {
                topPadding: ui.du(2)
                rightPadding: topPadding
                leftPadding: topPadding
                bottomPadding: topPadding
                
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                background: Color.LightGray
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
                    text: qsTr("Lisence")
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                }
                ImageView {
                    imageSource: "asset:///images/icons/ic_next.png"
                    preferredHeight: 32.0
                    preferredWidth: 32.0
                }
            }
        }
    }
}

