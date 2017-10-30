/* ====================================================================
 * File: nextremovablefigure.cpp
 * Created: 12/28/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CleanupStack
#include <e32std.h> // TTime
#include <e32math.h> // Math arithmetic

#include "nextremovablefigure.h"
#include "scene.h"
#include "grid.h"

// CONSTANTS
static const TInt KFigureKindNumber = 7; // I, J, L, O, S, T, Z
static const TInt KFigureDirectionNumber = 4; // S, N, E, W
// The seven one-sided tetrominoes in their Tetris Worlds colors. 
// Top row, left to right: I, J, L, O. Bottom row: S, T, Z.
// #I-type figure template
static const TInt KFigureI[4][4] =
    {
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 }
    };

// #J-type figure template
static const TInt KFigureJ[4][4] =
    {
        { 0, 0, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    };
 
// #L-type figure template
static const TInt KFigureL[4][4] =
    {
        { 0, 1, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    };

// #O-type figure template
static const TInt KFigureO[4][4] =
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    };
// #S-type figure template
static const TInt KFigureS[4][4] =
    {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 1 },
        { 0, 1, 1, 0 },
        { 0, 0, 0, 0 }
    };

// #T-type figure template
static const TInt KFigureT[4][4] =
    {
        { 0, 0, 1, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 0 }
    };
// #Z-type figure template
static const TInt KFigureZ[4][4] =
    {
        { 0, 0, 0, 0 },
        { 0, 1, 1, 0 },
        { 0, 0, 1, 1 },
        { 0, 0, 0, 0 }
    };

// Creates a new next removable figure object
CNextRemovableFigure* CNextRemovableFigure::NewL( 
        TScene& aScene, MFigureObserver& aObserver )
    {
    CNextRemovableFigure* self = 
        new( ELeave ) CNextRemovableFigure( aScene, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// gets a new figues
void CNextRemovableFigure::ChangeFigueL()
    {
    RandomFigureL();
    RandomDirection();
    RandomColor();
    }

// C++ Constructor
CNextRemovableFigure::CNextRemovableFigure( 
    TScene& aScene, MFigureObserver& aObserver )
    : CFigureBase( aScene, aObserver )
    { // no implementation required 
    }

// Completes construction
void CNextRemovableFigure::ConstructL()
    {
    CFigureBase::ConstructL();
    }

// sets a figure type in random.
void CNextRemovableFigure::RandomFigureL()
    {
    const TInt* removableFigure( NULL );
    TTime time;
    time.UniversalTime();
    TInt64 randSeed( time.Int64() );
    TInt rand( Math::Rand( randSeed ) % KFigureKindNumber );
    
    // get type according to the value of number.
    switch( rand )
        {
        case 0:
            removableFigure = &KFigureI[0][0];
            break;
        case 1:
            removableFigure = &KFigureJ[0][0];
            break;
        case 2:
            removableFigure = &KFigureL[0][0];
            break;
        case 3:
            removableFigure = &KFigureO[0][0];
            break;
        case 4:
            removableFigure = &KFigureS[0][0];
            break;
        case 5:
            removableFigure = &KFigureT[0][0];
            break;
        case 6:
            removableFigure = &KFigureZ[0][0];
            break;
        default:
            break;
        }
    // making figures...
    TGrid* grid( NULL );
    iGridList->Reset();
    for( TInt i = 0; i < iScene.Width(); ++i )
        for( TInt j = 0; j < iScene.Width(); ++j )
            {
            if ( *( removableFigure + iScene.Width() * i + j ) )
                {
                grid = new( ELeave ) TGrid( j, i, KRgbBlack );
                CleanupStack::PushL( grid );
                iGridList->AppendL( *grid );
                CleanupStack::PopAndDestroy();
                grid = NULL;
                }
            }
    }

// sets a direction in random.
void CNextRemovableFigure::RandomDirection()
    {
    const TInt* result( NULL );
    TTime time;
    time.UniversalTime();
    TInt64 randSeed( time.Int64() );
    TInt rand( Math::Rand( randSeed ) % KFigureDirectionNumber );
    
    // the times of rotate in terms of  random number.
    TGrid* thisGrid( NULL );
    for ( TInt i = 0; i < rand; ++i )
        {
        for ( TInt j = 0; j < iGridList->Count(); ++j )
            {
            thisGrid = &iGridList->At( j );
            thisGrid->iY = thisGrid->iX + thisGrid->iY;
            thisGrid->iX = thisGrid->iY - thisGrid->iX;
            thisGrid->iY = iScene.Height() - 1 - thisGrid->iY + thisGrid->iX;
            }
        }
    }

// sets a colour in random. 
void CNextRemovableFigure::RandomColor()
    {
    
    }

// End of the file.
