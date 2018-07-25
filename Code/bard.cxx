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
#include <cv.h>
#include <iostream>

#include "bardOpenCVVideoSource.h"
#include "bardArucoProcessor.h"
#include "bardPnPRegistration.h"
#include "bardTrackingModelData.h"
#include "bardMainWindow.h"
#include "bardMainRenderingWidget.h"
#include "bardVTKModelPipeline.h"
#include "bardFileIO.h"

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo", ' ', "0.1");
    TCLAP::ValueArg<std::string> intrinsicsArg("i","intrinsics","File containing (3x3) camera intrinsics then (1x4) distortion coefficients.",false,"","string");
    TCLAP::ValueArg<std::string> worldRefArg("w","world","File containing (nx4) points of a tracker board defining world coordinates.",true,"","string");
    TCLAP::ValueArg<std::string> pointerRefArg("p","pointer","File containing (nx4) points of a tracker board defining pointer coordinates.",false,"","string");
    TCLAP::ValueArg<std::string> modelArg0("m","model0","vtkPolyData file a model to be rendered in the scene.",false,"","string");
    TCLAP::ValueArg<std::string> modelArg1("n", "model1", "vtkPolyData file a model to be rendered in the scene.", false, "", "string");
    TCLAP::ValueArg<std::string> outputDirArg("d", "directory", "Output directory to dump files.", false, "", "string");
    TCLAP::ValueArg<std::string> modelAlignArg("a", "align", "File containing (4x4) transform, to align models to world.", false, "", "string");
    TCLAP::ValueArg<float> imageOpacityArg("o","opacity","Image opacity.",false,0.5,"float");
    TCLAP::ValueArg<int> imageXSizeArg("x","xsize","xsize when calibrating.",true,1,"int");
    TCLAP::ValueArg<int> imageYSizeArg("y","ysize","ysize when calibrating.",true,1,"int");
    TCLAP::ValueArg<int> openCVSourceIndex("k", "index", "Camera Index to use", false, 0, "int");
    TCLAP::SwitchArg doDistortionArg("c","correct","Do distortion correction.", false);
    TCLAP::SwitchArg flipSwitchArg("f","flip","Flip in Y-axis.", false);
    TCLAP::SwitchArg pointerRecordMatrixArg("r","record","Record pointer matrix (e.g. for pivot calib).", false);
    TCLAP::SwitchArg pointerRecordTipArg("t","tip","Record pointer tip (e.g. for registration).", false);
    cmd.add( intrinsicsArg );
    cmd.add( worldRefArg );
    cmd.add( pointerRefArg );
    cmd.add( modelArg0 );
    cmd.add( modelArg1 );
    cmd.add( outputDirArg );
    cmd.add( modelAlignArg );
    cmd.add( imageOpacityArg );
    cmd.add( imageXSizeArg );
    cmd.add( imageYSizeArg );
    cmd.add( openCVSourceIndex );
    cmd.add( doDistortionArg );
    cmd.add( flipSwitchArg );
    cmd.add( pointerRecordMatrixArg );
    cmd.add( pointerRecordTipArg );
    cmd.parse( argc, argv );
    std::string intrinsicsFile = intrinsicsArg.getValue();
    std::string worldRef = worldRefArg.getValue();
    std::string pointerRef = pointerRefArg.getValue();
    std::string modelFile0 = modelArg0.getValue();
    std::string modelFile1 = modelArg1.getValue();
    std::string outputDir = outputDirArg.getValue();
    std::string modelAlignFile = modelAlignArg.getValue();
    float opacity = imageOpacityArg.getValue();
    int xSize = imageXSizeArg.getValue();
    int ySize = imageYSizeArg.getValue();
    int sourceIndex = openCVSourceIndex.getValue();
    bool doDistortionCorrection = doDistortionArg.getValue();
    bool doFlipY = flipSwitchArg.getValue();
    bool pointerRecordMatrix = pointerRecordMatrixArg.getValue();
    bool pointerRecordTip =pointerRecordTipArg.getValue();

    if ((pointerRecordMatrix || pointerRecordTip) && pointerRef.size() == 0)
    {
      throw std::runtime_error("You asked to record pointer movement, but did not provide a pointer reference model.");
    }
    if ((pointerRecordMatrix || pointerRecordTip) && outputDir.size() == 0)
    {
      throw std::runtime_error("You asked to record pointer movement, but did not provide an output directory.");
    }

    QApplication app(argc, argv);
    app.setOrganizationName("CMIC");
    app.setApplicationName("BARD");

    bard::MainWindow mainWin;

    cv::Point2i imageSize;
    imageSize.x = xSize;
    imageSize.y = ySize;

    bard::OpenCVVideoSource mySource(sourceIndex);
    mySource.SetFlipY(doFlipY);
    mySource.SetUndistort(doDistortionCorrection);

    bard::ArucoProcessor myProcessor;
    bard::PnPRegistration myRegistration;
    bard::TrackingModelData myWorldTrackingModel(worldRef);

    bard::MainRenderingWidget myWidget;
    myWidget.SetCalibratedImageSize(imageSize);
    myWidget.SetVideoSource(&mySource);
    myWidget.SetTagProcessor(&myProcessor);
    myWidget.SetRegistrationAlgorithm(&myRegistration);
    myWidget.SetImageOpacity(opacity);
    myWidget.SetOutputDirectory(outputDir);
    myWidget.SetRecordMatrix(pointerRecordMatrix);
    myWidget.SetRecordPointOfInterest(pointerRecordTip);

    // Load intrinsic/distortion parameters
    cv::Matx33d intrinsicParameters;
    cv::Matx14d distortionParameters;
    if (intrinsicsFile.size() > 0)
    {
      bard::LoadCameraParameters(intrinsicsFile, intrinsicParameters, distortionParameters);
      myWidget.SetCameraIntrinsics(intrinsicParameters);
    }

    // Loads 4x4 registration matrix.
    cv::Matx44d registerModelsToWorld;
    if (modelAlignFile.size() > 0)
    {
      registerModelsToWorld = bard::LoadMatrixFromFile(modelAlignFile);
      myWidget.SetModelsToWorld(registerModelsToWorld);
    }

    // Adds data-files that enable us to do tag tracking of various objects.
    myWidget.AddTrackingModel(&myWorldTrackingModel);
    bard::TrackingModelData* pointerTrackingModel = NULL;
    if (pointerRef.size() > 0)
    {
      pointerTrackingModel = new bard::TrackingModelData(pointerRef);
      myWidget.AddTrackingModel(pointerTrackingModel);
    }

    // Add VTK files that enable us to visualise virtual objects in scene.
    bard::VTKModelPipeline *modelForVisualisation0 = NULL;
    if (modelFile0.size() > 0)
    {
      modelForVisualisation0 = new bard::VTKModelPipeline(modelFile0);
      myWidget.AddVTKModel(modelForVisualisation0);
    }
    bard::VTKModelPipeline *modelForVisualisation1 = NULL;
    if (modelFile1.size() > 0)
    {
      modelForVisualisation1 = new bard::VTKModelPipeline(modelFile1);
      myWidget.AddVTKModel(modelForVisualisation1);
    }
    mainWin.setCentralWidget(&myWidget);
    mainWin.show();
    mainWin.raise();
    mainWin.showMaximized();


    myWidget.GetInteractor()->Disable();
    myWidget.SetEnableImage(true);
    myWidget.SetEnableTrackingModels(true);
    myWidget.SetEnableVTKModels(true);

    int status = app.exec();

    // Tidy up.
    if (pointerTrackingModel != NULL)
    {
      delete pointerTrackingModel;
    }
    if (modelForVisualisation0 != NULL)
    {
      delete modelForVisualisation0;
    }
    if (modelForVisualisation1 != NULL)
    {
      delete modelForVisualisation1;
    }
    return status;
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
}
