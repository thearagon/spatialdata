// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

// SWIG interface
%module spatialdb

// Header files for module C++ code
%{
#include <iosfwd>
#include <string> // USES std::string

#include "spatialdata/geocoords/CoordSys.hh"

#include "spatialdata/spatialdb/SpatialDB.hh"
#include "spatialdata/spatialdb/SimpleDB.hh"
#include "spatialdata/spatialdb/SimpleDBData.hh"
#include "spatialdata/spatialdb/SimpleIO.hh"
#include "spatialdata/spatialdb/SimpleIOAscii.hh"
#include "spatialdata/spatialdb/UniformDB.hh"
#include "spatialdata/spatialdb/CompositeDB.hh"
#include "spatialdata/spatialdb/SCECCVMH.hh"
#include "spatialdata/spatialdb/GravityField.hh"

%}

%include "exception.i"
%exception {
  try {
    $action
  } catch (const std::exception& err) {
    SWIG_exception(SWIG_RuntimeError, err.what());
  } // try/catch
 } // exception

%include "typemaps.i"
%include "../include/chararray.i"

// Numpy interface stuff
%{
#define SWIG_FILE_WITH_INIT
%}
%include "../include/numpy.i"
%init %{
import_array();
%}

// Interfaces

%include "SpatialDBObj.i"
%include "SimpleDB.i"
%include "SimpleDBData.i"
%include "SimpleIO.i"
%include "SimpleIOAscii.i"
%include "UniformDB.i"
%include "CompositeDB.i"
%include "SCECCVMH.i"
%include "GravityField.i"


// End of file