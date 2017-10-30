/* ====================================================================
 * File: animationfigure.h
 * Created: 01/30/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_ANIMATIONFIGURE_H
#define C_ANIMATIONFIGURE_H

// INCLUDES
#include <e32def.h>
#include "figurebase.h" // CFigureBase

// FORWARD DECLARATIONS
class CPeriodic;

/**
* CRemovableFigure class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CAnimationFigure ) : public CFigureBase
    {
public:// New Functions
    // Creates a new next removable figure object
    static CAnimationFigure* NewL( 
        TScene& aScene, MFigureObserver& aObserver );
 
    // C++ Destructor.
    ~CAnimationFigure();
    
    // reset all members variable
    void Reset();

    // plays animation( uprightness type ).
    void PlayL( CFigureBase& aFigure );

private:
    // C++ Constructor
    CAnimationFigure( TScene& aScene, MFigureObserver& aObserver );

    // Completes construction
    void ConstructL();

    // Handles an active object's request completion event.
    void RunL();
    
    // finds the position of an element within the grid list
    TInt Find( TInt aX, TInt aY  );

    // Callback for put-down updates.
    static TInt TimerCallback( TAny* aPtr );

private: // Members
    // Current Status 
    TBool iAnimationStatus;

    // Current Line
    TInt iLine;

    // Periodic timer active object.
    // Own
    CPeriodic* iPeriodic;

    };

#endif // C_ANIMATIONFIGURE_H

// End of the file.
