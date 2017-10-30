/* ====================================================================
 * File: scene.cpp
 * Created: 12/21/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "scene.h"
#include "figurebase.h"
#include "fixedfigure.h"
#include "removablefigure.h"
#include "nextremovablefigure.h"

// Constructor
TScene::TScene( TInt aHeight, TInt aWidth )
    : iHeight( aHeight ), iWidth( aWidth )
    {
    iFigureList.Reset();
    }

// C++ destructor.
TScene::~TScene()
    {
    iFigureList.Close();
    }

// Gets the height of the scene.
TInt TScene::Height() const
    {
    return iHeight;
    }

// Gets the width of the scene.
TInt TScene::Width() const
    {
    return iWidth;
    }

// Add the pointer of  a figure to this scene. 
void TScene::AddFigure( const CFigureBase* aFigure )
    {
    iFigureList.Append( aFigure );
    }

// Remove the pointer of a figure from this scene.
void TScene::RemoveFigure( const CFigureBase* aFigure )
    {
    iFigureList.Remove( iFigureList.Find( aFigure ) );
    }

// Gets the number of CFixedFigure* in the scene.
TInt TScene::Count() const
    {
    return iFigureList.Count();
    }

// Gets a pointer of CFixedFigure located at a specified position within scene
const CFigureBase* TScene::At( TInt anIndex ) const
    {
    const CFigureBase* result( NULL );
    if ( anIndex >= 0 && anIndex < iFigureList.Count() )
        {
        result = iFigureList[anIndex];;
        }
    return result;
    }

// End of the file.
