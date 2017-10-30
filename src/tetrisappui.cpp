/* ====================================================================
 * File: TetrisAppUi.cpp
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator All rights reserved
 * ==================================================================== */

// INCLUDES
#include <eikmenub.h>
#include <avkon.hrh>
#include <tetris.rsg>

#include "tetris.hrh"
#include "tetrisappui.h" // CTetrisAppUi
#include "tetrismainview.h" // CTetirsMainView
#include "tetrisgameengine.h" // CTetrisGameEngine
#include "tetris.pan"

// Two stage constructor and it will 
// be called by the application framework.
void CTetrisAppUi::ConstructL()
    {
    BaseConstructL();
    // creates member variable
    iGameEngine = CTetrisGameEngine::NewL( *this );
    iMainView = CTetrisMainView::NewL( *iGameEngine );
    AddViewL( iMainView );
    // default view is now main view
    SetDefaultViewL( *iMainView );
    }

// C++ default constructor.
CTetrisAppUi::CTetrisAppUi()                              
    { // no implementation required
    }

// C++ destructor
CTetrisAppUi::~CTetrisAppUi()
    {
    delete iGameEngine;
    }

// Handle any menu commands
void CTetrisAppUi::HandleCommandL( TInt aCommand )
    {
    switch(aCommand)
        {
        case EEikCmdExit: // fall through
        case EAknSoftkeyExit: // fall through
            Exit();
            break;
        case ETetrisStart:
            if ( iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineStart ) )
                {
                iEikonEnv->AppUiFactory()->MenuBar()->
                    SetMenuTitleResourceId( R_TETRIS_RUN_MENUBAR );
                }
            break;
        case ETetrisRestart:
            if ( iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineRestart ) )
                {
                iEikonEnv->AppUiFactory()->MenuBar()->
                    SetMenuTitleResourceId( R_TETRIS_RUN_MENUBAR );
                }
            break;
        case ETetrisStop:
            if ( iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineStop ) )
                {
                iEikonEnv->AppUiFactory()->MenuBar()->
                    SetMenuTitleResourceId( R_TETRIS_MENUBAR );
                }
            break;
        case ETetrisPause:
            if ( iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEnginePause ) )
                {
                iEikonEnv->AppUiFactory()->MenuBar()->
                    SetMenuTitleResourceId( R_TETRIS_PAUSE_MENUBAR );
                }
                break;
        case ETetrisResume:
            if ( iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineResume ) )
                {
                iEikonEnv->AppUiFactory()->MenuBar()->
                    SetMenuTitleResourceId( R_TETRIS_RUN_MENUBAR );
                }
            break;
        default:
            break;
        }
    }

// Handles key events
TKeyResponse CTetrisAppUi::HandleKeyEventL( 
    const TKeyEvent& aKeyEvent, TEventCode /* aType */ )                            
    {
    switch(aKeyEvent.iCode)
        {  
        case EKeyUpArrow: // ROTATE
            iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineUpKey );
            break;
        case EKeyDownArrow: // SPEEDUP DROP
            iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineDownKey );
            break;
        case EKeyLeftArrow: // TURN LEFT
            iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineLeftKey );
            break;
        case EKeyRightArrow: // TURN RIGHT
            iGameEngine->HandleCommandL( 
                CTetrisGameEngine::EEngineRightKey );
            break;
        default:
            break;
        }
    return EKeyWasConsumed;
    }

// Called when game engine state changes and observer needs to be notified.
void CTetrisAppUi::StateChangedL( TEngineState aNewState )
    {
    if ( aNewState == EEngineGameOver )
        {
        iEikonEnv->AppUiFactory()->MenuBar()->
            SetMenuTitleResourceId( R_TETRIS_MENUBAR );
        }
    else
        {
        iMainView->UpdateViewL( aNewState );    
        }
    }

// End of the file.
