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
#include "bardCalibratedCamera.h"

namespace bard
{

class VideoSourceInterface;

/**
 * \class MainRenderingWidget
 * \brief Qt widget to hold a VTK rendered scene.
 */
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

  void SetImageArray(unsigned char* data, int width, int height);
  void SetImageCameraToFaceImage();

  QTimer                           *m_Timer;


  bard::VideoSourceInterface       *m_VideoSource;

  // For placing an image in the foreground/background.
  vtkSmartPointer<vtkImageImport>   m_ImageImporter;
  vtkSmartPointer<vtkImageActor>    m_ImageActor;
  vtkSmartPointer<vtkRenderer>      m_Renderer;

  // For providing a difference camera to correctly render to calibrated intrinsic params.
  vtkSmartPointer<CalibratedCamera> m_CalibratedCamera;
};

} // end namespace

#endif

