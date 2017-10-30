/* ====================================================================
 * File: tetrisgameengine.h
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_TETRISGAMEENGINE_H
#define C_TETRISGAMEENGINE_H

// INCLUDES
#include <e32def.h>
#include "figureobserver.h" // MFigureObserver
#include "engineobserver.h" // MEngineObserver
#include "scorekeeper.h"

// FORWARD DECLARATIONS
class TGrid;
class TScene;
class CFixedFigure;
class CNextRemovableFigure;
class CRemovableFigure;
class CAnimationFigure;

/**
* CTetrisGameEngine class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CTetrisGameEngine ) : public CBase,
                                                                    public MFigureObserver,
                                                                    public MScorekeeperObserver
    {
public:
    enum TEngineCommands // for handle all kinds of commands
        {
        EEngineStart = 1,
        EEngineStop,
        EEngineRestart,
        EEnginePause,
        EEngineResume,
        EEngineLeftKey,
        EEngineRightKey,
        EEngineUpKey,
        EEngineDownKey
        };

public:
    // Standard construction sequence
    static CTetrisGameEngine* NewL( MEngineObserver& aObserver );
    
    // 
    virtual ~CTetrisGameEngine();
    
    // handle all kinds of commands from CTetrisAppUi
    TBool HandleCommandL( TEngineCommands aNewCommand );

    // gets the number of grids contained on primary screen.
    TInt CountComponentGridsOnPrimaryScreen() const;
    
    // gets an indexed component  on primary screen.
    TGrid* ComponentGridOnPrimaryScreen( TInt aIndex );

    // gets the number of grids contained on secondary screen.
    TInt CountComponentGridsOnSecondaryScreen() const;
    
    // gets an indexed component on secondary screen.
    TGrid* ComponentGridOnSecondaryScreen( TInt aIndex );
    
    // gets grid number on primary scene by vertical
    TInt PrimarySceneWidth() const;
    
    // gets grid number on primary scene by horizontal
    TInt PrimarySceneHeight() const;
    
    // gets grid number on secondary scene by vertical
    TInt SecondarySceneWidth() const;
    
    // gets grid number on secondary scene by horizontal
    TInt SecondarySceneHeight() const;
    
    // gets the current Level.
    TInt Level() const;
    
    // gets the line number which has been be removed in this game.
    TInt Line() const;

    // gets the total score.
    TInt Score() const;
    
    // gets the life number in this game.
    TInt Life() const;
    
    
public: // from base class MFigureObserver
    virtual void StateChangedL( TFigureState aNewState ); 
   
public: // from base class MScorekeeperObserver
    virtual void StateChangedL( TScorekeeperState aNewState );
   
private:
    // Constructor
    CTetrisGameEngine( MEngineObserver& aObserver );
    
    // Completes construction of the CTetrisGameEngine object
    void ConstructL();
   
    void StartL();
    
    void Stop();
private:
    // The game scorekeeper.
    // Own
    CScorekeeper* iScorekeeper;
    
    // The game primary scene
    // Own
    TScene* iPrimaryScene;
    
    // The game secondary scene
    // Own
    TScene* iSecondaryScene;
    
    // The current removable figure
    // Own.
    CRemovableFigure* iRemovableFigure;
    
    // The next removable figure
    // Own.
    CNextRemovableFigure* iNextRemovableFigure;
    
    // The fixed figure on the bottom of this scene
    // Own.
    CFixedFigure* iFixedFigure;
    
    // Game Engine's observer, actually it is CTetrisAppUi
    // No own.
    MEngineObserver& iObserver;
    
    // The animation figure
    // Own
    CAnimationFigure* iAnimationFigure;
    
    // The Mark of playing animation
    TBool iPlayingAnimation;
    };

#endif // C_TETRISGAMEENGINE_H

// End of the file.
