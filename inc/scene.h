/* ====================================================================
 * File: scene.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef T_SCENE_H
#define T_SCENE_H

// INCLUDES
#include <e32cmn.h>
#include <e32def.h>

// FORWARD DECLARATIONS
class CFigureBase;
class CFixedFigure;
class CRemovableFigure;
class CNextRemovableFigure;

/**
* TScene class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( TScene )
    {
public:
    // Constructor
    TScene( TInt aHeight, TInt aWidth );
    
    ~TScene();
    
    // Gets the height of the scene.
    TInt Height() const;

    // Gets the width of the scene.
    TInt Width() const;

    // Add the pointer of  a figure to this scene. 
    void AddFigure( const CFigureBase* aFigure );
    
    // Remove the pointer of a figure from this scene.
    void RemoveFigure( const CFigureBase* aFigure );
    
    // Gets the number of CFixedFigure* in the scene.
    TInt Count() const;
    
    // Gets a pointer of CFixedFigure located at a specified position within scene
    const CFigureBase* At( TInt anIndex ) const;

private: // Members

    TInt iHeight;
    
    TInt iWidth;

    RArray<const CFigureBase*> iFigureList;
    
    };

#endif // T_SCENE_H

// End of the file.
