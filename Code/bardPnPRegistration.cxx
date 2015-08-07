/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardPnPRegistration.h"

namespace bard
{

//-----------------------------------------------------------------------------
PnPRegistration::PnPRegistration()
{
}


//-----------------------------------------------------------------------------
PnPRegistration::~PnPRegistration()
{
}


//-----------------------------------------------------------------------------
vtkSmartPointer<vtkMatrix4x4> PnPRegistration::DoRegistration(
      const cv::Matx33d& intrinsics,
      const std::vector<ModelData>& model,
      const std::vector<TagData>& tags)
{
  vtkSmartPointer<vtkMatrix4x4> pose = vtkSmartPointer<vtkMatrix4x4>::New();
  pose->Identity();
  return pose;
}

} // end namespace
