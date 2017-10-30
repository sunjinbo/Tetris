/* ====================================================================
 * File: grid.cpp
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#include "grid.h"

// CONSTANTS
const TInt KDefaultPositionX = 0;
const TInt KDefaultPositonY = 0;

// Constructor.
 TGrid::TGrid() 
    : iX( KDefaultPositionX ), iY( KDefaultPositonY ), iColor( KRgbWhite )
    { // no implementation required
    }
 
  TGrid::TGrid( TGrid& aGrid )
     : iX( aGrid.iX ), iY( aGrid.iY ), iColor( aGrid.iColor )
     { // no implementation required
     }
 
 // Constructor.
 TGrid::TGrid( TInt aX, TInt aY, TRgb aColor ) 
    : iX( aX ), iY( aY ), iColor( aColor )
    { // no implementation required	    
    }

// Overloading operator '=='.
TBool TGrid::operator ==( const TGrid& aGrid )
    {
    TBool result( EFalse );
    if ( iX == aGrid.iX && iY == aGrid.iY )
        {
        result = ETrue;
        }
    return result;
    }

// End of the file.
