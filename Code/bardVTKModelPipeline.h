/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardVTKModelPipeline_h
#define bardVTKModelPipeline_h

#include "bardVTKModelInterface.h"

#include <vtkActor.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

namespace bard
{

/**
 * \class VTKModelPipeline
 * \brief Class to contain a basic pipeline to render vtkPolyData.
 */
class VTKModelPipeline : public VTKModelInterface {

public:

  VTKModelPipeline(const std::string& fileName);
  virtual ~VTKModelPipeline();

  /** \see VTKModelInterface::GetActor() */
  virtual vtkSmartPointer<vtkActor> GetActor() const;

private:
  vtkSmartPointer<vtkPolyDataReader> m_PolyDataReader;
  vtkSmartPointer<vtkPolyDataMapper> m_Mapper;
  vtkSmartPointer<vtkActor>          m_Actor;
};

} // end namespace

#endif
