/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardModelData_h
#define bardModelData_h

#include <cv.h>

namespace bard {

/**
 * \class ModelData
 * \brief Value type to hold point ID and a 3D point.
 */
class ModelData {

public:

  ModelData();
  ModelData(const ModelData& another);
  ModelData(const int& pointId, const cv::Point3d modelPoint);
  ~ModelData();
  ModelData& operator=(const ModelData& another);

  /**
   * \brief Returns the pointID, which is normally derived from the tag barcode.
   *
   * This number is NOT the index in a list, so consecutive ModelData in a vector
   * will most likely have non-consecutive values for GetPointId().
   */
  int GetPointId() const;

  /**
   * \brief Return point location.
   */
  cv::Point3d GetPoint() const;

  /**
   * \brief Enables external clients to update the point.
   */
  void SetPoint(const cv::Point3d& point);

private:

  /**
   * \brief Used by operator= and copy constructor to copy all data.
   */
  void CopyData(const bard::ModelData& another);

  int          m_PointID;
  cv::Point3d  m_Point;

}; // end class

} // end namespace

#endif

