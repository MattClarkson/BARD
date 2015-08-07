/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardMainRenderingWidget.h"
#include "bardVideoSourceInterface.h"
#include "bardOpenCVVideoSource.h"

#include <vtkRenderWindow.h>
#include <vtkImageData.h>

namespace bard
{

//-----------------------------------------------------------------------------
MainRenderingWidget::MainRenderingWidget()
: m_VideoSource(NULL)
, m_TagProcessor(NULL)
, m_RegistrationAlgorithm(NULL)
, m_Timer(NULL)
, m_ImageImporter(NULL)
, m_ImageActor(NULL)
, m_ImageRenderer(NULL)
, m_VTKRenderer(NULL)
, m_TrackingRenderer(NULL)
, m_CalibratedCamera(NULL)
, m_WorldToCameraTransform(NULL)
{
  m_Timer = new QTimer();
  m_Timer->setInterval(40);
  connect(m_Timer, SIGNAL(timeout()), this, SLOT(OnTimerTriggered()));

  m_ImageImporter = vtkSmartPointer<vtkImageImport>::New();
  m_ImageImporter->SetDataScalarTypeToUnsignedChar();
  m_ImageImporter->SetNumberOfScalarComponents(3);
  m_ImageImporter->SetScalarArrayName("importedImage");

  m_ImageActor = vtkSmartPointer<vtkImageActor>::New();
  m_ImageActor->SetInputData(m_ImageImporter->GetOutput());

  m_ImageRenderer = vtkSmartPointer<vtkRenderer>::New();
  m_ImageRenderer->InteractiveOff();
  this->GetRenderWindow()->AddRenderer(m_ImageRenderer);

  m_VTKRenderer = vtkSmartPointer<vtkRenderer>::New();
  m_VTKRenderer->InteractiveOff();
  this->GetRenderWindow()->AddRenderer(m_VTKRenderer);

  m_TrackingRenderer = vtkSmartPointer<vtkRenderer>::New();
  m_TrackingRenderer->InteractiveOff();
  this->GetRenderWindow()->AddRenderer(m_TrackingRenderer);

  m_CalibratedCamera = vtkSmartPointer<CalibratedCamera>::New();
  m_WorldToCameraTransform = vtkSmartPointer<vtkMatrix4x4>::New();
}


//-----------------------------------------------------------------------------
MainRenderingWidget::~MainRenderingWidget()
{
  if (m_Timer != NULL)
  {
    m_Timer->stop();
    delete m_Timer;
  }
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetCameraIntrinsics(const cv::Matx33d& intrinsics)
{
  m_Intrinsics = intrinsics;
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetVideoSource(bard::VideoSourceInterface* source)
{
  m_VideoSource = source;
  m_ImageImporter->SetImportVoidPointer(const_cast<unsigned char*>(source->ExposeImage()));
  m_ImageImporter->SetWholeExtent(1, source->GetWidth(), 1, source->GetHeight(), 1, 1);
  m_ImageImporter->SetDataExtentToWholeExtent();
  m_ImageImporter->Update();
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetTagProcessor(bard::TagProcessingInterface* processor)
{
  m_TagProcessor = processor;
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetRegistrationAlgorithm(bard::RegistrationInterface* registration)
{
  m_RegistrationAlgorithm = registration;
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetEnableModels(bool isEnabled, vtkRenderer* renderer, std::vector<VTKModelInterface*>& models)
{
  if (isEnabled)
  {
    if (renderer->GetActors()->GetNumberOfItems() == 0)
    {
      for (unsigned int i = 0; i < models.size(); i++)
      {
        renderer->AddActor(models[i]->GetActor());
      }
    }
  }
  else
  {
    if (renderer->GetActors()->GetNumberOfItems() > 0)
    {
      for (unsigned int i = 0; i < models.size(); i++)
      {
        renderer->RemoveActor(models[i]->GetActor());
      }
    }
  }
}


//-----------------------------------------------------------------------------
bool MainRenderingWidget::GetEnableModels(vtkRenderer* renderer) const
{
  if (renderer->GetActors()->GetNumberOfItems() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::AddTrackingModel(bard::TrackingModelInterface* model)
{
  m_TrackingModels.push_back(model);
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetEnableTrackingModels(bool isEnabled)
{
  std::vector<VTKModelInterface*> tmp;
  for (int i = 0; i < m_TrackingModels.size(); i++)
  {
    tmp.push_back(dynamic_cast<VTKModelInterface*>(m_TrackingModels[i]));
  }
  this->SetEnableModels(isEnabled, m_TrackingRenderer, tmp);
}


//-----------------------------------------------------------------------------
bool MainRenderingWidget::GetTrackingModelsAreEnabled() const
{
  return this->GetEnableModels(m_TrackingRenderer);
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::AddVTKModel(bard::VTKModelInterface* model)
{
  m_VTKModels.push_back(model);
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetEnableVTKModels(bool isEnabled)
{
  this->SetEnableModels(isEnabled, m_VTKRenderer, m_VTKModels);
}


//-----------------------------------------------------------------------------
bool MainRenderingWidget::GetVTKModelsAreEnabled() const
{
  return this->GetEnableModels(m_VTKRenderer);
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetEnableImage(bool isEnabled)
{
  if (isEnabled)
  {
    if (m_ImageRenderer->GetActors()->GetNumberOfItems() == 0)
    {
      m_ImageRenderer->AddActor(m_ImageActor);
      m_Timer->start();
    }
  }
  else
  {
    if (m_ImageRenderer->GetActors()->GetNumberOfItems() > 0)
    {
      m_ImageRenderer->RemoveActor(m_ImageActor);
      m_Timer->stop();
    }
  }
}


//-----------------------------------------------------------------------------
bool MainRenderingWidget::GetImageIsEnabled() const
{
  if (m_ImageRenderer->GetActors()->GetNumberOfItems() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetImageCameraToFaceImage()
{
  vtkCamera* camera = m_ImageRenderer->GetActiveCamera();

  int    windowSize[2];
  windowSize[0] = this->GetRenderWindow()->GetSize()[0];
  windowSize[1] = this->GetRenderWindow()->GetSize()[1];

  int    imageSize[3];
  m_ImageImporter->GetOutput()->GetDimensions(imageSize);

  double spacing[3];
  m_ImageImporter->GetOutput()->GetSpacing(spacing);

  double origin[3];
  m_ImageImporter->GetOutput()->GetOrigin(origin);

  double clippingRange[2];
  clippingRange[0] = 1;
  clippingRange[1] = 100000;

  double distanceAlongX = ( spacing[0] * (imageSize[0] - 1) ) / 2.0;
  double vectorAlongX[3] = {1, 0, 0};
  vectorAlongX[0] = distanceAlongX;

  double distanceAlongY = ( spacing[1] * (imageSize[1] - 1) ) / 2.0;
  double vectorAlongY[3] = {0, 1, 0};
  vectorAlongY[1] = distanceAlongY;

  double distanceToFocalPoint = -1000;
  double vectorAlongZ[3] = {0, 0, 1};
  vectorAlongZ[2] = distanceToFocalPoint;

  double viewUpScaleFactor = 1.0e9;
  if ( true )
  {
    viewUpScaleFactor *= -1;
  }

  double focalPoint[3] = {0, 0, 1};
  for ( unsigned int i = 0; i < 3; ++i)
  {
    focalPoint[i] = origin[i] + vectorAlongX[i] + vectorAlongY[i];
  }

  double position[3] = {0, 0, 0};
  position[0] = focalPoint[0] + vectorAlongZ[0];
  position[1] = focalPoint[1] + vectorAlongZ[1];
  position[2] = focalPoint[2] + vectorAlongZ[2];

  double viewUp[3] = {0, 1, 0};
  viewUp[0] = vectorAlongY[0] * viewUpScaleFactor;
  viewUp[1] = vectorAlongY[1] * viewUpScaleFactor;
  viewUp[2] = vectorAlongY[2] * viewUpScaleFactor;

  double imageWidth = imageSize[0]*spacing[0];
  double imageHeight = imageSize[1]*spacing[1];

  double widthRatio = imageWidth / windowSize[0];
  double heightRatio = imageHeight / windowSize[1];

  double scale = 1;
  if (widthRatio > heightRatio)
  {
    scale = 0.5*imageWidth*((double)windowSize[1]/(double)windowSize[0]);
  }
  else
  {
    scale = 0.5*imageHeight;
  }

  camera->SetPosition(position);
  camera->SetFocalPoint(focalPoint);
  camera->SetViewUp(viewUp);
  camera->SetParallelProjection(true);
  camera->SetParallelScale(scale);
  camera->SetClippingRange(clippingRange);
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetImageOpacity(float zeroToOne)
{
  m_ImageActor->SetOpacity(zeroToOne);
}


//-----------------------------------------------------------------------------
float MainRenderingWidget::GetImageOpacity() const
{
  return m_ImageActor->GetOpacity();
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::OnTimerTriggered()
{
  if (m_VideoSource != NULL)
  {
    if(m_VideoSource->GrabImage())
    {
      if (m_TagProcessor != NULL)
      {
        std::vector<TagData> tags = m_TagProcessor->GetTags(*(m_VideoSource->ExposeOpenCVImage()));
/*
        if (tags.size() > 0 &&
            m_TagModel != NULL &&
            m_TagModel->size() > 0 &&
            m_RegistrationAlgorithm != NULL)
        {
          vtkSmartPointer<vtkMatrix4x4> matrix = m_RegistrationAlgorithm->DoRegistration(m_Intrinsics, *m_TagModel, tags);
          this->SetWorldToCameraTransform(*matrix);
        }
*/
      }
      m_ImageImporter->Modified();
      m_ImageImporter->Update(); // this is what pulls a new image in.

      this->SetImageCameraToFaceImage();
      this->GetRenderWindow()->Render();
    }
  }
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetWorldToCameraTransform(const vtkMatrix4x4& matrix)
{
  m_WorldToCameraTransform->DeepCopy(&matrix);

  // aim here is to move the VTK camera of the main render window to match position described by matrix.
}


//-----------------------------------------------------------------------------
vtkSmartPointer<vtkMatrix4x4> MainRenderingWidget::GetWorldToCameraTransform() const
{
  vtkSmartPointer<vtkMatrix4x4> result = vtkSmartPointer<vtkMatrix4x4>::New();
  result->DeepCopy(m_WorldToCameraTransform);
  return result;
}

} // end namespace
