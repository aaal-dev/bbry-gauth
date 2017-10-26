import bb.cascades 1.4
import bb.cascades.multimedia 1.2
import bb.multimedia 1.4
import bb.system 1.2
import bb.device 1.4


Page {
    id: scanQRCodePage
    
    signal done()

    function getCameraUnit(camUnitList) {
        if (camUnitList.length == 0 || camUnitList[0] == CameraUnit.None) {
            qmlToast.body = "No camera units are available";
            qmlToast.show();
            
            return null;
        }
        
        for (var i = 0; i < camUnitList.length; ++ i) {
            if (camUnitList[i] == CameraUnit.Rear)
                return camUnitList[i];
        }
        
        for (var j = 0; j < camUnitList.length; ++ j) {
            if (camUnitList[i] == CameraUnit.Front)
                return camUnitList[i];
        }    
    }
    
    titleBar: TitleBar {
        title: qsTr("Scan QR Code") + Retranslate.onLocaleOrLanguageChanged
        kind: TitleBarKind.Default
    }
    
    content: Container {
        background: Color.Black
        Container {
            topPadding: ui.du(1)
            bottomPadding: topPadding
            leftPadding: ui.du(2)
            rightPadding: leftPadding
            Label {
                text: qsTr("Move device until you get QR code on your visual site, then stand still until decoding")
                textStyle.color: Color.White
                multiline: true
            }
        }

        Camera {
            id: camera
            
            onCameraOpened: {
                getSettings(cameraSettings)
                applySettings(cameraSettings);
                camera.startViewfinder();
            }
            onViewfinderStopped: {
                camera.close()
            }
            
            attachedObjects: [
                BarcodeDetector {
                    id: barcodeDetector
                    camera: camera
                    formats: BarcodeFormat.QrCode
                    onDetected: {
                        camera.stopViewfinder();
                        if (cameraVibration.isSupported()){
                            cameraVibration.start(100, 100);
                        }
                        cameraSound.play();
                        scanQRCodePage.done();
                        _app.parseQRData(data);
                    }
                },
                SystemSound {
                    id: cameraSound
                    sound: SystemSound.GeneralNotification
                },
                CameraSettings {
                    id: cameraSettings
                    shootingMode: CameraShootingMode.Stabilization
                    cameraMode: CameraMode.Photo
                    sceneMode: CameraSceneMode.Auto
                    flashMode: CameraFlashMode.Light
                    focusMode: CameraFocusMode.ContinuousMacro
                },
                VibrationController{
                    id: cameraVibration
                }
            ]
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
        }
        
        onCreationCompleted: {
            var cameraUnit = getCameraUnit(camera.supportedCameras);
            
            if (cameraUnit != null) {
                if (camera.isCameraAccessible(cameraUnit)) {
                    camera.open(cameraUnit);
                }
            }
            
            camera.open()
        }
    }
    
    onDone: {
        barcodeDetector.camera = null
        camera.stopViewfinder()
        navigationPane.pop()
    }
 
    attachedObjects: [
        SystemToast {
            id: qmlToast
        }
    ]
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            onTriggered: {
                scanQRCodePage.done()
            }
        }
    }
}

