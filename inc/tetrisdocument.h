/* ====================================================================
 * File: TetrisDocument.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef __TETRIS_DOCUMENT_H__
#define __TETRIS_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CTetrisAppUi;
class CEikApplication;


/*! 
  @class CTetrisDocument
  
  @discussion An instance of class CTetrisDocument is the Document part of the AVKON
  application framework for the Tetris example application
  */
class CTetrisDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CTetrisDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CTetrisDocument
  */
    static CTetrisDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CTetrisDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CTetrisDocument
  */
    static CTetrisDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CTetrisDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTetrisDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CTetrisAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CTetrisDocument object
  */
    void ConstructL();

/*!
  @function CTetrisDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CTetrisDocument(CEikApplication& aApp);

    };


#endif // __TETRIS_DOCUMENT_H__
