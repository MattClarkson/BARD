/*=============================================================================

  NifTK: A software platform for medical image computing.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include "bardTagData.h"

namespace bard {

//-----------------------------------------------------------------------------
TagData::~TagData()
{
}


//-----------------------------------------------------------------------------
TagData::TagData()
: m_PointID(0)
{
  m_CentrePoint.x = 0;
  m_CentrePoint.y = 0;
  m_Corners[0].x = 0;
  m_Corners[0].y = 0;
  m_Corners[1].x = 0;
  m_Corners[1].y = 0;
  m_Corners[2].x = 0;
  m_Corners[2].y = 0;
  m_Corners[3].x = 0;
  m_Corners[3].y = 0;
}


//-----------------------------------------------------------------------------
TagData::TagData(const TagData& another)
{
  CopyData(another);
}


//-----------------------------------------------------------------------------
TagData& TagData::operator=(const TagData& another)
{
  if (this != &another)
  {
    CopyData(another);
  }
  return *this;
}


//-----------------------------------------------------------------------------
void TagData::CopyData(const TagData& another)
{
  m_PointID = another.m_PointID;
  m_CentrePoint = another.m_CentrePoint;
  m_Corners[0].x = another.m_Corners[0].x;
  m_Corners[0].y = another.m_Corners[0].y;
  m_Corners[1].x = another.m_Corners[1].x;
  m_Corners[1].y = another.m_Corners[1].y;
  m_Corners[2].x = another.m_Corners[2].x;
  m_Corners[2].y = another.m_Corners[2].y;
  m_Corners[3].x = another.m_Corners[3].x;
  m_Corners[3].y = another.m_Corners[3].y;
}


//-----------------------------------------------------------------------------
TagData::TagData(const int& pointId,
        const cv::Point2f centrePoint,
        const cv::Point2f cornerPoint0,
        const cv::Point2f cornerPoint1,
        const cv::Point2f cornerPoint2,
        const cv::Point2f cornerPoint3
        )
{
  m_PointID = pointId;
  m_CentrePoint = centrePoint;
  m_Corners[0].x = cornerPoint0.x;
  m_Corners[0].y = cornerPoint0.y;
  m_Corners[1].x = cornerPoint1.x;
  m_Corners[1].y = cornerPoint1.y;
  m_Corners[2].x = cornerPoint2.x;
  m_Corners[2].y = cornerPoint2.y;
  m_Corners[3].x = cornerPoint3.x;
  m_Corners[3].y = cornerPoint3.y;
}


//-----------------------------------------------------------------------------
int TagData::GetPointId() const
{
  return m_PointID;
}


//-----------------------------------------------------------------------------
cv::Point2f TagData::GetCentrePoint() const
{
  return m_CentrePoint;
}


//-----------------------------------------------------------------------------
void TagData::SetCentrePoint(const cv::Point2f& point)
{
  m_CentrePoint = point;
}


//-----------------------------------------------------------------------------
cv::Point2f TagData::GetCornerPoint(const int cornerPointId) const
{
  assert(cornerPointId >= 0);
  assert(cornerPointId <= 3);
  return m_Corners[cornerPointId];
}


//-----------------------------------------------------------------------------
void TagData::SetCornerPoint(const int cornerPointId, const cv::Point2f& cornerPoint)
{
  assert(cornerPointId >= 0);
  assert(cornerPointId <= 3);
  m_Corners[cornerPointId] = cornerPoint;
}

} // end namespace

