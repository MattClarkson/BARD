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
 *
 * This could be generalised to "any number of additional points", but for now is hard coded
 * to exactly 4, as we are working with square tags. However, the ordering is unspecified
 * and in practical terms will depend on what your tag tracking library outputs.
 */
class TagData {

public:

  TagData();
  TagData(const TagData& another);
  TagData(const int& pointId,
          const cv::Point2d centrePoint,
          const cv::Point2d cornerPoint0,
          const cv::Point2d cornerPoint1,
          const cv::Point2d cornerPoint2,
          const cv::Point2d cornerPoint3
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
  cv::Point2d GetCentrePoint() const;

  /**
   * \brief Enables external clients to update this centre point.
   */
  void SetCentrePoint(const cv::Point2d& point);

  /**
   * \brief Returns the stored corner point.
   * \param cornerPointId integer between 0 and 3 inclusive.
   */
  cv::Point2d GetCornerPoint(const int cornerPointId) const;

  /**
   * \brief Sets the corner point.
   */
  void SetCornerPoint(const int cornerPointId, const cv::Point2d& cornerPoint);

private:

  /**
   * \brief Used by operator= and copy constructor to copy all data.
   */
  void CopyData(const bard::TagData& another);

  int          m_PointID;
  cv::Point2d  m_CentrePoint;
  cv::Point2d  m_Corners[4];

}; // end class

} // end namespace

#endif

