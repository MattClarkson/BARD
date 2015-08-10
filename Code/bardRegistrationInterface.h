/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardRegistrationInterface_h
#define bardRegistrationInterface_h

#include "bardTagData.h"
#include "bardModelData.h"

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <cv.h>

namespace bard
{

/**
 * \class RegistrationInterface
 * \brief Abstract class for any type of 3D/2D registration algorithm.
 */
class RegistrationInterface {

public:

  RegistrationInterface();
  virtual ~RegistrationInterface();

  /**
  * \brief Takes 3D points and 2D points, and computes a pose matrix.
  */
  virtual vtkSmartPointer<vtkMatrix4x4> DoRegistration(
      const cv::Matx33d& intrinsics,
      const std::vector<ModelData>& model,
      const std::vector<TagData>& tags) = 0;
};

} // end namespace

#endif
