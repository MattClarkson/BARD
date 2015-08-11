/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardVideoSourceInterface_h
#define bardVideoSourceInterface_h

#include <cv.h>

namespace bard {

/**
 * \class VideoSourceInterface
 * \brief Abstract class defining a bare-bones video source.
 *
 * Implementors must implement RAII, and all errors must be thrown as subclasses of std::runtime_exception.
 *
 * Note the two methods ExposeImage() and ExposeOpenCVImage(). This exposes
 * a raw pointer to internal images. Its up to sub-classes to decide whether
 * to clone or not to protect themselves. Either way, these points are READ only.
 */
class VideoSourceInterface
{
public:

  VideoSourceInterface();
  virtual ~VideoSourceInterface();

  bool GetFlipY() const;
  void SetFlipY(bool doFlip);

  bool GetUndistort() const;
  void SetUndistort(bool doUndistort);

  /**
   * \brief Gets the image width in pixels.
   */
  virtual unsigned int GetWidth() = 0;

  /**
   * \brief Gets the image height in pixels.
   */
  virtual unsigned int GetHeight() = 0;

  /**
  * \brief Asks the video source to retrieve an image, either from a device, or from file.
  *
  * The image can then be read by reading from ExposeImage. or ExposeOpenCVImage.
  */
  virtual bool GrabImage() = 0;

  /** Output must be in RGB format, with enough chars for 3 x width * height. */
  virtual const unsigned char* const ExposeImage() = 0;

  /** Output must be in BGR format, which I believe is normal OpenCV format. */
  virtual const cv::Mat* const ExposeOpenCVImage() = 0;

  /** Writes image to file. */
  virtual void DumpImage(const std::string& fileName) = 0;

private:

  bool m_FlipY;
  bool m_Undistort;
};

} // end namespace

#endif
