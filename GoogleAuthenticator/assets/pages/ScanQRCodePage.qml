import bb.cascades 1.4
import bb.cascades.multimedia 1.2
import bb.multimedia 1.4
import bb.system 1.2
import bb.device 1.4

Page {
    id: scanQRCodePage;
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
        
        Camera {
            id: camera
            
            onCameraOpened: {
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
                        if (cameraVibration.isSupported()){
                            cameraVibration.start(100, 100);
                        }
                        cameraSound.play();
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
                    focusMode: CameraFocusMode.ContinuousAuto
                },
                VibrationController{
                    id: cameraVibration
                }
            ]
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
    }
    
    attachedObjects: [
        SystemToast {
            id: qmlToast
        }
    ]
}

