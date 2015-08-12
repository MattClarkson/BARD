/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardOpenCVVideoSource.h"
#include "bardMainWindow.h"
#include "bardMainRenderingWidget.h"

#include <QApplication>
#include <tclap/CmdLine.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Frame Grabber", ' ', "0.1");
    TCLAP::ValueArg<std::string> outputDirArg("d", "directory", "Output directory to dump files.", false, "", "string");
    cmd.add( outputDirArg );
    cmd.parse( argc, argv );
    std::string outputDir = outputDirArg.getValue();

    QApplication app(argc, argv);
    app.setOrganizationName("CMIC");
    app.setApplicationName("BARD");

    bard::MainWindow mainWin;

    bard::OpenCVVideoSource mySource("");

    bard::MainRenderingWidget myWidget;
    myWidget.SetVideoSource(&mySource);

    mainWin.setCentralWidget(&myWidget);
    mainWin.setFixedSize(mySource.GetWidth(), mySource.GetHeight());
    mainWin.show();
    mainWin.raise();

    myWidget.GetInteractor()->Disable();
    myWidget.SetEnableImage(true);
    myWidget.SetOutputDirectory(outputDir);

    int status = app.exec();
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
