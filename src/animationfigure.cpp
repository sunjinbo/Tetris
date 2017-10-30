/* ====================================================================
 * File: animationfigure.cpp
 * Created: 01/30/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CPeriodic

#include "animationfigure.h"
#include "scene.h"
#include "engineobserver.h"
#include "figureobserver.h"
#include "grid.h"

// CONSTANTS
const TInt KDefaultInitialLine = -1; // Line 0.
const TInt KAnimationDelayTimeout = 0; // 0 secs.
const TInt KAnimationUpdateTimeout = 150000; // 0.15 secs.

// Creates a new next removable figure object
CAnimationFigure* CAnimationFigure::NewL( TScene& aScene, 
                                          MFigureObserver& aObserver )
    {
    CAnimationFigure* self = new( ELeave ) CAnimationFigure( 
        aScene, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// C++ destructor
CAnimationFigure::~CAnimationFigure()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;   
        }
    }

// reset all members variable
void CAnimationFigure::Reset()
    {
    CFigureBase::Reset();

    iAnimationStatus = ETrue;
    iLine = KDefaultInitialLine;
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;   
        iPeriodic = NULL;
        }
    }

// C++ Constructor
CAnimationFigure::CAnimationFigure( TScene& aScene, 
                                    MFigureObserver& aObserver )
    : CFigureBase( aScene, aObserver )
    { // no implementation required
    }

// Completes construction
void CAnimationFigure::ConstructL()
    {
    CFigureBase::ConstructL();
    iAnimationStatus = ETrue;
    iLine = KDefaultInitialLine;
    }

// plays animation( uprightness type ).
void CAnimationFigure::PlayL( CFigureBase& aFigure )
    {
    Reset();

    CFigureBase::CopyL( aFigure );
    
    iObserver.StateChangedL( EAnimationFigureStarted );
    // Initializations that are not related directly to control framework.
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    // start playing animation
    iPeriodic->Start(
            KAnimationDelayTimeout,
            KAnimationUpdateTimeout,
            TCallBack( TimerCallback, this ) ); 
    }

// Handles an active object's request completion event.
void CAnimationFigure::RunL()
    {
    if ( iAnimationStatus ) // UP
        {
        iLine += 1;
        TGrid* grid( NULL );
        for ( TInt i = 0; i < iScene.Width(); ++i )
            {
            if ( KErrNotFound == Find( i, iLine ) )
                {
                grid = new( ELeave ) TGrid( i, iLine, KRgbBlack );
                iGridList->AppendL( *grid );
                delete grid;
                grid = NULL;
                }
            }
        if ( iLine == iScene.Height() - 1 )
            {
            iAnimationStatus = EFalse;
            }
        }
    else // DOWN
        {
        TInt index( KErrNotFound );
        for ( TInt i = 0; i < iScene.Width(); ++i )
            {
            index = Find( i, iLine );
            iGridList->Delete( index );
            iGridList->Compress();
            }
        iLine -= 1;
        if ( KDefaultInitialLine == iLine )
            {
            Reset();
            iObserver.StateChangedL( EAnimationFigureEnded );
            }
        }
    iObserver.StateChangedL( EAnimationFigureUpdated );
    }

// finds the position of an element within the grid list.
TInt CAnimationFigure::Find( TInt aX, TInt aY  )
    {
    TInt result ( KErrNotFound );
    for ( TInt i = 0; i < iGridList->Count(); ++i )
        {
        TGrid grid = iGridList->At( i );
        if ( grid.iX == aX && grid.iY == aY )
            {
            result = i;
            break;
            }
        }
    return result;
    }

// The timer for put-down updates
TInt CAnimationFigure::TimerCallback( TAny* aPtr )
    {
    CAnimationFigure* self = static_cast<CAnimationFigure*> ( aPtr );
    self->RunL();
    return 0;
    }

// End of the file.
