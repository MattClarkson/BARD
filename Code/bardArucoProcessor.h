/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardArucoProcessor_h
#define bardArucoProcessor_h

#include "bardTagData.h"
#include "bardTagProcessingInterface.h"

namespace bard
{

/**
 * \class ArucoProcessor
 * \brief Extracts Aruco Tags from an OpenCV image.
 */
class ArucoProcessor : public TagProcessingInterface {

public:

  ArucoProcessor();
  virtual ~ArucoProcessor();

  void SetMinSize(float minSize);
  float GetMinSize() const;

  void SetMaxSize(float minSize);
  float GetMaxSize() const;

  void SetBlockSize(int blockSize);
  int GetBlockSize() const;

  void SetOffset(int offset);
  int GetOffset() const;

  /**
  * \see TagProcessingInterface::GetTags()
  */
  virtual std::vector<TagData> GetTags(const cv::Mat& image) const;

private:

  float m_MinSize;
  float m_MaxSize;
  int m_BlockSize;
  int m_Offset;
};

} // end namespace

#endif
