/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/

#include "bardMainWindow.h"
#include "bardMainRenderingWidget.h"

namespace bard
{

//-----------------------------------------------------------------------------
MainWindow::MainWindow()
{
}


//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{

}


//-----------------------------------------------------------------------------
void MainWindow::Start()
{
  m_RenderingWidget->GetInteractor()->Start();
}


//-----------------------------------------------------------------------------
void MainWindow::SetMainRenderingWidget(MainRenderingWidget* widget)
{
  m_RenderingWidget = widget;
  this->setCentralWidget(m_RenderingWidget);
}

} // end namespace

