/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardPnPRegistration.h"

namespace bard
{

//-----------------------------------------------------------------------------
PnPRegistration::PnPRegistration()
{
}


//-----------------------------------------------------------------------------
PnPRegistration::~PnPRegistration()
{
}


//-----------------------------------------------------------------------------
vtkSmartPointer<vtkMatrix4x4> PnPRegistration::DoRegistration(
      const cv::Matx33d& intrinsics,
      const std::vector<ModelData>& model,
      const std::vector<TagData>& tags)
{
  vtkSmartPointer<vtkMatrix4x4> pose = vtkSmartPointer<vtkMatrix4x4>::New();
  pose->Identity();

  // Collect tag points that have been detected in image and are present in this model.
  std::vector<cv::Point3f> points3D;
  std::vector<cv::Point2f> points2D;
  for (int i = 0; i < tags.size(); i++)
  {
    for (int j = 0; j < model.size(); j++)
    {
      if (tags[i].GetPointId() == model[i].GetPointId())
      {
        points3D.push_back(model[i].GetCentrePoint());
        points3D.push_back(model[i].GetCornerPoint(0));
        points3D.push_back(model[i].GetCornerPoint(1));
        points3D.push_back(model[i].GetCornerPoint(2));
        points3D.push_back(model[i].GetCornerPoint(3));
        points2D.push_back(tags[i].GetCentrePoint());
        points2D.push_back(tags[i].GetCornerPoint(0));
        points2D.push_back(tags[i].GetCornerPoint(1));
        points2D.push_back(tags[i].GetCornerPoint(2));
        points2D.push_back(tags[i].GetCornerPoint(3));
      }
    }
  }

  // Now solve 2D/3D registration.
  cv::Mat cameraMatrix(intrinsics);

  cv::Mat distortionCoefficients(4, 1, cv::DataType<double>::type);
  distortionCoefficients.at<double>(0) = 0;
  distortionCoefficients.at<double>(1) = 0;
  distortionCoefficients.at<double>(2) = 0;
  distortionCoefficients.at<double>(3) = 0;

  cv::Mat rvec(3, 1, cv::DataType<double>::type);
  cv::Mat tvec(3, 1, cv::DataType<double>::type);

  cv::solvePnP(points3D, points2D, cameraMatrix, distortionCoefficients, rvec, tvec);

  cv::Mat rotationMatrix(3, 3, cv::DataType<double>::type);
  cv::Rodrigues(rvec, rotationMatrix);

  // Convert to VTK matrix.
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      pose->SetElement(i, j, rotationMatrix.at<double>(i,j));
    }
    pose->SetElement(i, 3, tvec.at<double>(i, 0));
  }
  std::cerr << "Matt, matrix is" << *pose << std::endl;
  return pose;
}

} // end namespace
