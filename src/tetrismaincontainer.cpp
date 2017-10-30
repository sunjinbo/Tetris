/* ====================================================================
 * File: tetrismaincontainer.cpp
 * Created: 01/09/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CleanupStack
#include <fbs.h> // CFbsBitmap
#include <bitdev.h> // CFbsBitmapDevice
#include <bitstd.h> // CFbsBitGc
#include <e32cmn.h>
#include <stringloader.h>  // StringLoader
#include <eikenv.h> // CEikonEnv - iEikonEnv
#include <tetris.rsg>

#include "tetrismaincontainer.h"
#include "tetrisgameengine.h" // CTetrisGameEngine
#include "grid.h" // TGrid


// CONSTANTS
const TInt KPromptMaxChars = 12;

const TInt KStatusPanelItemOrderOne = 0;
const TInt KStatusPanelItemOrderTwo = 1;
const TInt KStatusPanelItemOrderThree = 2;
const TInt KStatusPanelItemOrderFour = 3;
const TInt KStatusPanelItemTotal = 4;
// Two stage constructor.
CTetrisMainContainer* CTetrisMainContainer::NewL( const TRect& aRect, CTetrisGameEngine& aEngine ) 
    {
    CTetrisMainContainer* self = new( ELeave ) CTetrisMainContainer( aEngine );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// C++ destructor.
CTetrisMainContainer::~CTetrisMainContainer()
    {
    delete iOffScrnBmp; 
    delete iOffScrnBmpDevice; 
    delete iOffScrnContext; 
    }

// Update the primary screen
void CTetrisMainContainer::UpdatePrimaryScreen()
    {
    // redraw framework of primary screen.
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->Clear( TRect( iPrimarySceneOrigin, iPrimarySceneSize ) );
    iOffScrnContext->DrawRect( TRect( iPrimarySceneOrigin, iPrimarySceneSize ) );

    // redraw the inner details of primary screen.
    // iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::EForwardDiagonalHatchBrush );
    TPoint gridOrigin;
    TGrid* grid( NULL );
    TInt count( iEngine.CountComponentGridsOnPrimaryScreen() );
    for ( TInt i = 0; i < count; ++i )
        {
        grid = iEngine.ComponentGridOnPrimaryScreen( i );
        if ( grid )
            {
            if ( grid->iY <= iEngine.PrimarySceneHeight() - 1 )
                {
                gridOrigin.iX = iPrimarySceneOrigin.iX + 
                    grid->iX * iPrimarySceneGridSize.iWidth;
                gridOrigin.iY = iPrimarySceneOrigin.iY + 
                    ( iEngine.PrimarySceneHeight() - 1 - grid->iY ) * iPrimarySceneGridSize.iHeight;
                iOffScrnContext->DrawRect( TRect( gridOrigin, iPrimarySceneGridSize ) );
                }
            }
        }
    // Draws the control, with low priority
    DrawDeferred();
    }

// Update the secondary screen
void CTetrisMainContainer::UpdateSecondaryScreenL()
    {
    // redraw framework of secondary screen.
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->Clear( TRect( iSecondarySceneOrigin, iSecondarySceneSize ) );

    // redraw the inner details of secondary screen.
    // iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::EForwardDiagonalHatchBrush );
    TPoint gridOrigin;
    TGrid* grid( NULL );
    TInt count( iEngine.CountComponentGridsOnSecondaryScreen() );
    for ( TInt i = 0; i < count; ++i )
        {
        grid = iEngine.ComponentGridOnSecondaryScreen( i );
        if ( grid )
            {
            if ( grid->iY <= iEngine.SecondarySceneHeight() - 1 )
                {
                gridOrigin.iX = iSecondarySceneOrigin.iX + 
                    grid->iX * iSecondarySceneGridSize.iWidth;
                gridOrigin.iY = iSecondarySceneOrigin.iY + 
                    ( iEngine.SecondarySceneHeight() - 1 - grid->iY ) * iSecondarySceneGridSize.iHeight;
                iOffScrnContext->DrawRect( TRect( gridOrigin, iSecondarySceneGridSize ) );
                }
            }
        }
    // Draws the control, with low priority
    DrawDeferred();
    }

// Update the level of this game
void CTetrisMainContainer::UpdateLevelPaneL()
    {
    // clears level panel.
    TPoint point( iStatusPanelOrigin.iX, 
        iStatusPanelOrigin.iY + iStatusPanelItemSize.iHeight * KStatusPanelItemOrderOne );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->Clear( TRect( point, iStatusPanelItemSize ) );

    // gets text from resource.
    TBuf<KPromptMaxChars> prompt;
    HBufC* levelString = StringLoader::LoadLC( R_STR_LEVEL );
    prompt.Format( *levelString, iEngine.Level() );
    CleanupStack::PopAndDestroy( levelString );

    // Draws text on screen memory buffer
    const CFont* font = iEikonEnv->DenseFont();
    iOffScrnContext->UseFont( font );
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    point.iY = point.iY + font->FontMaxHeight();
    iOffScrnContext->DrawText( prompt, point );

    // Draws the control, with low priority
    DrawDeferred();
    }

// Update the line of this game
void CTetrisMainContainer::UpdateLinePaneL()
    {
    // clears line panel.
    TPoint point( iStatusPanelOrigin.iX, 
        iStatusPanelOrigin.iY + iStatusPanelItemSize.iHeight * KStatusPanelItemOrderTwo );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->Clear( TRect( point, iStatusPanelItemSize ) );

    // gets text from resource.
    TBuf<KPromptMaxChars> prompt;
    HBufC* lineString = StringLoader::LoadLC( R_STR_LINE );
    prompt.Format( *lineString, iEngine.Line() );
    CleanupStack::PopAndDestroy( lineString );

    // Draws text on screen memory buffer
    const CFont* font = iEikonEnv->DenseFont();
    iOffScrnContext->UseFont( font );
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    point.iY = point.iY + font->FontMaxHeight();
    iOffScrnContext->DrawText( prompt, point );

    // Draws the control, with low priority
    DrawDeferred();
    }

// Update the score of this game
void CTetrisMainContainer::UpdateScorePaneL()
    {
    // clears score panel.
    TPoint point( iStatusPanelOrigin.iX, 
        iStatusPanelOrigin.iY + iStatusPanelItemSize.iHeight * KStatusPanelItemOrderThree );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->Clear( TRect( point, iStatusPanelItemSize ) );

    // gets text from resource.
    TBuf<KPromptMaxChars> prompt;
    HBufC* scoreString = StringLoader::LoadLC( R_STR_SCORE );
    prompt.Format( *scoreString, iEngine.Score() );
    CleanupStack::PopAndDestroy( scoreString );

    // Draws text on screen memory buffer
    const CFont* font = iEikonEnv->DenseFont();
    iOffScrnContext->UseFont( font );
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    point.iY = point.iY + font->FontMaxHeight();
    iOffScrnContext->DrawText( prompt, point );

    // Draws the control, with low priority
    //Window().Invalidate( TRect( point, iStatusPanelItemSize ) );
    DrawDeferred();
    }

// Update the level of this game
void CTetrisMainContainer::UpdateLifePaneL()
    {
    // clears life panel.
    TPoint point( iStatusPanelOrigin.iX, 
        iStatusPanelOrigin.iY + iStatusPanelItemSize.iHeight * KStatusPanelItemOrderFour );
    iOffScrnContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iOffScrnContext->SetBrushColor( KRgbWhite );
    iOffScrnContext->Clear( TRect( point, iStatusPanelItemSize ) );

    // gets text from resource.
    TBuf<KPromptMaxChars> prompt;
    HBufC* lifeString = StringLoader::LoadLC( R_STR_LIFE );
    prompt.Format( *lifeString, iEngine.Life() );
    CleanupStack::PopAndDestroy( lifeString );

    // Draws text on screen memory buffer
    const CFont* font = iEikonEnv->DenseFont();
    iOffScrnContext->UseFont( font );
    iOffScrnContext->SetPenColor( KRgbBlack );
    iOffScrnContext->SetPenStyle( CGraphicsContext::ESolidPen );
    point.iY = point.iY + font->FontMaxHeight();
    iOffScrnContext->DrawText( prompt, point );

    // Draws the control, with low priority
    //Window().Invalidate( TRect( point, iStatusPanelItemSize ) );
    DrawDeferred();
    }

// C++ default constructor.
CTetrisMainContainer::CTetrisMainContainer(  CTetrisGameEngine& aEngine  )
    : iEngine( aEngine )
    {
    }

// Symbian second phase constructor.
void CTetrisMainContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect( aRect );

    // creates double buffer memory.
    iOffScrnBmp = new ( ELeave ) CFbsBitmap; 
    User::LeaveIfError( iOffScrnBmp->Create( Size(), EColor4K ) ); 
    iOffScrnBmpDevice = CFbsBitmapDevice::NewL( iOffScrnBmp ); 
    User::LeaveIfError( iOffScrnBmpDevice->CreateContext( iOffScrnContext ) );
 
    // gets primary scene's some position or sizeinfomation.
    iPrimarySceneGridSize.iHeight = 
        aRect.Height() / ( iEngine.PrimarySceneHeight() + 2 ) ;
    iPrimarySceneGridSize.iWidth = iPrimarySceneGridSize.iHeight;
    iPrimarySceneOrigin.iX = iPrimarySceneGridSize.iWidth;
    iPrimarySceneOrigin.iY = iPrimarySceneGridSize.iHeight;
 
    iPrimarySceneSize.iHeight = 
        iPrimarySceneGridSize.iHeight * iEngine.PrimarySceneHeight();
   iPrimarySceneSize.iWidth = 
        iPrimarySceneGridSize.iWidth * iEngine.PrimarySceneWidth();

    // gets secondary scene's some position or size infomation.
    iSecondarySceneOrigin.iX = iPrimarySceneOrigin.iX + 
        iPrimarySceneGridSize.iWidth * ( iEngine.PrimarySceneWidth() + 1 );
    iSecondarySceneOrigin.iY = iPrimarySceneOrigin.iY;
    
    iSecondarySceneSize.iHeight = iPrimarySceneSize.iHeight  / 2;
    iSecondarySceneSize.iWidth = aRect.Width() - 
        iPrimarySceneGridSize.iWidth * ( iEngine.PrimarySceneWidth() + 3 );
    
    iSecondarySceneGridSize.iHeight = 
        iSecondarySceneSize.iHeight / iEngine.SecondarySceneHeight();
    iSecondarySceneGridSize.iWidth = iSecondarySceneGridSize.iHeight;

    // gets status panel's some position or size infomation.
    iStatusPanelOrigin.iX = iSecondarySceneOrigin.iX;
    iStatusPanelOrigin.iY = iPrimarySceneOrigin.iY + 
        iPrimarySceneSize.iHeight  / 2;

    iStatusPanelItemSize.iHeight = iSecondarySceneSize.iHeight / KStatusPanelItemTotal;
    iStatusPanelItemSize.iWidth = iSecondarySceneSize.iWidth;

    // update the full screen.
    UpdatePrimaryScreen();
    UpdateSecondaryScreenL();
    UpdateLevelPaneL();
    UpdateLinePaneL();
    UpdateScorePaneL();
    UpdateLifePaneL();
    
    //Sets the control as ready to be drawn.
    //The application should call this function on all controls 
    // that are not components in a compound control.
    ActivateL();
    }

// Gets the number of controls contained in a compound control.
TInt CTetrisMainContainer::CountComponentControls() const
    {
    return 0;
    }

// Gets an indexed component of a compound control.
CCoeControl* CTetrisMainContainer::ComponentControl( TInt /* aIndex */ ) const
    {
    return NULL;
    }

// Draws the control.
void CTetrisMainContainer::Draw( const TRect& /* aRect */ ) const
    {
    CWindowGc& gc = SystemGc(); 
    gc.BitBlt( TPoint( 0, 0 ), iOffScrnBmp );
    }

// End of this file.
