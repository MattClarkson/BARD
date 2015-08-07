/*=============================================================================

  NifTK: A software platform for medical image computing.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/
#include "bardModelData.h"

namespace bard {

//-----------------------------------------------------------------------------
ModelData::~ModelData()
{
}


//-----------------------------------------------------------------------------
ModelData::ModelData()
: m_PointID(0)
{
  m_Point.x = 0;
  m_Point.y = 0;
  m_Point.z = 0;
}


//-----------------------------------------------------------------------------
ModelData::ModelData(const ModelData& another)
{
  CopyData(another);
}


//-----------------------------------------------------------------------------
ModelData& ModelData::operator=(const ModelData& another)
{
  if (this != &another)
  {
    CopyData(another);
  }
  return *this;
}


//-----------------------------------------------------------------------------
void ModelData::CopyData(const ModelData& another)
{
  m_PointID = another.m_PointID;
  m_Point = another.m_Point;
}


//-----------------------------------------------------------------------------
ModelData::ModelData(const int& pointId,
        const cv::Point3d point
        )
{
  m_PointID = pointId;
  m_Point = point;
}


//-----------------------------------------------------------------------------
int ModelData::GetPointId() const
{
  return m_PointID;
}


//-----------------------------------------------------------------------------
cv::Point3d ModelData::GetPoint() const
{
  return m_Point;
}


//-----------------------------------------------------------------------------
void ModelData::SetPoint(const cv::Point3d& point)
{
  m_Point = point;
}

} // end namespace

