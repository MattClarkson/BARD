/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardMaths_h
#define bardMaths_h

#include <cv.h>

namespace bard
{

/**
 * \brief Calculates centroid of a list of points. Won't cope with NaN.
 */
cv::Point3d CalculateCentroid(const std::vector<cv::Point3d>& points);

/**
 * \brief Subtracts a point (e.g. the centroid), from all points.
 */
std::vector<cv::Point3d> SubtractPointFromPoints(const std::vector<cv::Point3d>& points, const cv::Point3d& point);

/**
 * \brief Implements eqn 11 in Arun et al. 1987.
 */
cv::Matx33d CalculateCrossCovarianceH(const std::vector<cv::Point3d>& q, const std::vector<cv::Point3d>& qPrime);

/**
 * \brief Returns true if value is closer to zero than tolerance.
 */
bool IsCloseToZero(const double& value, const double& tolerance = 0.000001);

/**
 * \brief Sets the matrix to Identity.
 */
void MakeIdentity(cv::Matx44d& matrix);

/**
 * \brief Does Pivot calibration.
 */
double DoPivotCalibration(const std::vector<cv::Matx44d>& matrices, cv::Matx44d& outputMatrix);

/**
 * \brief Does SVD point based registration.
 *
 * Based on Arun's method:
 * Least-Squares Fitting of two, 3-D Point Sets, Arun, 1987,
 * http://dx.doi.org/10.1109/TPAMI.1987.4767965
 */
double DoSVDPointBasedRegistration(const std::vector<cv::Point3d>& fixedPoints,
                                   const std::vector<cv::Point3d>& movingPoints,
                                   cv::Matx33d& H,
                                   cv::Point3d& p,
                                   cv::Point3d& pPrime,
                                   cv::Matx44d& outputMatrix);

/**
 * \brief Calculates the FRE of fixed and moving points transformed by the matrix.
 */
double CalculateFiducialRegistrationError(const std::vector<cv::Point3d>& fixedPoints,
                                          const std::vector<cv::Point3d>& movingPoints,
                                          const cv::Matx44d& matrix
                                          );

} // end namespace
#endif
