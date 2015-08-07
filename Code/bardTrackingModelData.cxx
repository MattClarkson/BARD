/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardTrackingModelData.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vtkProperty.h>

namespace bard
{

//-----------------------------------------------------------------------------
TrackingModelData::TrackingModelData(const std::string& fileName)
{
  if (fileName.size() == 0)
  {
    throw std::runtime_error("Empty filename supplied for tracking model data");
  }
  std::ifstream ifs(fileName.c_str());
  if (!ifs.is_open())
  {
    std::stringstream oss;
    oss << "Failed to open file:" << fileName << std::endl;
    throw std::runtime_error(oss.str());
  }
  // basically read in a bunch of points: int float float float
  int pointId;
  cv::Point3d point;
  while (!ifs.eof())
  {
    ifs >> pointId;
    ifs >> point.x;
    ifs >> point.y;
    ifs >> point.z;
    if (ifs.good())
    {
      ModelData modelPoint(pointId, point);
      m_ModelPoints.push_back(modelPoint);
    }
  }

  m_Points = vtkSmartPointer<vtkPoints>::New();
  m_Points->SetNumberOfPoints(m_ModelPoints.size());
  for (unsigned int i = 0; i < m_ModelPoints.size(); i++)
  {
    cv::Point3d p = m_ModelPoints[i].GetPoint();
    m_Points->SetPoint(i, p.x, p.y, p.z);
  }

  m_PolyData = vtkSmartPointer<vtkPolyData>::New();
  m_PolyData->SetPoints(m_Points);

  m_SphereSource = vtkSmartPointer<vtkSphereSource>::New();
  m_SphereSource->SetRadius(0.5);

  m_Glyph3D = vtkSmartPointer<vtkGlyph3D>::New();
  m_Glyph3D->SetInputData(m_PolyData);
  m_Glyph3D->SetSourceConnection(m_SphereSource->GetOutputPort());

  m_Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  m_Mapper->SetInputConnection(m_Glyph3D->GetOutputPort());

  m_Actor = vtkSmartPointer<vtkActor> ::New();
  m_Actor->SetMapper(m_Mapper);
  m_Actor->GetProperty()->SetColor(1, 0, 0);
}


//-----------------------------------------------------------------------------
TrackingModelData::TrackingModelData()
{

}


//-----------------------------------------------------------------------------
TrackingModelData::~TrackingModelData()
{

}


//-----------------------------------------------------------------------------
std::vector<ModelData> TrackingModelData::GetTrackingModel() const
{
  // Takes a copy.
  return m_ModelPoints;
}


//-----------------------------------------------------------------------------
vtkSmartPointer<vtkActor> TrackingModelData::GetActor() const
{
  return m_Actor;
}

} // end namespace
