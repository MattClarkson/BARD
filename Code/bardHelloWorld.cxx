/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <iostream>
#include <cstdlib>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <cv.h>
#include <aruco/boarddetector.h>
#include <bardOpenCVVideoSource.h>

int main()
{
  // Its a "Hello World" to test include and library paths are set.

  vtkSmartPointer<vtkPolyData> somePolies = vtkSmartPointer<vtkPolyData>::New();
  cv::Matx44d someMatrix;
  aruco::Board someBoard;
  bard::OpenCVVideoSource mySource("");

  char a;
  std::cin >> a;
  mySource.DumpImage("/tmp/matt.jpg");
  std::cin >> a;

  std::cout << "Hello World, video is " << mySource.GetWidth() << " x " << mySource.GetHeight() << std::endl;

  return EXIT_SUCCESS;
}
