/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <bardMainRenderingWidget.h>
#include <vtkRenderWindow.h>
#include <bardVideoSourceInterface.h>
#include <bardOpenCVVideoSource.h>

namespace bard
{

//-----------------------------------------------------------------------------
MainRenderingWidget::MainRenderingWidget()
: m_VideoSource(NULL)
, m_ImageImporter(NULL)
, m_ImageActor(NULL)
, m_Renderer(NULL)
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

  m_Renderer = vtkSmartPointer<vtkRenderer>::New();
  m_Renderer->InteractiveOff();

  this->GetRenderWindow()->AddRenderer(m_Renderer);
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
void MainRenderingWidget::SetVideoSource(bard::VideoSourceInterface* source)
{
  m_VideoSource = source;
  this->SetImageArray(source->ExposeImage(), source->GetWidth(), source->GetHeight());
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetImageArray(unsigned char* data, int width, int height)
{
  m_ImageImporter->SetImportVoidPointer(data);
  m_ImageImporter->SetWholeExtent(1, width, 1, height, 1, 1);
  m_ImageImporter->SetDataExtentToWholeExtent();
  m_ImageImporter->Update();
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::SetEnableImage(bool isEnabled)
{
  if (isEnabled)
  {
    if (m_Renderer->GetActors()->GetNumberOfItems() == 0)
    {
      m_Renderer->AddActor(m_ImageActor);
      m_Timer->start();
    }
  }
  else
  {
    if (m_Renderer->GetActors()->GetNumberOfItems() > 0)
    {
      m_Renderer->RemoveActor(m_ImageActor);
      m_Timer->stop();
    }
  }
}


//-----------------------------------------------------------------------------
bool MainRenderingWidget::GetImageIsEnabled() const
{
  if (m_Renderer->GetActors()->GetNumberOfItems() > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


//-----------------------------------------------------------------------------
void MainRenderingWidget::OnTimerTriggered()
{
  if (m_VideoSource != NULL)
  {
    if(m_VideoSource->GrabImage())
    {
      m_ImageImporter->Modified();
      m_ImageImporter->Update();
      this->GetRenderWindow()->Render();
    }
  }
}

} // end namespace
