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
#include "bardTrackingModelInterface.h"
#include "bardVTKModelInterface.h"

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
  void SetCalibratedImageSize(const cv::Point2i& imageSize);

  void SetOutputDirectory(const std::string& output);
  void SetRecordMatrix(bool doRecord);
  void SetRecordPointOfInterest(bool doRecord);

  void SetVideoSource(bard::VideoSourceInterface* source);
  void SetTagProcessor(bard::TagProcessingInterface* processor);
  void SetRegistrationAlgorithm(bard::RegistrationInterface* registration);

  void AddTrackingModel(bard::TrackingModelInterface* model);
  void SetEnableTrackingModels(bool isEnabled);
  bool GetTrackingModelsAreEnabled() const;

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
  void SetEnableModels(bool isEnabled, vtkRenderer* renderer, std::vector<VTKModelInterface*>& models);
  bool GetEnableModels(vtkRenderer* renderer) const;
  void UpdateLayers();
  void WriteMatrix(int i, vtkMatrix4x4& matrix);
  void WritePoint(int i, vtkMatrix4x4& matrix, cv::Point3d& point);

  // To store camera intrinsic parameters;
  cv::Matx33d                          m_Intrinsics;
  cv::Point2i                          m_CalibratedImageSize;

  // Here, when I say 'Dependency Injection' I mean:
  // a) Objects are passed in, so this class does NOT own them.
  // b) This means that this class does NOT manage their lifecycle (eg. deletion).

  // Dependency Injection: Video source, OpenCV, from file, etc.
  bard::VideoSourceInterface          *m_VideoSource;

  // Dependency Injection: To extract tags, ArUco, AprilTags, etc.
  bard::TagProcessingInterface        *m_TagProcessor;

  // Dependency Injection: To calculate pose, PnP, PnP with RANSAC, etc.
  bard::RegistrationInterface         *m_RegistrationAlgorithm;

  // Dependency Injection: We store pointers to any number of Tracking models.
  std::vector<TrackingModelInterface*> m_TrackingModels;

  // Dependency Injection: We store pointers to any number of VTK models to render.
  std::vector<VTKModelInterface*>      m_VTKModels;

  // Locally owned objects.
  QTimer                              *m_Timer;
  vtkSmartPointer<CalibratedCamera>    m_TrackingCalibratedCamera;
  vtkSmartPointer<CalibratedCamera>    m_VTKCalibratedCamera;
  vtkSmartPointer<vtkRenderer>         m_BackgroundRenderer;
  vtkSmartPointer<vtkImageImport>      m_ImageImporter;
  vtkSmartPointer<vtkImageActor>       m_ImageActor;
  vtkSmartPointer<vtkRenderer>         m_ImageRenderer;
  vtkSmartPointer<vtkRenderer>         m_VTKRenderer;
  vtkSmartPointer<vtkRenderer>         m_TrackingRenderer;
  vtkSmartPointer<vtkMatrix4x4>        m_WorldToCameraTransform;
  vtkSmartPointer<vtkMatrix4x4>        m_CameraToWorldTransform;
  std::string                          m_OutputDirectory;
  bool                                 m_RecordMatrix;
  bool                                 m_RecordPointOfInterest;
  unsigned long int                    m_FrameCounter;
  std::string                          m_PathSeparator;
};

} // end namespace

#endif

