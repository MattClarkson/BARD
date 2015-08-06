/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <QApplication>

#include <bardOpenCVVideoSource.h>
#include <bardMainWindow.h>
#include <bardMainRenderingWidget.h>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  app.setOrganizationName("CMIC");
  app.setApplicationName("BARD");

  bard::OpenCVVideoSource mySource("");

  bard::MainRenderingWidget myWidget;
  myWidget.SetVideoSource(&mySource);

  bard::MainWindow mainWin;
  mainWin.SetMainRenderingWidget(&myWidget);
  mainWin.show();

  myWidget.SetEnableImage(true);

  return app.exec();
}
