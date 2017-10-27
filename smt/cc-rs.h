// *** File: cc-rs.h
// *** Author(s): Th. Fraichard
// *** Last modified on 15 Mar 2017

// Description: 

#ifndef CC_RS_H
#define CC_RS_H

#include <iostream>
#include <vector>
#include <float.h>		/* to have FLT_MAX */
using namespace std;


#include <utilities.h>
#include <configuration.h>
#include <paths.h>

SMT_CC_RS_Path *cc_reeds_shepp (SMT_Configuration start, 
				SMT_Configuration end,
				double kappa, double sigma);

#endif
