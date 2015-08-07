/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardVTKModelPipeline.h"
#include <stdexcept>

namespace bard
{

//-----------------------------------------------------------------------------
VTKModelPipeline::VTKModelPipeline(const std::string& fileName)
{
  if (fileName.size() == 0)
  {
    throw std::runtime_error("Empty filename supplied for VTK model data");
  }

  m_PolyDataReader = vtkSmartPointer<vtkPolyDataReader>::New();
  m_PolyDataReader->SetFileName(fileName.c_str());
  m_PolyDataReader->Update();

  m_Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  m_Mapper->SetInputConnection(m_PolyDataReader->GetOutputPort());

  m_Actor = vtkSmartPointer<vtkActor> ::New();
  m_Actor->SetMapper(m_Mapper);
}


//-----------------------------------------------------------------------------
VTKModelPipeline::~VTKModelPipeline()
{
}


//-----------------------------------------------------------------------------
vtkSmartPointer<vtkActor> VTKModelPipeline::GetActor() const
{
  return m_Actor;
}

} // end namespace
