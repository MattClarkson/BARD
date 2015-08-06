/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardTagProcessingInterface_h
#define bardTagProcessingInterface_h

#include <bardTagData.h>

namespace bard
{

/**
 * \class TagProcessingInterface
 * \brief Abstract class for any type of Tag processor.
 */
class TagProcessingInterface {

public:

  TagProcessingInterface();
  virtual ~TagProcessingInterface();

  /**
  * \brief Reads the supplied video image, and extract tag ID and position information.
  */
  virtual std::vector<TagData> GetTags(const cv::Mat& image) const = 0;
};

} // end namespace

#endif
