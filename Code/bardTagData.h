/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardTagData_h
#define bardTagData_h

#include <cv.h>

namespace bard {

/**
 * \class TagData
 * \brief Value type to hold centre point, 4 additional (corner) points [0-3] and point ID.
 */
class TagData {

public:

  TagData();
  TagData(const TagData& another);
  TagData(const int& pointId,
          const cv::Point2f centrePoint,
          const cv::Point2f cornerPoint0,
          const cv::Point2f cornerPoint1,
          const cv::Point2f cornerPoint2,
          const cv::Point2f cornerPoint3
          );
  ~TagData();
  TagData& operator=(const TagData& another);


  /**
   * \brief Returns the pointID, which is normally derived from the tag barcode.
   *
   * This number is NOT the index in a list, so consecutive TagData in a vector
   * will most likely have non-consecutive values for GetPointId().
   */
  int GetPointId() const;

  /**
   * \brief Return the centre of the tag, normally used as the tag 'location'.
   */
  cv::Point2f GetCentrePoint() const;

  /**
   * \brief Enables external clients to update this centre point.
   */
  void SetCentrePoint(const cv::Point2f& point);

  /**
   * \brief Returns the stored corner point.
   * \param cornerPointId integer between 0 and 3 inclusive.
   */
  cv::Point2f GetCornerPoint(const int cornerPointId) const;

  /**
   * \brief Sets the corner point.
   */
  void SetCornerPoint(const int cornerPointId, const cv::Point2f& cornerPoint);

private:

  /**
   * \brief Used by operator= and copy constructor to copy all data.
   */
  void CopyData(const bard::TagData& another);

  int          m_PointID;
  cv::Point2f  m_CentrePoint;
  cv::Point2f  m_Corners[4];

}; // end class

} // end namespace

#endif

