/* ====================================================================
 * File: Tetris.cpp
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <eikstart.h> // EikStart
#include "TetrisApplication.h" // CTetrisApplication


// Create an application, and return a pointer to it
CApaApplication* NewApplication()
	{
	return new CTetrisApplication;
	}

// Application entry
TInt E32Main()
	{
       return EikStart::RunApplication( NewApplication );
	}

// End of the file.
