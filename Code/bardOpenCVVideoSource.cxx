/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#include "bardOpenCVVideoSource.h"

#include <stdexcept>
#include <iostream>
#include <cv.h>

namespace bard
{

//-----------------------------------------------------------------------------
OpenCVVideoSource::OpenCVVideoSource(const std::string& fileName)
{
  if (fileName.length() > 0)
  {
    m_VideoCapture = new cv::VideoCapture(fileName);
  }
  else
  {
    m_VideoCapture = new cv::VideoCapture(0);
  }

  if (m_VideoCapture == NULL)
  {
    throw std::runtime_error("Video capture device is NULL.");
  }

  if (!m_VideoCapture->isOpened())
  {
    throw std::runtime_error("Video capture device failed to open.");
  }

  m_FileName = fileName;

  // Grab at least one frame, so image is initialised.
  if (!this->GrabImage())
  {
    throw std::runtime_error("Failed to grab first frame.");
  }
}


//-----------------------------------------------------------------------------
OpenCVVideoSource::~OpenCVVideoSource()
{
  // OpenCV docs says the destructor will release stuff.
  delete m_VideoCapture;
}


//-----------------------------------------------------------------------------
bool OpenCVVideoSource::GrabImage()
{
  if (!m_VideoCapture->grab())
  {
    if (m_FileName.length() == 0)
    {
      throw std::runtime_error("Failed to grab image from device.");
    }

    // If its a file read, it might just be end of file.
    return false;
  }

  if (!m_VideoCapture->retrieve(m_CurrentFrameInBGR))
  {
    throw std::runtime_error("Failed to retrieve recently grabbed image.");
  }

  cvtColor(m_CurrentFrameInBGR, m_CurrentFrameInRGB, CV_BGR2RGB);

  return true;
}


//-----------------------------------------------------------------------------
const unsigned char* const OpenCVVideoSource::ExposeImage()
{
  return m_CurrentFrameInRGB.data;
}


//-----------------------------------------------------------------------------
const cv::Mat* const OpenCVVideoSource::ExposeOpenCVImage()
{
  return &m_CurrentFrameInBGR;
}


//-----------------------------------------------------------------------------
unsigned int OpenCVVideoSource::GetWidth()
{
  return static_cast<unsigned int>(m_VideoCapture->get(CV_CAP_PROP_FRAME_WIDTH));
}


//-----------------------------------------------------------------------------
unsigned int OpenCVVideoSource::GetHeight()
{
  return static_cast<unsigned int>(m_VideoCapture->get(CV_CAP_PROP_FRAME_HEIGHT));
}


//-----------------------------------------------------------------------------
void OpenCVVideoSource::DumpImage(const std::string& fileName)
{
  if (!this->GrabImage())
  {
    throw std::runtime_error("Failed to grab image.");
  }
  if (!cv::imwrite(fileName, m_CurrentFrameInBGR))
  {
    throw std::runtime_error("Failed to write file.");
  }
}

} // end namespace

