/* ====================================================================
 * File: fixedfigure.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_FIXEDFIGURE_H
#define C_FIXEDFIGURE_H

// INCLUDES
#include "figurebase.h" 

/**
* CFixedFigure class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CFixedFigure ) : public CFigureBase
    {
public:
    // creates a new fixed figure object, 
    // and leaves if there is insufficient memory to create it.
    static CFixedFigure* NewL( TScene& aScene, MFigureObserver& aObserver );

    // merge the other one figure
    void MergeL( CFigureBase& aFigureBase );

protected:
    // constructor.
    CFixedFigure( TScene& aScene, MFigureObserver& aObserver );

    // completes construction of the CFixedFigure object.
    void ConstructL();

private:
    // releases some lines in which fill with grids.
    virtual void ReleaseL();

    // it uesd to evaluate whether or not this figure get to the top of scene.
    void OverTestL();

    };

#endif // C_FIXEDFIGURE_H

// End of the file.
