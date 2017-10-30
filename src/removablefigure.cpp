/* ====================================================================
 * File: removablefiOriginXedfigure.cpp
 * Created: 12/28/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CPeriodic

#include "removablefigure.h"
#include "scene.h"
#include "engineobserver.h"
#include "figureobserver.h"
#include "grid.h"

// CONSTANTS
const TInt KDropDelayTimeout = 0; // 0.0 secs
const TInt KDropSpeedDefaultTimeout = 0; // 0.0 sec
const TInt KDropSpeedLevelZeroTimeout = 800000; // 0.8 secs
const TInt KDropSpeedLevelOneTimeout = 500000; // 0.5 secs
const TInt KDropSpeedLevelTwoTimeout = 400000; // 0.4 secs
const TInt KDropSpeedLevelThreeTimeout = 300000; // 0.3 secs
const TInt KDropSpeedLevelFourTimeout = 200000; // 0.2 secs
const TInt KDropSpeedLevelFiveTimeout = 100000; // 0.1 secs
const TInt KDropSpeedAccelerateTimeout = 50000; // 0.05 secs

// Creates a new next removable figure object
CRemovableFigure* CRemovableFigure::NewL( TScene& aScene, 
                                          MFigureObserver& aObserver )
    {
    CRemovableFigure* self = new( ELeave ) CRemovableFigure( 
        aScene, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// C++ destructor
CRemovableFigure::~CRemovableFigure()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;   
        }
    }

// rotates( by 90 degrees clockwise )
void CRemovableFigure::Rotate()
    {
    TInt countGridList( iGridList->Count() );
    TGrid* thisGrid( NULL );
    for ( TInt i = 0; i < countGridList; ++i )
        {
        thisGrid = &iGridList->At( i );
        thisGrid->iY = thisGrid->iX + thisGrid->iY;
        thisGrid->iX = thisGrid->iY - thisGrid->iX;
        thisGrid->iY = 3 - thisGrid->iY + thisGrid->iX;
        }
    // Hit Test and Margin Test
    if ( HitTest( iOriginX, iOriginY ) && MarginTest( iOriginX, iOriginY ) )
        {
        iObserver.StateChangedL( ERemovableFigureRotated );    
        }
    else // back rotate
        {
        for ( TInt i = 0; i < countGridList; ++i )
            {
            thisGrid = &iGridList->At( i );
            thisGrid->iX = thisGrid->iY + thisGrid->iX;
            thisGrid->iY = thisGrid->iX - thisGrid->iY;
            thisGrid->iX = 3 - thisGrid->iX + thisGrid->iY;
            }
        }
    }

// Moving downwards
void CRemovableFigure::DropL()
    {
    if ( HitTest( iOriginX, iOriginY - 1 ) )
        {
        if ( MarginTest( iOriginX, iOriginY - 1 ) )
            {
            iOriginY -= 1;
            iObserver.StateChangedL( ERomovableFigureDropped );
            }
        else
            {
            iObserver.StateChangedL( ERomovableFigureDropEnded );
            }
        }
    else
        {
        iObserver.StateChangedL( ERomovableFigureDropEnded );
        }
    }

// Moving leftwards
void CRemovableFigure::Left()
    {
    if ( HitTest( iOriginX - 1, iOriginY ) && MarginTest( iOriginX - 1, iOriginY ) )
        {
        iOriginX -= 1;
        iObserver.StateChangedL( ERemovableFigureLeftMoved );
        }
    }

// Moving rightwards
void CRemovableFigure::Right()
    {
    if ( HitTest( iOriginX + 1, iOriginY ) &&  MarginTest( iOriginX + 1, iOriginY ) )
        {
        iOriginX += 1;
        iObserver.StateChangedL( ERemovableFigureRightMoved );
        }
    }

// starts moving downwards.
void CRemovableFigure::StartL( TInt aLevel )
    {
    // If timer is running, stop it fristly.
    Stop();
    
     // Initializations that are not related directly to control framework.
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    
    iPeriodic->Cancel();
    // Default drop speed is level 1.
    switch( aLevel )
        {
        case 0:
            iDropSpeed = KDropSpeedLevelZeroTimeout;
            break;
        case 1:
            iDropSpeed = KDropSpeedLevelOneTimeout;
            break;
        case 2:
            iDropSpeed = KDropSpeedLevelTwoTimeout;
            break;
        case 3:
            iDropSpeed = KDropSpeedLevelThreeTimeout;
            break;
        case 4:
            iDropSpeed = KDropSpeedLevelFourTimeout;
            break;
        default:
            iDropSpeed = KDropSpeedLevelFourTimeout;
            break;
        }
    iPeriodic->Start(
        KDropDelayTimeout,
        iDropSpeed,
        TCallBack( TimerCallback, this ) ); 
    }

 // stops moving downwards.
 void CRemovableFigure::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;   
        }
    }

// resumes moving downwards
void CRemovableFigure::Resume()
    {
    // Initializations that are not related directly to control framework.
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
        KDropDelayTimeout,
        iDropSpeed,
        TCallBack( TimerCallback, this ) ); 
    }

// resets all
void CRemovableFigure::Reset()
    {
    CFigureBase::Reset();
    // stops active object.
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;   
        }
    iDropSpeed = KDropSpeedDefaultTimeout;
    }

// gets a new figues and then restart.
void CRemovableFigure::ChangeFigueL(  CFigureBase& aFigure  )
    {
    TInt count( aFigure.CountComponentGrids() );
    iGridList->Reset();
    for ( TInt i = 0; i < count; ++i )
        {
        TGrid* grid = aFigure.ComponentGrid( i );
        iGridList->AppendL( *grid );
        }
    
    iOriginX = iScene.Width() / 2 - 2;
    iOriginY = iScene.Height();

    iObserver.StateChangedL( ERemovableFigureUpdated );
    }

 // Constructor
 CRemovableFigure::CRemovableFigure( TScene& aScene, 
		                             MFigureObserver& aObserver )
    : CFigureBase( aScene, aObserver )
    { // no implementation required 
    }

// Completes construction
void CRemovableFigure::ConstructL()
    {
    CFigureBase::ConstructL();
    iOriginX = iScene.Width() / 2 - 2;
    iOriginY = iScene.Height();
    iDropSpeed = KDropSpeedDefaultTimeout;
    }

// it uesd to evaluate whether or not 
// this figure hit to the other one figures.
TBool CRemovableFigure::HitTest( TInt aX, TInt aY )
    {
    CFigureBase* figure( NULL );
    TInt countFigures( iScene.Count() );
    TInt countGrids( 0 );
    const TGrid* figureGrid( NULL );
    TGrid* thisGrid( NULL );
    for ( TInt i = 0; i < countFigures; ++i )
        {
        figure = const_cast<CFigureBase*>( iScene.At( i ) );
        if ( figure != this )
            {
            countGrids = figure->CountComponentGrids();
            for ( TInt j = 0; j < countGrids; ++j )
                {
                figureGrid = figure->ComponentGrid( j );
                for ( TInt m = 0; m < iGridList->Count(); ++m )
                    {
                    thisGrid = &iGridList->At( m );
                    if ( ( thisGrid->iX + aX == figureGrid->iX ) &&
                         ( thisGrid->iY + aY == figureGrid->iY ) )
                        {
                        return EFalse;
                        }
                    }
                }
            }
        }
    return ETrue;
    }

// it uesd to evaluate whether or not 
// this figure hit to the margin of scene.
TBool CRemovableFigure::MarginTest( TInt aX, TInt aY )
    {
    TBool result( ETrue );
    TInt countGridList( iGridList->Count() );
    TGrid* thisGrid( NULL );
    
    for ( TInt i = 0; i < countGridList; ++i )
        {
        thisGrid = &iGridList->At( i );
        if ( thisGrid->iX + aX > iScene.Width() - 1 ||
             thisGrid->iX + aX < 0 ||
             thisGrid->iY + aY < 0 )
            result = EFalse;
        }
    return result;
    }

// The timer for put-down updates
TInt CRemovableFigure::TimerCallback( TAny* aPtr )
    {
    CRemovableFigure* self = static_cast<CRemovableFigure*> ( aPtr );
    self->DropL();
    return 0;
    }

// End of the file.
