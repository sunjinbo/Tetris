/* ====================================================================
 * File: TetrisApplication.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef __TETRIS_APPLICATION_H__
#define __TETRIS_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CTetrisApplication
  
  @discussion An instance of CTetrisApplication is the application part of the AVKON
  application framework for the Tetris example application
  */
class CTetrisApplication : public CAknApplication
    {
public:  // from CAknApplication

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CAknApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __TETRIS_APPLICATION_H__
