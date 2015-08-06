/*============================================================================

  BARD: Basic Augmented Reality Demo.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

============================================================================*/
#ifndef bardMainWindow_h
#define bardMainWindow_h

#include <QMainWindow>
#include "ui_bardMainWindow.h"

namespace bard
{

class MainRenderingWidget;

class MainWindow : public QMainWindow, public Ui::BARDMainWindow {

  Q_OBJECT

public:
  MainWindow();
  virtual ~MainWindow();

  void Start();
  void SetMainRenderingWidget(MainRenderingWidget* widget);

private:
  MainRenderingWidget *m_RenderingWidget;
};

} // end namespace

#endif
