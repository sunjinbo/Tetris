/* ====================================================================
 * File: TetrisApplication.cpp
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "tetrisapplication.h"
#include "tetrisdocument.h"

// CONSTANTS
// UID for the application, this should correspond to 
// the uid defined in the mmp file
static const TUid KUidTetrisApp = { 0x0E0F3E4F };

// Create an Tetris document, and return a pointer to it
CApaDocument* CTetrisApplication::CreateDocumentL()
    {
    CApaDocument* document = CTetrisDocument::NewL(*this);
    return document;
    }

// Return the UID for the Tetris application
TUid CTetrisApplication::AppDllUid() const
    {
    return KUidTetrisApp;
    }

// End of the file.
