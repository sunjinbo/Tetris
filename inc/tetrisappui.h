/* ====================================================================
 * File: tetrisappui.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_TETRISAPPUI_H
#define C_TETRISAPPUI_H

// INCLUDES
#include <aknviewappui.h>
#include "engineobserver.h" // MEngineObserver

// Forward reference
class CTetrisMainView;
class CTetrisGameEngine;

/**
* CTetrisAppUi class
*
* @since S60 3.1
*/
class CTetrisAppUi : public CAknViewAppUi,
                              public MEngineObserver
    {
public:
    // Two stage constructor and it will be called by the application framework
    void ConstructL();

    // C++ default constructor.
    CTetrisAppUi();

    // Destructor
    ~CTetrisAppUi();


private: // from base class CAknAppUi
    // Handle user menu selections
    void HandleCommandL(TInt aCommand);
    
    // Handles key events
    TKeyResponse HandleKeyEventL( const TKeyEvent& aKeyEvent, 
                                  TEventCode aType );

private: // from base class MEngineOberver
    //
    void StateChangedL( TEngineState aNewState );

private:
    // The tetirs game engine.
    // Own.
    CTetrisGameEngine* iGameEngine;
    
    // The main view of this game.
    // Own.
    CTetrisMainView* iMainView;
    };

#endif // C_TETRISAPPUI_H

// End of the file.


