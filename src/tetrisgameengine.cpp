/* ====================================================================
 * File: tetrisgameengine.cpp
 * Created: 12/21/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <e32base.h> // CleanupStack
#include <fbs.h> // CFbsBitmap
#include <bitdev.h> // CFbsBitmapDevice
#include <bitstd.h> // CFbsBitGc

#include "tetrisgameengine.h" // CTetrisGameEngine
#include "scene.h" // TScene
#include "fixedfigure.h" // CFixedFigure
#include "nextremovablefigure.h" // CNextRemovableFigure
#include "removablefigure.h" // CRemovableFigure
#include "animationfigure.h"
#include "grid.h"


// CONSTANTS
const TInt KPrimarySceneWidth = 10;
const TInt KPrimarySceneHeight = 18;
const TInt KSecondarySceneWidth = 4;
const TInt KSecondarySceneHeight = 4;

// Standard construction sequence
CTetrisGameEngine* CTetrisGameEngine::NewL( MEngineObserver& aObserver )
    {
    CTetrisGameEngine* self = new ( ELeave ) CTetrisGameEngine( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// Destructor
CTetrisGameEngine::~CTetrisGameEngine()
    {
    delete iScorekeeper;
    delete iPrimaryScene;
    delete iSecondaryScene;
    delete iRemovableFigure;
    delete iNextRemovableFigure;
    delete iAnimationFigure;
    delete iFixedFigure;
    }

// Handle all kinds of commands from CTetrisAppUi
TBool CTetrisGameEngine::HandleCommandL( TEngineCommands aNewCommand )
    {
    if ( iPlayingAnimation )
        {
        return EFalse;
        }
    
    switch( aNewCommand )
        {
        case EEngineStart:
            {
            StartL();
            }
            break;
        case EEngineStop:
            {
            Stop();
            }
            break;
        case EEngineRestart:
            {
            Stop();
            StartL();
            }
            break;
        case EEnginePause:
            {
            iRemovableFigure->Stop();
            }
            break;
        case EEngineResume:
            {
            iRemovableFigure->Resume();
            }
            break;
        case EEngineLeftKey:
            {
            iRemovableFigure->Left();
            }
            break;
        case EEngineRightKey:
            {
            iRemovableFigure->Right();
            }
            break;       
        case EEngineUpKey:
            {
            iRemovableFigure->Rotate();
            }
            break;
        case EEngineDownKey:
            {
            iRemovableFigure->DropL();    
            }
            break;
        default:
            break;
        }

    return ETrue;
    }

// Gets the number of grids contained on primary screen.
TInt CTetrisGameEngine::CountComponentGridsOnPrimaryScreen() const
    {
    TInt countTotal( 0 );
    TInt countFixedFigure( 0 );
    TInt countRemovableFigure( 0 );
    TInt countAnimationFigure( 0 );
    
    // calculate the number of grids in each component.
    if ( iFixedFigure )
        {
        countFixedFigure = iFixedFigure->CountComponentGrids();
        }

    if ( iRemovableFigure )
        {
        countRemovableFigure = iRemovableFigure->CountComponentGrids();
        }
         
    if ( iAnimationFigure )
        {
        countAnimationFigure = iAnimationFigure->CountComponentGrids();
        }
    // gets the total number according to animation status.
    if ( iPlayingAnimation )
        {
        countTotal = countAnimationFigure;
        }
    else
        {
        countTotal = countFixedFigure + countRemovableFigure;
        }
 
    return countTotal;
    }

// Gets an indexed component  on primary screen.
TGrid* CTetrisGameEngine::ComponentGridOnPrimaryScreen( TInt aIndex )
    {
    TGrid* result( NULL );
    // gets the grid according to animation status.
    if ( iPlayingAnimation )
        {
        TInt countAnimationFigure( iAnimationFigure->CountComponentGrids() );
        result = iAnimationFigure->ComponentGrid( aIndex );
        }
    else
        {
        TInt countFixedFigure( iFixedFigure->CountComponentGrids() );
        TInt countRemovableFigure( iRemovableFigure->CountComponentGrids() );
        if ( aIndex < countFixedFigure )
            {
            result = iFixedFigure->ComponentGrid( aIndex );
            }
        else
            {
            result = iRemovableFigure->ComponentGrid( aIndex - countFixedFigure );
            }
        }
    return result;
    }

// Gets the number of grids contained on secondary screen.
TInt CTetrisGameEngine::CountComponentGridsOnSecondaryScreen() const
    {
    TInt countNextRemovableFigure( 0 );
    if ( iNextRemovableFigure )
        {
        countNextRemovableFigure = iNextRemovableFigure->CountComponentGrids();
        }
    return countNextRemovableFigure;
    }

// Gets an indexed component on secondary screen.
TGrid* CTetrisGameEngine::ComponentGridOnSecondaryScreen( TInt aIndex )
    {
    TGrid* result( NULL );
    if ( iNextRemovableFigure )
        {
        TInt countNextRemovableFigure( iNextRemovableFigure->CountComponentGrids() );
        if ( aIndex >= 0 && aIndex < countNextRemovableFigure )
            {
            result = iNextRemovableFigure->ComponentGrid( aIndex );
            }
        }
    return result;
    }

// gets grid number on primary screen by vertical
TInt CTetrisGameEngine::PrimarySceneWidth() const
    {
    return iPrimaryScene->Width();
    }
    
// gets grid number on primary screen by horizontal
TInt CTetrisGameEngine::PrimarySceneHeight() const
    {
    return iPrimaryScene->Height();
    }
    
// gets grid number on secondary screen by vertical
TInt CTetrisGameEngine::SecondarySceneWidth() const
    {
    return iSecondaryScene->Width();
    }
    
// gets grid number on secondary screen by horizontal
TInt CTetrisGameEngine::SecondarySceneHeight() const
    {
    return iSecondaryScene->Height();
    }

// Gets the current Level.
TInt CTetrisGameEngine::Level() const
    {
    return iScorekeeper->Level();
    }
    
// Gets the line number which has been be removed in this game.
TInt CTetrisGameEngine::Line() const
    {
    return iScorekeeper->Line();
    }

// Gets the total score.
TInt CTetrisGameEngine::Score() const
    {
    return iScorekeeper->Score();
    }

// Gets the life number in this game.
TInt CTetrisGameEngine::Life() const
    {
    return iScorekeeper->Life();
    }

// Handle all kinds of notification from Figure
void CTetrisGameEngine::StateChangedL( TFigureState aNewState )
    {
    switch( aNewState )
        {
        case EFixedFigureReleaseOneLine:
            {
            iObserver.StateChangedL( EEnginePrimaryScreenUpdated );
            iScorekeeper->DeleteLines( 1 ); 
            }
            break;
   
        case EFixedFigureReleaseTwoLines:
            {
            iObserver.StateChangedL( EEnginePrimaryScreenUpdated );
            iScorekeeper->DeleteLines( 2 ); 
            }
            break;
 
        case EFixedFigureReleaseThreeLines:
            {
            iObserver.StateChangedL( EEnginePrimaryScreenUpdated );
            iScorekeeper->DeleteLines( 3 ); 
            }
            break;
            
        case EFixedFigureReleaseFourLines:
            {
            iObserver.StateChangedL( EEnginePrimaryScreenUpdated );
            iScorekeeper->DeleteLines( 4 ); 
            }
            break;

        case ENextRemovableFigureUpdated:
            {
            iObserver.StateChangedL( EEngineSecondaryScreenUpdated );
            }
            break;

        case EFixedFigureMerged:
            {
            iRemovableFigure->Stop();
            iRemovableFigure->ChangeFigueL( *iNextRemovableFigure );
            iRemovableFigure->StartL( iScorekeeper->Level() );
            iNextRemovableFigure->ChangeFigueL();
            iObserver.StateChangedL( EEngineSecondaryScreenUpdated );
            }
            break;

        case EFixedFigureOverflowed:
            {
            iRemovableFigure->Stop();
            iAnimationFigure->PlayL( *iFixedFigure );
            }
            break;
  
        case ERemovableFigureUpdated: // fall through
        case ERemovableFigureLeftMoved: // fall through
        case ERemovableFigureRightMoved: // fall through
        case ERemovableFigureRotated: // fall through
        case ERomovableFigureDropped: // fall through
        case EAnimationFigureUpdated: // fall through
            {
            iObserver.StateChangedL( EEnginePrimaryScreenUpdated );
            }
            break;

        case ERomovableFigureDropEnded:
            {
            iFixedFigure->MergeL( *iRemovableFigure );
            }
            break;
        
        case EAnimationFigureStarted:
            {
            iPlayingAnimation = ETrue;
            }
            break;

        case EAnimationFigureEnded:
            {
            iPlayingAnimation = EFalse;
            iScorekeeper->KillLife();
            }
            break;
            
        default:
            break;
        }
    }

// Handle all kinds of notification from Scorekeeper
void CTetrisGameEngine::StateChangedL( TScorekeeperState aNewState )
    {
    if ( iPlayingAnimation )
        return;

    switch( aNewState )
        {
        case EScorekeeperLevelUpdated:
            {
            iObserver.StateChangedL( EEngineLevelUpdated );
            }
            break;
            
        case EScorekeeperLineUpdated:
            {
            iObserver.StateChangedL( EEngineLineUpdated );
            }
            break;

        case EScorekeeperScoreUpdated:
            {
            iObserver.StateChangedL( EEngineScoreUpdated );
            }
            break;

        case EScorekeeperLifeUpdated:
            {
            iObserver.StateChangedL( EEngineLifeUpdated );
            if ( iScorekeeper->Life() )
                {
                iFixedFigure->Reset();
                iRemovableFigure->Stop();
                iRemovableFigure->ChangeFigueL( *iNextRemovableFigure );
                iRemovableFigure->StartL( iScorekeeper->Level() );
                iNextRemovableFigure->ChangeFigueL();
                iObserver.StateChangedL( EEngineSecondaryScreenUpdated );
                }
            else
                {
                Stop();
                iObserver.StateChangedL( EEngineGameOver );
                }
            }
            break;

        case EScorekeeperAllLifeOver:
            break;

        default:
            break;
        }
    }

 // Constructor
CTetrisGameEngine::CTetrisGameEngine( MEngineObserver& aObserver )
    : iObserver( aObserver )
    { // no implementation required       
    }

// Completes construction of the CTetrisGameEngine object
void CTetrisGameEngine::ConstructL( )
    {
    iScorekeeper = CScorekeeper::NewL( *this );
    iPrimaryScene = 
        new( ELeave ) TScene( KPrimarySceneHeight,  KPrimarySceneWidth );
    iSecondaryScene = 
        new( ELeave ) TScene( KSecondarySceneHeight,  KSecondarySceneWidth );
    iFixedFigure = CFixedFigure::NewL( *iPrimaryScene, *this );
    iNextRemovableFigure = CNextRemovableFigure::NewL( *iSecondaryScene, *this );
    iRemovableFigure = CRemovableFigure::NewL( *iPrimaryScene, *this );
    iAnimationFigure = CAnimationFigure::NewL( *iPrimaryScene, *this );
    iPlayingAnimation = EFalse;
    }

void CTetrisGameEngine::StartL()
    {
    iNextRemovableFigure->ChangeFigueL();
    iRemovableFigure->ChangeFigueL( *iNextRemovableFigure );
    iRemovableFigure->StartL( iScorekeeper->Level() );
    iNextRemovableFigure->ChangeFigueL();
    iObserver.StateChangedL( EEngineSecondaryScreenUpdated );
    }

void CTetrisGameEngine::Stop()
    {
    iNextRemovableFigure->Reset();
    iRemovableFigure->Reset();
    iFixedFigure->Reset();
    iAnimationFigure->Reset();
    iScorekeeper->Reset();
    iObserver.StateChangedL( EEngineAllUpdated );
    }

// End of the file.
