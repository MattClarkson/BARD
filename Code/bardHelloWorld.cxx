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

int main()
{
  // Its a "Hello World" to test include and library paths are set.

  vtkSmartPointer<vtkPolyData> somePolies = vtkSmartPointer<vtkPolyData>::New();
  cv::Matx44d someMatrix;
  aruco::Board someBoard;

  std::cout << "Hello World" << std::endl;
  return EXIT_SUCCESS;
}
