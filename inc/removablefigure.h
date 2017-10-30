/* ====================================================================
 * File: removablefigure.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_REMOVABLEFIGURE_H
#define C_REMOVABLEFIGURE_H

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
NONSHARABLE_CLASS( CRemovableFigure ) : public CFigureBase
    {
public:// New Functions
    // Creates a new next removable figure object
    static CRemovableFigure* NewL( 
        TScene& aScene, MFigureObserver& aObserver );

    // C++ Destructor.
    ~CRemovableFigure();

    // rotates( by 90 degrees clockwise )
    void Rotate();

    // moving downwards
    void DropL();

    // moving leftwards
    void Left();

    // moving rightwards
    void Right();

    // starts moving downwards.
    void StartL( TInt iLevel );
    
    // stops moving downwards.
    void Stop();
 
    // resumes moving downwards.
    void Resume();
    
   // resets all
    void Reset();
    
    // gets a new figues and then restart.
    void ChangeFigueL( CFigureBase& aFigure );

private:
    // C++ Constructor
    CRemovableFigure( TScene& aScene, MFigureObserver& aObserver );

    // Completes construction
    void ConstructL();
 
    // it uesd to evaluate whether or not 
    // this figure hit to the other one figures.
    TBool HitTest( TInt aX, TInt aY );

    // it uesd to evaluate whether or not 
    // this figure hit to the margin of scene.
    TBool MarginTest( TInt aX, TInt aY );

    // Callback for put-down updates.
    static TInt TimerCallback( TAny* aPtr );

private: // Members
    // The timer for put-down updates
    CPeriodic* iPeriodic;
    
    // Drop speed
    TTimeIntervalMicroSeconds32 iDropSpeed;
    };

#endif // C_REMOVABLEFIGURE_H

// End of the file.
