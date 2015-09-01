/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include <tclap/CmdLine.h>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cv.h>
#include <highgui.h>
#include <fstream>

int main(int argc, char** argv)
{
  try
  {
    TCLAP::CmdLine cmd("Basic Augmented Reality Demo - Camera Calibration", ' ', "0.1");
    TCLAP::ValueArg<std::string> outputArg("o","output","Output file for intrinsic and distortion params",true,"","string");
    TCLAP::UnlabeledMultiArg<std::string> inputArg("input","Multiple valued argument, of files of images, containing chessboards.",true, "string");
    TCLAP::ValueArg<int> widthArg("x","xcorners","Number of internal corners along the width (x)",true,1,"int");
    TCLAP::ValueArg<int> heightArg("y","ycorners","Number of internal corners along the height (y)",true,1,"int");
    TCLAP::ValueArg<float> sizeArg("s","size","Square size in millimetres",true,1,"float");
    cmd.add( inputArg );
    cmd.add( outputArg );
    cmd.add( widthArg );
    cmd.add( heightArg );
    cmd.add( sizeArg );
    cmd.parse( argc, argv );
    std::vector<std::string> inputFiles = inputArg.getValue();
    std::string outputFile = outputArg.getValue();
    int width = widthArg.getValue();
    int height = heightArg.getValue();
    float size = sizeArg.getValue();
    std::vector<std::vector<cv::Point2f> > imagePoints;
    cv::Size boardSize(width, height);
    cv::Size imageSize;

    std::cout << "Input file list contains " << inputFiles.size() << " elements" << std::endl;
    std::cout << "Looking for chessboards with (" << width << ", " << height << ") corners, that are " << size << " mm square." << std::endl;
    std::cout << "Output file: " << outputFile << std::endl;

    // For each input image.
    for (int i = 0; i < inputFiles.size(); i++)
    {
      // Load image
      std::string fileName = inputFiles[i];
      cv::Mat view = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);
      if(view.empty())
      {
          std::cout << "WARNING: Can not open " << fileName << std::endl;
      }

      std::cout << "Read: " << fileName;
      if (i == 0)
      {
        imageSize = cv::Size(view.cols, view.rows);
      }
      else
      {
        if (view.cols != imageSize.width || view.rows != imageSize.height)
        {
          throw std::runtime_error("Inconsistent image sizes");
        }
      }

      // Convert colour to grey-scale.
      cv::Mat viewGray;
      cv::cvtColor(view, viewGray, cv::COLOR_RGB2GRAY);

      // Extract corners.
      std::vector<cv::Point2f> pointbuf;
      bool isSuccessful = false;

      isSuccessful = cv::findChessboardCorners( view, boardSize, pointbuf,
                     CV_CALIB_CB_ADAPTIVE_THRESH |
                     CV_CALIB_CB_FAST_CHECK |
                     CV_CALIB_CB_NORMALIZE_IMAGE);

      std::cout << ", isSuccessful: " << isSuccessful << std::endl;
      if (isSuccessful)
      {
        cv::cornerSubPix(viewGray, pointbuf,
                         cv::Size(11,11),
                         cv::Size(-1,-1),
                         cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

        imagePoints.push_back(pointbuf);
      }
    }

    // Check at least 3 images.
    if (imagePoints.size() < 3)
    {
      throw std::runtime_error("Less than 3 images processed successfully");
    }

    // Create object coordinates
    std::vector<std::vector<cv::Point3f> > objectPoints(1);
    for( int i = 0; i < height; i++ )
    {
      for( int j = 0; j < width; j++ )
      {
        objectPoints[0].push_back(cv::Point3f(float(j*size),
                                              float(i*size), 0));
      }
    }
    objectPoints.resize(imagePoints.size(),objectPoints[0]);

    // Run Calibration
    cv::Mat cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
    std::vector<cv::Mat> rvecs, tvecs;

    double rms = cv::calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
                    distCoeffs, rvecs, tvecs);

    std::cout << "RMS=" << rms << std::endl;

    // Output calib data.
    std::ofstream ofs(outputFile.c_str());
    if (!ofs.is_open())
    {
      std::stringstream errMsg;
      errMsg << "Failed to open file " << outputFile << " to write intrinsic data." << std::endl;
      throw std::runtime_error(errMsg.str());
    }
    for (int i = 0; i < 3; i++)
    {
      ofs << cameraMatrix.at<double>(i, 0) << " " << cameraMatrix.at<double>(i, 1) << " " << cameraMatrix.at<double>(i, 2) << std::endl;
    }
    ofs << distCoeffs.at<double>(0,0) << " " << distCoeffs.at<double>(1,0) << " " << distCoeffs.at<double>(2,0) << " " << distCoeffs.at<double>(3,0) << std::endl;
    ofs.close();

    return EXIT_SUCCESS;
  }
  catch (TCLAP::ArgException &e)
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
}
