/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardPnPRegistration_h
#define bardPnPRegistration_h

#include "bardRegistrationInterface.h"

namespace bard
{

/**
 * \class PnPRegistration
 * \brief Implements 2D/3D registration using OpenCV PnP algorithm.
 */
class PnPRegistration : public RegistrationInterface {

public:

  PnPRegistration();
  virtual ~PnPRegistration();

  /**
  * \brief Takes 3D points and 2D points, and computes a pose matrix.
  */
  virtual vtkSmartPointer<vtkMatrix4x4> DoRegistration(
      const cv::Matx33d& intrinsics,
      const std::vector<ModelData>& model,
      const std::vector<TagData>& tags);
};

} // end namespace

#endif
