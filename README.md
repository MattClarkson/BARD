Basic Augmented Reality Demo (BARD)
===================================

This project was built for the [MediCSS](http://www.medicss.cs.ucl.ac.uk/) summer school 2015-2017

The aim was to demo some features of [VTK](http://www.vtk.org), [OpenCV](http://www.opencv.org) and [ArUco](http://www.uco.es/investiga/grupos/ava/node/26).

Features
--------

 1. `bardGrabber` uses OpenCV video source to grab a single frame and save to file. For now, camera calibration should be done externally. 
 1. `bard` performs the following:
   1. launches a single QVTKWidget
   1. creates an OpenCV VideoSource (e.g. from webcam).
   1. displays semi-transparent video in foreground vtkRenderer
   1. overlays vtkPolyData
   1. loads references models (3D coordinates and point ID) of ArUco boards.
   1. uses ArUco/OpenCV to track ArUco boards
   1. provides a modified VTK camera that uses the calibrated intrinsic parameters
   1. moves the VTK camera according to a registration transformation from 3D reference model coordinates to 2D coordinates of ArUco markers
   1. tracks a single pointer, made using a separate ArUco marker
 1. `bardPivotCalibration` does pivot calibration to create a pointer object. See [Feuerstein 2008](http://dx.doi.org/10.1109/TMI.2007.907327).
 1. `bardProcrustes` does point based registration (Procrustes analysis). See [Arun 1987](http://dx.doi.org/10.1109/TPAMI.1987.4767965).
 1. `bardCameraCalibration` does intrinsic camera calibration, based on OpenCV. See [OpenCV](http://docs.opencv.org/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html).

Build Instructions
------------------

 1. CMake version: 3.1+
 1. Qt version: Tested with 4.8.7 or 5.4.2. If you go much newer then Qt 5.4.2 you will probably have to build Qt to ensure it has QtWebkitWidgets
 1. Ensure qmake is on your PATH
 1. Install git bash from http://git-scm.com

Currently tested on:
 1. Mac OSX 10.10.5, Qt 4.8.7, CMake 3.1.2, clang 600.0.57
 1. Windows, Qt 5.4.0, Visual Studio 2013.

  
```
git clone https://github.com/MattClarkson/BARD.git
mkdir BARD-SuperBuild-Debug
cd BARD-SuperBuild-Debug
ccmake ../BARD
(set some options, most likely for Qt)
make
```

