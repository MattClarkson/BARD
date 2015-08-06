/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardOpenCVVideoSource_h
#define bardOpenCVVideoSource_h

#include "bardVideoSourceInterface.h"
#include <highgui.h>

namespace bard
{

/**
 * \class OpenCVVideoSource
 * \brief Implements a very basic interface to OpenCV's video source.
 *
 * Implements RAII, so all setup/init is in constructor, and all tear-down is in destructor.
 */
class OpenCVVideoSource : public VideoSourceInterface {

public:

  OpenCVVideoSource(const std::string& fileName);
  virtual ~OpenCVVideoSource();

  virtual unsigned int GetWidth();
  virtual unsigned int GetHeight();
  virtual bool GrabImage();
  virtual const unsigned char* const ExposeImage();
  virtual const cv::Mat* const ExposeOpenCVImage();
  void DumpImage(const std::string& fileName);

private:

  cv::VideoCapture *m_VideoCapture;
  std::string       m_FileName; // if empty, we are grabbing from default device.
  cv::Mat           m_CurrentFrameInBGR;
  cv::Mat           m_CurrentFrameInRGB;
};

} // end namespace

#endif
