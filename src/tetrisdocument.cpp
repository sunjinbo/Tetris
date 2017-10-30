/* ====================================================================
 * File: TetrisDocument.cpp
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#include "tetrisAppUi.h"
#include "tetrisDocument.h"

// Standard Symbian OS construction sequence
CTetrisDocument* CTetrisDocument::NewL(CEikApplication& aApp)
    {
    CTetrisDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CTetrisDocument* CTetrisDocument::NewLC(CEikApplication& aApp)
    {
    CTetrisDocument* self = new (ELeave) CTetrisDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CTetrisDocument::ConstructL()
    { // no implementation required	
    }    

CTetrisDocument::CTetrisDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    { // no implementation required
    }

CTetrisDocument::~CTetrisDocument()
    { // no implementation required
    }

CEikAppUi* CTetrisDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CTetrisAppUi;
    return appUi;
    }

// End of the file.
