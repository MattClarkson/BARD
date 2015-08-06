/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardArucoProcessor.h"

namespace bard
{

//-----------------------------------------------------------------------------
ArucoProcessor::ArucoProcessor()
{

}


//-----------------------------------------------------------------------------
ArucoProcessor::~ArucoProcessor()
{

}


//-----------------------------------------------------------------------------
std::vector<TagData> ArucoProcessor::GetTags(const cv::Mat& image) const
{
  std::vector<TagData> results;
  return results;
}

} // end namespace
