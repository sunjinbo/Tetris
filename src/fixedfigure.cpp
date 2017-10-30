/* ====================================================================
 * File: fixedfigure.cpp
 * Created: 12/24/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "fixedfigure.h"
#include "figureobserver.h"
#include "scene.h"
#include "grid.h"

// Creates a new fixed figure object, and leaves
// if there is insufficient memory to create it.
CFixedFigure* CFixedFigure::NewL( 
    TScene& aScene, MFigureObserver& aObserver )
    {
    CFixedFigure* self = new( ELeave ) CFixedFigure( aScene, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// merge the other one figure
void CFixedFigure::MergeL( CFigureBase& aFixedFigure )
    {
    // merge
    TGrid* grid( NULL );
    TInt count( aFixedFigure.CountComponentGrids() );
    for ( TInt i = 0; i < count; ++i )
        {
        grid = aFixedFigure.ComponentGrid( i );
        iGridList->AppendL( *grid );
        }
    iObserver.StateChangedL( EFixedFigureMerged );

    // release
    ReleaseL();

    // over test
    OverTestL();
    }

// Constructor.
CFixedFigure::CFixedFigure( TScene& aScene, MFigureObserver& aObserver )
    : CFigureBase( aScene, aObserver )
    { // no implementation required 
    }

// Completes construction of the CFixedFigure object.
void CFixedFigure::ConstructL()
    {
    CFigureBase::ConstructL();
    }

// Release some lines in which fill with grids.
void CFixedFigure::ReleaseL()
    {
    TInt delLineNumber( 0 );
    TGrid* grid( NULL );
    TInt temp = 0;
    for ( TInt lineNumber = 0; lineNumber < iScene.Height(); ++lineNumber )
        {
        temp = 0;
        for ( TInt i = 0; i < iGridList->Count(); ++i )
            {
            grid = &iGridList->At( i );
            if ( grid->iY == lineNumber )
                {
                temp += 1;
                }
            }

        if ( temp == iScene.Width() )
            {
            for ( TInt i = 0; i < iGridList->Count(); ++i )
                {
                grid = &iGridList->At( i );
                if ( grid->iY == lineNumber )
                    {
                    iGridList->Delete( i );
                    iGridList->Compress();
                    i -= 1;
                    }
                else if ( grid->iY > lineNumber )
                    {
                    grid->iY -= 1;
                    }
                }
            delLineNumber += 1;
            lineNumber = 0;
            }
        }

    switch( delLineNumber )
        {
        case 1:
            iObserver.StateChangedL( EFixedFigureReleaseOneLine );
            break;
        case 2:
            iObserver.StateChangedL( EFixedFigureReleaseTwoLines );
            break;
        case 3:
            iObserver.StateChangedL( EFixedFigureReleaseThreeLines );
            break;
        case 4:
            iObserver.StateChangedL( EFixedFigureReleaseFourLines );
            break;
        default:
            break;
        }
    }

// it uesd to evaluate whether or not this figure get to the top of scene.
void CFixedFigure::OverTestL()
    {
    TInt maxHeight( 0 );
    TGrid* grid( NULL );
    for ( TInt i = 0; i < iGridList->Count(); ++i )
        {
        grid = &iGridList->At( i );
        if ( maxHeight < grid->iY )
            {
            maxHeight = grid->iY;
            }
        }

    if ( maxHeight >= iScene.Height() - 1 )
        {
        iObserver.StateChangedL( EFixedFigureOverflowed );
        }
    }

// End of the file.
