/* ====================================================================
 * File: removablefigure.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_NEXTREMOVABLEFIGURE_H
#define C_NEXTREMOVABLEFIGURE_H

// INCLUDES
#include <e32def.h>
#include <e32base.h> // CArrayFixFlat

#include "figurebase.h" // CFigureBase

// FORWARD DECLARATIONS
class TGrid;

/**
* CNextRemovableFigure class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CNextRemovableFigure ) : public CFigureBase
    {
public:// New Functions
    // Creates a new next removable figure object
    static CNextRemovableFigure* NewL( 
        TScene& aScene, MFigureObserver& aObserver );

    // gets a new figues
    void ChangeFigueL();

private:
    // C++ Constructor
    CNextRemovableFigure( TScene& aScene, MFigureObserver& aObserver );

    // Completes construction
    void ConstructL();

    // sets a figure type in random.
    void RandomFigureL();

    // sets a direction in random.
    void RandomDirection();

    // sets a colour in random. 
    void RandomColor();

    };

#endif // C_NEXTREMOVABLEFIGURE_H

// End of the file.
