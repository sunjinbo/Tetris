/* ====================================================================
 * File: tetrismaincontainer.h
 * Created: 01/09/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_TETRISMAINCONTAINER_H
#define C_TETRISMAINCONTAINER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CTetrisGameEngine;
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CTetrisMainView;


/**
* CTetrisMainContainer class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CTetrisMainContainer ) : public CCoeControl
    {
public:
    // Two stage constructor.
    static CTetrisMainContainer* NewL( const TRect& aRect, CTetrisGameEngine& aEngine );

    // C++ destructor.
    virtual ~CTetrisMainContainer();
    
    // update primary screen
    void UpdatePrimaryScreen();
    
    // update secondary screen
    void UpdateSecondaryScreenL();
    
    // update level pane
    void UpdateLevelPaneL();
    
    // update line pane
    void UpdateLinePaneL();
    
    // update score pane
    void UpdateScorePaneL();
    
    // update life pane
    void UpdateLifePaneL();

private:
    // C++ default constructor.
    CTetrisMainContainer( CTetrisGameEngine& aEngine );

    // Symbian second phase constructor.
    void ConstructL( const TRect& aRect );

private: // from base class CCoeControl
    // Gets the number of controls contained in a compound control.
    TInt CountComponentControls() const;
    
    // Gets an indexed component of a compound control.
    CCoeControl* ComponentControl( TInt aIndex ) const;

    // Draws the control.
    virtual void Draw( const TRect& aRect ) const;

private:
    
    // No own.
    CTetrisGameEngine& iEngine;
    
    //
    //CFbsBitmap& iBitmap;
    CFbsBitmap* iOffScrnBmp;
    
    CFbsBitmapDevice* iOffScrnBmpDevice;
    
    CFbsBitGc* iOffScrnContext;
    
    // The co-ordinates of the primary scene's top left hand corner.
    TPoint iPrimarySceneOrigin;
    
    // The co-ordinates of the secondary scene's top left hand corner.
    TPoint iSecondarySceneOrigin;
    
    // The co-ordinates of the status panel's top left hand corner.
    TPoint iStatusPanelOrigin;
    
    // The primary scene size.
    TSize iPrimarySceneSize;
    
    // The secondary scene size.
    TSize iSecondarySceneSize;
    
    // The status panel item size.
    TSize iStatusPanelItemSize;
    
    // The primary scene grid's width and height. 
    TSize iPrimarySceneGridSize;
    
    // The secondary scene grid's width and height.
    TSize iSecondarySceneGridSize;
    
    };

#endif // C_TETRISMAINCONTAINER_H

// End of this file.
