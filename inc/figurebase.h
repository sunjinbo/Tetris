/* ====================================================================
 * File: fixedbase.h
 * Created: 01/30/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_FIGUREBASE_H
#define C_FIGUREBASE_H

// INCLUDES
#include <e32base.h> // CArrayFixFlat
#include <e32def.h>
#include <gdi.h> // TRgb

// FORWARD DECLARATIONS
class TGrid;
class TScene;
class MFigureObserver;

/**
* CFigureBase class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CFigureBase ) : public CBase
    {
public:
    // Destructor.
    virtual ~CFigureBase();

    // Gets the number of grids contained in a compound figure.
    TInt CountComponentGrids() const;

    // Gets an indexed component of a compound figure.
    TGrid* ComponentGrid( TInt aIndex );

    // gets relative displacement Y-pos.
    TInt OriginX() const;

    // gets relative displacement Y-pos.
    TInt OriginY() const;

    // resets to default settings.
    virtual void Reset();
    
    // copies the contents from other one CFigureBase 
    virtual void CopyL( CFigureBase& aFigure );
    
protected:
    // Constructor.
    CFigureBase( TScene& aScene, MFigureObserver& aObserver );

    // Completes construction of the CFigureBase object.
    virtual void ConstructL();

protected:
    // Relative displacement X-pos
    TInt iOriginX;

    // Relative displacement Y-pos
    TInt iOriginY;

    // The data of CFixedFigure.
    // Own.
    CArrayFixFlat<TGrid>* iGridList;

    // The scene in which this figure locus on. 
    // No own.
    TScene& iScene;

    // Figure's observer, actually it is CTetrisGameEngine's object.
    // No own.
    MFigureObserver& iObserver;

private:
    // Used for searches
    // Own.
    TGrid* iGrid;

    };

#endif // C_FIGUREBASE_H

// End of the file.
