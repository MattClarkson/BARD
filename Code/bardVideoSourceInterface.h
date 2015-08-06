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

namespace bard {

/**
 * \class VideoSourceInterface
 * \brief Abstract class defining a bare-bones video source.
 *
 * Implementors must implement RAII, so all errors must be thrown as subclasses of std::runtime_exception.
 *
 * Images must be delivered as RGB, as that is what VTK pipeline expects.
 */
class VideoSourceInterface
{
public:

  VideoSourceInterface();
  virtual ~VideoSourceInterface();

  bool GetFlipY();
  void SetFlipY(bool doFlip);

  bool GetUndistort();
  void SetUndistort(bool doUndistort);

  virtual bool GrabImage() = 0;
  virtual int GetWidth() = 0;
  virtual int GetHeight() = 0;

  /**
  * Calling this 'ExposeImage' to highlight the fact that we
  * are exposing the internal data array of the image.
  */
  virtual unsigned char* ExposeImage() = 0;

private:

  bool m_FlipY;
  bool m_Undistort;
};

} // end namespace

#endif
