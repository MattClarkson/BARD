Basic Augmented Reality Demo (BARD)
===================================

This project was built for the [MediCSS](http://www.medicss.cs.ucl.ac.uk/) summer school 2015.

The aim was to demo some features of VTK, OpenCV and ArUco.

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
   1. includes pivot calibration to create a pointer object
   1. includes Procrustes analysis to register models to world coordinates

Build Instructions
------------------

Currently tested on Mac OSX 10.10.4, using Xcode 6.1, Qt 4.8.7, CMake 3.1.2

```
git clone https://github.com/MattClarkson/BARD.git
mkdir BARD-SuperBuild-Debug
cd BARD-SuperBuild-Debug
ccmake ../BARD
make
```

Future Plans
------------

 * Command line app to calibrate mono camera using OpenCV standard routines.

(As of Aug 2015, these 3 apps were done using existing software, eg. NifTK))

