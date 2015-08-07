/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardTrackingModelData_h
#define bardTrackingModelData_h

#include "bardTrackingModelInterface.h"
#include "bardModelData.h"
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

namespace bard
{

/**
 * \class TrackingModelData
 * \brief Class to hold ModelData and a VTK pipeline to represent it.
 */
class TrackingModelData : public TrackingModelInterface {

public:
  TrackingModelData();
  TrackingModelData(const std::string& fileName);
  virtual ~TrackingModelData();

  /** \see TrackingModelInterface::GetTrackingModel() */
  virtual std::vector<ModelData> GetTrackingModel() const;

  /** \see VTKModelInterface::GetActor() */
  virtual vtkSmartPointer<vtkActor> GetActor() const;

private:
  std::vector<ModelData>             m_ModelPoints;
  vtkSmartPointer<vtkPoints>         m_Points;
  vtkSmartPointer<vtkPolyData>       m_PolyData;
  vtkSmartPointer<vtkSphereSource>   m_SphereSource;
  vtkSmartPointer<vtkGlyph3D>        m_Glyph3D;
  vtkSmartPointer<vtkPolyDataMapper> m_Mapper;
  vtkSmartPointer<vtkActor>          m_Actor;
};

} // end namespace

#endif
