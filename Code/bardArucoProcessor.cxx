/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardArucoProcessor.h"

#include <aruco/aruco.h>
#include <bardTagData.h>

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
std::vector<TagData> ArucoProcessor::GetTags(const cv::Mat& image) const
{
  std::vector<TagData> results;

  aruco::CameraParameters cameraParams;
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

      cv::Point2d cd = cf;
      cv::Point2d c0d = c0f;
      cv::Point2d c1d = c1f;
      cv::Point2d c2d = c2f;
      cv::Point2d c3d = c3f;

      bard::TagData tagData(markers[i].id, cd, c0d, c1d, c2d, c3d);
      results.push_back(tagData);
    }
  }
  return results;
}

} // end namespace
