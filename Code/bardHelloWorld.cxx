/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <QApplication>
#include <tclap/CmdLine.h>

#include <bardOpenCVVideoSource.h>
#include <bardArucoProcessor.h>
#include <bardPnPRegistration.h>
#include <bardTrackingModelData.h>
#include <bardMainWindow.h>
#include <bardMainRenderingWidget.h>

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo", ' ', "0.1");
    TCLAP::ValueArg<std::string> distortionArg("d","distortion","File containing (1x4) camera distortion coefficients.",false,"","string");
    TCLAP::ValueArg<std::string> intrinsicsArg("i","intrinsics","File containing (3x3) camera intrinsics.",true,"","string");
    TCLAP::ValueArg<std::string> worldRefArg("w","world","File containing (nx4) points of a tracker board defining world coordinates.",true,"","string");
    TCLAP::ValueArg<std::string> pointerRefArg("p","pointer","File containing (nx4) points of a tracker board defining pointer coordinates.",false,"","string");
    TCLAP::ValueArg<float> imageOpacityArg("o","opacity","Image opacity.",false,0.5,"float");
    TCLAP::SwitchArg doDistortionArg("c","correct","Do distortion correction.", false);
    TCLAP::SwitchArg flipSwitchArg("f","flip","Flip in Y-axis.", false);
    cmd.add( distortionArg );
    cmd.add( intrinsicsArg );
    cmd.add( worldRefArg );
    cmd.add( pointerRefArg );
    cmd.add( imageOpacityArg );
    cmd.add( doDistortionArg );
    cmd.add( flipSwitchArg );
    cmd.parse( argc, argv );
    std::string distortionFile = distortionArg.getValue();
    std::string intrinsicsFile = intrinsicsArg.getValue();
    std::string worldRef = worldRefArg.getValue();
    std::string pointerRef = pointerRefArg.getValue();
    float opacity = imageOpacityArg.getValue();
    bool doDistortionCorrection = doDistortionArg.getValue();
    bool doFlipY = flipSwitchArg.getValue();

    QApplication app(argc, argv);
    app.setOrganizationName("CMIC");
    app.setApplicationName("BARD");

    bard::OpenCVVideoSource mySource("");
    mySource.SetFlipY(doFlipY);
    mySource.SetUndistort(doDistortionCorrection);

    bard::ArucoProcessor myProcessor;
    bard::PnPRegistration myRegistration;
    bard::TrackingModelData myWorldTrackingModel(worldRef);

    bard::MainRenderingWidget myWidget;
    myWidget.SetVideoSource(&mySource);
    myWidget.SetTagProcessor(&myProcessor);
    myWidget.SetRegistrationAlgorithm(&myRegistration);
    myWidget.SetImageOpacity(opacity);

    myWidget.AddTrackingModel(&myWorldTrackingModel);
    bard::TrackingModelData* pointerTrackingModel = NULL;
    if (pointerRef.size() > 0)
    {
      pointerTrackingModel = new bard::TrackingModelData(pointerRef);
      myWidget.AddTrackingModel(pointerTrackingModel);
    }

    bard::MainWindow mainWin;
    mainWin.SetMainRenderingWidget(&myWidget);
    mainWin.show();

    myWidget.SetEnableImage(true);
    myWidget.SetEnableTrackingModels(true);

    int status = app.exec();

    // Tidy up.
    if (pointerTrackingModel != NULL)
    {
      delete pointerTrackingModel;
    }
    return status;
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
}
