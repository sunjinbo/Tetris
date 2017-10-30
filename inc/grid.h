/* ====================================================================
 * File: grid.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef T_GRID_H
#define T_GRID_H

#include <e32cmn.h> // TPoint
#include <gdi.h> // TRgb


/**
* TGrid class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( TGrid )
    {
public:
    // Constructor.
    TGrid();
    
    TGrid( TGrid& aGrid );
    
    TGrid( TInt aX, TInt aY, TRgb aColor );

    // Overloading operator '=='.
    TBool operator ==( const TGrid& aGrid );

public:
    // The x co-ordinate value.
    TInt iX;

    // The y co-ordinate value.
    TInt iY;

    // The colour of this grid.
    TRgb iColor;
    
    };

#endif // T_GRID_H

// End of the file.
