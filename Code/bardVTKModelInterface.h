/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardVTKModelInterface_h
#define bardVTKModelInterface_h

#include <vtkActor.h>
#include <vtkSmartPointer.h>

namespace bard
{

/**
 * \class VTKModelInterface
 * \brief Abstract class describing methods to access a VTK model (source, polydata, mapper, actor etc).
 */
class VTKModelInterface {

public:

  VTKModelInterface();
  virtual ~VTKModelInterface();

  virtual vtkSmartPointer<vtkActor> GetActor() const = 0;
};

} // end namespace

#endif
