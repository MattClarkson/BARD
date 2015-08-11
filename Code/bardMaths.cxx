/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardMaths.h"

#include <stdexcept>
#include <strstream>

namespace bard
{

//-----------------------------------------------------------------------------
cv::Point3d CalculateCentroid(const std::vector<cv::Point3d>& points)
{
  cv::Point3d centroid(0,0,0);
  for (int i = 0; i < points.size(); i++)
  {
    centroid.x += points[i].x;
    centroid.y += points[i].y;
    centroid.z += points[i].z;
  }
  if (points.size() > 0)
  {
    double size = static_cast<double>(points.size());
    centroid.x /= size;
    centroid.y /= size;
    centroid.z /= size;
  }
  return centroid;
}


//-----------------------------------------------------------------------------
std::vector<cv::Point3d> SubtractPointFromPoints(const std::vector<cv::Point3d>& points, const cv::Point3d& point)
{
  cv::Point3d tmp;
  std::vector<cv::Point3d> result;
  for (int i = 0; i < points.size(); i++)
  {
    tmp = points[i];
    tmp.x -= point.x;
    tmp.y -= point.y;
    tmp.z -= point.z;
    result.push_back(tmp);
  }
  return result;
}


//-----------------------------------------------------------------------------
cv::Matx33d CalculateCrossCovarianceH(const std::vector<cv::Point3d>& q, const std::vector<cv::Point3d>& qPrime)
{
  cv::Matx33d result = cv::Matx33d::zeros();

  for (unsigned int i = 0; i < q.size(); ++i)
  {
    cv::Matx33d tmp(
          q[i].x*qPrime[i].x, q[i].x*qPrime[i].y, q[i].x*qPrime[i].z,
          q[i].y*qPrime[i].x, q[i].y*qPrime[i].y, q[i].y*qPrime[i].z,
          q[i].z*qPrime[i].x, q[i].z*qPrime[i].y, q[i].z*qPrime[i].z
        );

    result += tmp;
  }

  return result;
}


//-----------------------------------------------------------------------------
bool IsCloseToZero(const double& value, const double& tolerance)
{
  if (fabs(value) < tolerance)
  {
    return true;
  }
  else
  {
    return false;
  }
}


//-----------------------------------------------------------------------------
void MakeIdentity(cv::Matx44d& matrix)
{
  // Make Identity;
  matrix = matrix.zeros();
  for (int i = 0; i < 4; i++)
  {
    matrix(i,i) = 1;
  }
}


//-----------------------------------------------------------------------------
double DoSVDPointBasedRegistration(const std::vector<cv::Point3d>& fixedPoints,
                                   const std::vector<cv::Point3d>& movingPoints,
                                   cv::Matx33d& H,
                                   cv::Point3d& p,
                                   cv::Point3d& pPrime,
                                   cv::Matx44d& outputMatrix)
{
  // Based on Arun's method:
  // Least-Squares Fitting of two, 3-D Point Sets, Arun, 1987,
  // 10.1109/TPAMI.1987.4767965
  //
  // Also See:
  // http://eecs.vanderbilt.edu/people/mikefitzpatrick/papers/ (new line)
  // 2009_Medim_Fitzpatrick_TRE_FRE_uncorrelated_as_published.pdf
  // Then:
  // http://tango.andrew.cmu.edu/~gustavor/42431-intro-bioimaging/readings/ch8.pdf

  // Arun Equation 12.
  cv::SVD svd(H);

  // Arun Equation 13.
  // cv::Mat X = svd.vt.t() * svd.u.t();

  // Replace Arun Equation 13 with Fitzpatrick, chapter 8, page 470.
  cv::Mat VU = svd.vt.t() * svd.u;
  double detVU = cv::determinant(VU);
  cv::Matx33d diag = cv::Matx33d::zeros();
  diag(0,0) = 1;
  diag(1,1) = 1;
  diag(2,2) = detVU;
  cv::Mat diagonal(diag);
  cv::Mat X = (svd.vt.t() * (diagonal * svd.u.t()));

  // Arun Step 5.
  double detX = cv::determinant(X);
  bool haveTriedToFixDeterminantIssue = false;

  if ( detX < 0
       && (   bard::IsCloseToZero(svd.w.at<double>(0,0))
           || bard::IsCloseToZero(svd.w.at<double>(1,1))
           || bard::IsCloseToZero(svd.w.at<double>(2,2))
          )
     )
  {
    // Implement 2a in section VI in Arun paper.
    cv::Mat VPrime = svd.vt.t();
    VPrime.at<double>(0,2) = -1.0 * VPrime.at<double>(0,2);
    VPrime.at<double>(1,2) = -1.0 * VPrime.at<double>(1,2);
    VPrime.at<double>(2,2) = -1.0 * VPrime.at<double>(2,2);
    X = VPrime * svd.u.t();
    haveTriedToFixDeterminantIssue = true;
  }

  double fre = std::numeric_limits<double>::max();
  bard::MakeIdentity(outputMatrix);

  if (detX > 0 || haveTriedToFixDeterminantIssue)
  {
    // Arun Equation 10.
    cv::Matx31d T, tmpP, tmpPPrime;
    cv::Matx33d R(X);
    tmpP(0,0) = p.x;
    tmpP(1,0) = p.y;
    tmpP(2,0) = p.z;
    tmpPPrime(0,0) = pPrime.x;
    tmpPPrime(1,0) = pPrime.y;
    tmpPPrime(2,0) = pPrime.z;
    T = tmpPPrime - R*tmpP;

    for (int r = 0; r < 3; r++)
    {
      for (int c = 0; c < 3; c++)
      {
        outputMatrix(r,c) = R(r, c);
      }
      outputMatrix(r,3) = T(r, 0);
    }

  }

  fre = bard::CalculateFiducialRegistrationError(fixedPoints, movingPoints, outputMatrix);
  return fre;
}


//-----------------------------------------------------------------------------
double CalculateFiducialRegistrationError(const std::vector<cv::Point3d>& fixedPoints,
                                          const std::vector<cv::Point3d>& movingPoints,
                                          const cv::Matx44d& matrix
                                          )
{
  if (fixedPoints.size() != movingPoints.size())
  {
    std::stringstream oss;
    oss << "The number of 'fixed' points is " << fixedPoints.size()
        << " whereas the number of 'moving' points is " << movingPoints.size()
        << " and they should correspond.";
    throw std::runtime_error(oss.str());
  }

  unsigned int numberOfPoints = fixedPoints.size();
  double fre = 0;

  for (unsigned int i = 0; i < numberOfPoints; ++i)
  {
    cv::Matx41d f, m, mPrime;
    f(0,0) = fixedPoints[i].x;
    f(1,0) = fixedPoints[i].y;
    f(2,0) = fixedPoints[i].z;
    f(3,0) = 1;
    m(0,0) = movingPoints[i].x;
    m(1,0) = movingPoints[i].y;
    m(2,0) = movingPoints[i].z;
    m(3,0) = 1;
    mPrime = matrix * m;
    double squaredError =   (f(0,0) - mPrime(0,0)) * (f(0,0) - mPrime(0,0))
                          + (f(1,0) - mPrime(1,0)) * (f(1,0) - mPrime(1,0))
                          + (f(2,0) - mPrime(2,0)) * (f(2,0) - mPrime(2,0))
                          ;
    fre += squaredError;
  }
  if (numberOfPoints > 0)
  {
    fre /= static_cast<double>(numberOfPoints);
  }
  fre = sqrt(fre);
  return fre;
}

} // end namespace
