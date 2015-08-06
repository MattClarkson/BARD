/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include "bardVideoSourceInterface.h"

namespace bard
{

//-----------------------------------------------------------------------------
VideoSourceInterface::VideoSourceInterface()
{
}


//-----------------------------------------------------------------------------
VideoSourceInterface::~VideoSourceInterface()
{
}


//-----------------------------------------------------------------------------
bool VideoSourceInterface::GetFlipY()
{
  return m_FlipY;
}


//-----------------------------------------------------------------------------
void VideoSourceInterface::SetFlipY(bool doFlip)
{
  m_FlipY = doFlip;
}


//-----------------------------------------------------------------------------
bool VideoSourceInterface::GetUndistort()
{
  return m_Undistort;
}


//-----------------------------------------------------------------------------
void VideoSourceInterface::SetUndistort(bool doUndistort)
{
  m_Undistort = doUndistort;
}

} // end namespace
