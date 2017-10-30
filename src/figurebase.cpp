/* ====================================================================
 * File: fixedfigure.cpp
 * Created: 12/24/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "figurebase.h"
#include "figureobserver.h"
#include "scene.h"
#include "grid.h"

// CONSTANTS
const TInt KFigureBaseCranularity = 4;
const TInt KFigureBaseDefautOriginX = 0;
const TInt KFigureBaseDefautOriginY = 0;

// C++ destructor.
CFigureBase::~CFigureBase()
    {
    delete iGridList;
    delete iGrid;
    }

// Gets the number of grids contained in a compound figure.
TInt CFigureBase::CountComponentGrids() const
    {
    return iGridList->Count();
    }

// Gets an indexed component of a compound figure.
TGrid* CFigureBase::ComponentGrid( TInt aIndex )
    {
    delete iGrid;
    iGrid = NULL;
    TGrid* thisGrid( NULL );
    if ( aIndex >= 0 && aIndex < iGridList->Count() )
        {
        thisGrid = &( iGridList->At( aIndex ) );
        iGrid = new( ELeave ) TGrid( 
            thisGrid->iX + iOriginX, thisGrid->iY + iOriginY, 
            thisGrid->iColor );
        }
    return iGrid;
    }

// resets to default settings
void CFigureBase::Reset()
    {
    iGridList->Reset();
    iOriginX = KFigureBaseDefautOriginX;
    iOriginY = KFigureBaseDefautOriginY;
    }

// gets relative displacement Y-pos.
TInt CFigureBase::OriginX() const
    {
    return iOriginX;
    }

// gets relative displacement Y-pos.
TInt CFigureBase::OriginY() const
    {
    return iOriginY;
    }

// copies the contents from other one CFigureBase 
void CFigureBase::CopyL( CFigureBase& aFigure )
    {
    iOriginX = aFigure.iOriginX;
    iOriginY = aFigure.iOriginY;
    iGridList->Reset();
    CArrayFixFlat<TGrid>* gridList( aFigure.iGridList );
    for ( TInt i = 0; i < gridList->Count(); ++i )
        {
        iGridList->AppendL( gridList->At( i ) );
        }
    }

// Constructor.
CFigureBase::CFigureBase( TScene& aScene, MFigureObserver& aObserver )
    : iScene( aScene ), iObserver( aObserver )
    {
    iScene.AddFigure( this );
    }

// Completes construction of the CFixedFigure object.
void CFigureBase::ConstructL()
    {
    iGridList = 
        new( ELeave ) CArrayFixFlat<TGrid> ( KFigureBaseCranularity );
    }

// End of the file.
