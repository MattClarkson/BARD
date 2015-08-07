/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardTrackingModelInterface_h
#define bardTrackingModelInterface_h

#include "bardVTKModelInterface.h"
#include "bardModelData.h"

namespace bard
{

/**
 * \class TrackingModelInterface
 * \brief Abstract class describing methods to access a Tracking Model (point IDs, 3D coordinates)
 */
class TrackingModelInterface : public VTKModelInterface {

public:

  TrackingModelInterface();
  virtual ~TrackingModelInterface();

  /**
   * \brief Implementing classes return a pointer to their internal ModelData
   */
  virtual std::vector<ModelData> GetTrackingModel() const = 0;
};

} // end namespace

#endif
