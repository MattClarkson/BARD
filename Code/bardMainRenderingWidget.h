/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardMainRenderingWidget_h
#define bardMainRenderingWidget_h

#include <QVTKWidget.h>
#include <QTimer>
#include <vtkSmartPointer.h>
#include <vtkImageImport.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>

namespace bard
{

class VideoSourceInterface;

class MainRenderingWidget : public QVTKWidget {

  Q_OBJECT

public:
  MainRenderingWidget();
  ~MainRenderingWidget();

  void SetVideoSource(bard::VideoSourceInterface* source);
  void SetEnableImage(bool isEnabled);
  bool GetImageIsEnabled() const;

private slots:

  void OnTimerTriggered();

private:

  QTimer                         *m_Timer;

  void SetImageArray(unsigned char* data, int width, int height);
  bard::VideoSourceInterface     *m_VideoSource;

  // For placing an image in the foreground/background.
  vtkSmartPointer<vtkImageImport> m_ImageImporter;
  vtkSmartPointer<vtkImageActor>  m_ImageActor;
  vtkSmartPointer<vtkRenderer>    m_Renderer;
};

} // end namespace

#endif

