// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestSpatialDB.h" // implementation of class methods

#include "spatialdata/SpatialDB.h" // USES SimpleDB
#include "spatialdata/SimpleDB.h" // USES SimpleDB

#include "spatialdata/SimpleIO.h" // USES SimpleIOAscii
#include "spatialdata/SimpleIOAscii.h" // USES SimpleIOAscii

#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatial::TestSpatialDB );

// ----------------------------------------------------------------------
// Setup test subject
void
spatial::TestSpatialDB::setUp(void)
{ // setUp
  SimpleDB* pDB = new SimpleDB;

  const char* filename = "data/spatialdb.dat";
  SimpleIOAscii iohandler;
  iohandler.Filename(filename);
  pDB->IOHandler(&iohandler);

  mpDB = pDB;
  mpDB->Open();

  pDB->QueryType(SimpleDB::NEAREST);
} // setUp

// ----------------------------------------------------------------------
// Cleanup test subject
void
spatial::TestSpatialDB::tearDown(void)
{ // tearDown
  delete mpDB; mpDB = 0;
} // tearDown

// ----------------------------------------------------------------------
// Test SpatialDB
void
spatial::TestSpatialDB::testDB(void)
{ // testDB
  FIREWALL(0 != mpDB);

  const char* names[] = {"two", "one"};
  const int numVals = 2;
  const double queryLoc[] = {1.0, 2.0, 3.0};
  const double pVals[] = { 6.3, 4.7 };

  mpDB->QueryVals(names, numVals);

  double* pValsQ = (0 < numVals) ? new double[numVals] : 0;
  mpDB->Query(&pValsQ, numVals, queryLoc[0], queryLoc[1], queryLoc[2]);
  const double tolerance = 1.0e-06;
  for (int iVal=0; iVal < numVals; ++iVal)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(pValsQ[iVal]/pVals[numVals-iVal-1],
				 1.0, tolerance);

  delete[] pValsQ; pValsQ = 0;
  mpDB->Close();
} // testDB

// version
// $Id: TestSpatialDB.cc,v 1.2 2005/03/19 00:27:36 baagaard Exp $

// End of file 