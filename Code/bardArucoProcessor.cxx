/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardArucoProcessor.h"
#include "bardTagData.h"

#include <aruco/aruco.h>

namespace bard
{

//-----------------------------------------------------------------------------
ArucoProcessor::ArucoProcessor()
: m_MinSize(0.005)
, m_MaxSize(0.125)
, m_BlockSize(20)
, m_Offset(10)
{
}


//-----------------------------------------------------------------------------
ArucoProcessor::~ArucoProcessor()
{
}


//-----------------------------------------------------------------------------
void ArucoProcessor::SetMinSize(float minSize)
{
  m_MinSize = minSize;
}


//-----------------------------------------------------------------------------
float ArucoProcessor::GetMinSize() const
{
  return m_MinSize;
}


//-----------------------------------------------------------------------------
void ArucoProcessor::SetMaxSize(float maxSize)
{
  m_MaxSize = maxSize;
}


//-----------------------------------------------------------------------------
float ArucoProcessor::GetMaxSize() const
{
  return m_MaxSize;
}


//-----------------------------------------------------------------------------
void ArucoProcessor::SetBlockSize(int blockSize)
{
  m_BlockSize = blockSize;
}


//-----------------------------------------------------------------------------
int ArucoProcessor::GetBlockSize() const
{
  return m_BlockSize;
}


//-----------------------------------------------------------------------------
void ArucoProcessor::SetOffset(int offset)
{
  m_Offset = offset;
}


//-----------------------------------------------------------------------------
int ArucoProcessor::GetOffset() const
{
  return m_Offset;
}


//-----------------------------------------------------------------------------
std::vector<TagData> ArucoProcessor::GetTags(const cv::Mat& image) const
{
  std::vector<TagData> results;

  aruco::CameraParameters cameraParams; // using default camera params, as conversion to 3D points happens elsewhere.
  aruco::MarkerDetector   detector;

  std::vector<aruco::Marker> markers;
  detector.setMinMaxSize(m_MinSize, m_MaxSize);
  detector.setThresholdMethod(aruco::MarkerDetector::ADPT_THRES);
  detector.setThresholdParams(m_BlockSize, m_Offset);
  detector.detect(image, markers, cameraParams);

  for (unsigned int i=0; i < markers.size(); i++)
  {
    if (markers[i].isValid())
    {
      cv::Point2f cf = markers[i].getCenter();
      cv::Point2f c0f = markers[i][0];
      cv::Point2f c1f = markers[i][1];
      cv::Point2f c2f = markers[i][2];
      cv::Point2f c3f = markers[i][3];

      bard::TagData tagData(markers[i].id, cf, c0f, c1f, c2f, c3f);
      results.push_back(tagData);
    }
  }
  return results;
}

} // end namespace
