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
#include <cv.h>

#include "bardCalibratedCamera.h"
#include "bardTagProcessingInterface.h"
#include "bardRegistrationInterface.h"
#include "bardModelData.h"

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

  void SetCameraIntrinsics(const cv::Matx33d& intrinsics);
  void SetModel(std::vector<ModelData>& model);
  void SetTagProcessor(bard::TagProcessingInterface* processor);
  void SetRegistrationAlgorithm(bard::RegistrationInterface* registration);
  void SetVideoSource(bard::VideoSourceInterface* source);

  void SetEnableImage(bool isEnabled);
  bool GetImageIsEnabled() const;
  void SetImageOpacity(float zeroToOne);
  float GetImageOpacity() const;

  void SetWorldToCameraTransform(const vtkMatrix4x4& matrix);
  vtkSmartPointer<vtkMatrix4x4> GetWorldToCameraTransform() const;

private slots:

  void OnTimerTriggered();

private:

  void SetImageCameraToFaceImage();

  // To trigger updates at a regular (but inaccurate) frequency.
  QTimer                           *m_Timer;

  // To store camera intrinsic parameters;
  cv::Matx33d                       m_Intrinsics;

  // Video source is passed in, so this class does not own in, hence doesn't delete it.
  bard::VideoSourceInterface       *m_VideoSource;

  // For placing an image in the foreground/background.
  vtkSmartPointer<vtkImageImport>   m_ImageImporter;
  vtkSmartPointer<vtkImageActor>    m_ImageActor;
  vtkSmartPointer<vtkRenderer>      m_Renderer;

  // For providing a difference camera to correctly render to calibrated intrinsic params.
  vtkSmartPointer<CalibratedCamera> m_CalibratedCamera;

  // For extracting some tags from the video image
  bard::TagProcessingInterface     *m_TagProcessor;

  // The model that describes the coordinates of the tags in world space.
  std::vector<ModelData>           *m_TagModel;

  // For matching 3D to 2D points to compute a pose of the camera.
  bard::RegistrationInterface      *m_RegistrationAlgorithm;
  vtkSmartPointer<vtkMatrix4x4>     m_WorldToCameraTransform;

};

} // end namespace

#endif

