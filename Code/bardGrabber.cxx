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
    TCLAP::ValueArg<std::string> outputArg("o","output","Filename to write an image to.",true,"","string");
    cmd.add( outputArg );
    cmd.parse( argc, argv );
    std::string outputFile = outputArg.getValue();

    QApplication app(argc, argv);
    app.setOrganizationName("CMIC");
    app.setApplicationName("BARD");

    bard::MainWindow mainWin;

    bard::OpenCVVideoSource mySource("");

    bard::MainRenderingWidget myWidget;
    myWidget.SetVideoSource(&mySource);
    myWidget.SetDumpImageFileName(outputFile);

    mainWin.setCentralWidget(&myWidget);
    mainWin.setFixedSize(mySource.GetWidth(), mySource.GetHeight());
    mainWin.show();
    mainWin.raise();

    myWidget.GetInteractor()->Disable();
    myWidget.SetEnableImage(true);

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
