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
 * \brief Value type to hold centre point, 4 additional (corner) points [0-3] and point ID.
 * \see TagData
 */
class ModelData {

public:

  ModelData();
  ModelData(const ModelData& another);
  ModelData(const int& pointId,
          const cv::Point3f centrePoint,
          const cv::Point3f cornerPoint0,
          const cv::Point3f cornerPoint1,
          const cv::Point3f cornerPoint2,
          const cv::Point3f cornerPoint3
          );
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
   * \brief Return the centre of the tag, normally used as the tag 'location'.
   */
  cv::Point3f GetCentrePoint() const;

  /**
   * \brief Enables external clients to update this centre point.
   */
  void SetCentrePoint(const cv::Point3f& point);

  /**
   * \brief Returns the stored corner point.
   * \param cornerPointId integer between 0 and 3 inclusive.
   */
  cv::Point3f GetCornerPoint(const int cornerPointId) const;

  /**
   * \brief Sets the corner point.
   */
  void SetCornerPoint(const int cornerPointId, const cv::Point3f& cornerPoint);

private:

  /**
   * \brief Used by operator= and copy constructor to copy all data.
   */
  void CopyData(const bard::ModelData& another);

  int          m_PointID;
  cv::Point3f  m_CentrePoint;
  cv::Point3f  m_Corners[4];

}; // end class

} // end namespace

#endif

