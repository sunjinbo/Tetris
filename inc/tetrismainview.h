/* ====================================================================
 * File: tetrismainview.h
 * Created: 01/09/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_TETRISMAINVIEW_H
#define C_TETRISMAINVIEW_H

// INCLUDES
#include <aknview.h> // CAknView
#include "engineobserver.h"

// FORWARD DECLARATIONS
class CTetrisMainContainer;
class CTetrisGameEngine;

const TUid KTetrisMainViewId = { 1 };

/**
* CTetrisMainView class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CTetrisMainView ) : public CAknView
    {
public:
    // Two stage constructor.
    static CTetrisMainView* NewL( CTetrisGameEngine& aGameEngine );

    // C++ destructor.
    virtual ~CTetrisMainView();
    
    // Update view according to the new state command.
    void UpdateViewL( TEngineState aNewState );
    
public: // from base class CAknView
    // Get Uid of View
    TUid Id() const;

private:
    // C++ default constructor.
    CTetrisMainView( CTetrisGameEngine& aGameEngine );
    
    // Symbian second-phase constructor.
    void ConstructL();

protected:  // from base class CAknView
    // Handles a view activation and passes the message of type
    virtual void DoActivateL( const TVwsViewId& aPrevViewId,
                              TUid aCustomMessageId,
                              const TDesC8& aCustomMessage );
    
    // View deactivation function intended for overriding by sub classes.
    virtual void DoDeactivate();

private: // MEMBERS
    // Container control
    // Own.
    CTetrisMainContainer* iMainContainer;
    
    // 
    // No own.
    CTetrisGameEngine& iGameEngine;
    };

#endif // C_TETRISMAINVIEW_H

// End of this file.
