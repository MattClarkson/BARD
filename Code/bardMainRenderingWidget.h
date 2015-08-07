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
#include "bardVTKModelInterface.h"
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
  void SetVideoSource(bard::VideoSourceInterface* source);
  void SetTagProcessor(bard::TagProcessingInterface* processor);
  void SetRegistrationAlgorithm(bard::RegistrationInterface* registration);
  void SetModel(std::vector<ModelData>& model);

  void AddVTKModel(bard::VTKModelInterface* model);
  void SetEnableVTKModels(bool isEnabled);
  bool GetVTKModelsAreEnabled() const;

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

  // To store camera intrinsic parameters;
  cv::Matx33d                       m_Intrinsics;

  // Video source is passed in, so this class does not own in, hence doesn't delete it.
  bard::VideoSourceInterface       *m_VideoSource;

  // For extracting some tags from the video image
  bard::TagProcessingInterface     *m_TagProcessor;

  // For matching 3D to 2D points to compute a pose of the camera.
  bard::RegistrationInterface      *m_RegistrationAlgorithm;

  // The model that describes the coordinates of the tags in world space.
  std::vector<ModelData>           *m_TagModel;

  // Locally owned objects.
  QTimer                           *m_Timer;
  vtkSmartPointer<vtkImageImport>   m_ImageImporter;
  vtkSmartPointer<vtkImageActor>    m_ImageActor;
  vtkSmartPointer<vtkRenderer>      m_ImageRenderer;
  vtkSmartPointer<vtkRenderer>      m_VTKRenderer;
  vtkSmartPointer<CalibratedCamera> m_CalibratedCamera;
  vtkSmartPointer<vtkMatrix4x4>     m_WorldToCameraTransform;
  std::vector<VTKModelInterface*>   m_VTKModels;

};

} // end namespace

#endif

