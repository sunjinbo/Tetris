/* ====================================================================
 * File: tetrismainview.cpp
 * Created: 01/09/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CleanupStack
#include "tetrismainview.h" // CTetrisMainView
#include "tetrismaincontainer.h" // CTetrisMainContainer

// Two stage constructor.
CTetrisMainView* CTetrisMainView::NewL( CTetrisGameEngine& aGameEngine )
    {
    CTetrisMainView* self = new( ELeave ) CTetrisMainView( aGameEngine );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// C++ destructor.
CTetrisMainView::~CTetrisMainView()
    {
    delete iMainContainer;
    }

// Update view according to the new state command.
void CTetrisMainView::UpdateViewL( TEngineState aNewState )
    {
    switch( aNewState )
        {
        case EEnginePrimaryScreenUpdated:
            iMainContainer->UpdatePrimaryScreen();
            break;
        case EEngineSecondaryScreenUpdated:
            iMainContainer->UpdateSecondaryScreenL();
            break;
        case EEngineLevelUpdated:
            iMainContainer->UpdateLevelPaneL();
            break;
        case EEngineLineUpdated:
            iMainContainer->UpdateLinePaneL();
            break;
        case EEngineScoreUpdated:
            iMainContainer->UpdateScorePaneL();
            break;
        case EEngineLifeUpdated:
            iMainContainer->UpdateLifePaneL();
            break;
        case EEngineAllUpdated:
            iMainContainer->UpdatePrimaryScreen();
            iMainContainer->UpdateSecondaryScreenL();
            iMainContainer->UpdateLevelPaneL();
            iMainContainer->UpdateLinePaneL();
            iMainContainer->UpdateScorePaneL();
            iMainContainer->UpdateLifePaneL();
            break;
        default:
            break;
        }
    }

// Get Uid of View
TUid CTetrisMainView::Id() const
    {
    //return TUid::Uid( KTetrisMainViewId );
    return KTetrisMainViewId;
    }

// C++ default constructor.
CTetrisMainView::CTetrisMainView( CTetrisGameEngine& aGameEngine ) 
    : iGameEngine ( aGameEngine )
    {
    }

// Symbian second-phase constructor.
void CTetrisMainView::ConstructL()
    {
    BaseConstructL( 0 );
    }

// Handles a view activation and passes the message of type
void CTetrisMainView::DoActivateL( const TVwsViewId& /* aPrevViewId */,
                                   TUid /* aCustomMessageId */,
                                   const TDesC8& /* aCustomMessage */ )
    {
    if ( !iMainContainer )
        {
        iMainContainer = CTetrisMainContainer::NewL( ClientRect(), iGameEngine );
        }
    iMainContainer->MakeVisible( ETrue );

    // This DrawNow line is needed for fixing the drawing problems when
    // this view is activated (in this situation whole screen can
    // remain blank if this function call is not done).
    iMainContainer->DrawNow();
    }

// View deactivation function intended for overriding by sub classes.
void CTetrisMainView::DoDeactivate()
    {
    if ( iMainContainer )
        {
        // Remove View1's container form controllStack
        //AppUi()->RemoveFromStack( iMainContainer );
        delete iMainContainer;
        iMainContainer = NULL;
        }
    }

// End of this file.
