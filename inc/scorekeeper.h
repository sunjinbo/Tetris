/* ====================================================================
 * File: scorekeeper.h
 * Created: 12/21/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREKEEPER_H
#define C_SCOREKEEPER_H

#include <e32def.h>
#include <e32base.h>

// Enumeration for specifying, which figure state chaged.
enum TScorekeeperState // for reporting to observer
    {
    EScorekeeperLevelUpdated = 0,
    EScorekeeperLineUpdated,
    EScorekeeperScoreUpdated,
    EScorekeeperLifeUpdated,
    EScorekeeperAllLifeOver
    };

/**
* MScorekeeperObserver class
*
* @since S60 3.1
*/
class MScorekeeperObserver
    {
public:
    // Called when figure state changes and observer needs to be notified.
    virtual void StateChangedL( TScorekeeperState aNewState ) = 0;
    };

/**
* CScorekeeper class
*
* @since S60 3.1
*/
NONSHARABLE_CLASS( CScorekeeper ) : public CBase
    {
public:
    // Creates a new Scorekeeper object, 
    // and leaves if there is insufficient memory to create it.
    static CScorekeeper* NewL( MScorekeeperObserver& aObserver );

    // Get level
    TInt Level() const;

    // Get line
    TInt Line() const;

    // Get score
    TInt Score() const;

    // Get life
    TInt Life() const;

    // Delete lines
    void DeleteLines( TInt aLines );
    
    // Kill one life
    void KillLife();

    // Reset all
    void Reset();

private:
    // Constructor.
    CScorekeeper( MScorekeeperObserver& aObserver );

    // Completes construction of the CScorekeeper object.
    void ConstructL();

private:
    // Level
    TInt iLevel;

    // Line
    TInt iLine;

    // Score
    TInt iScore;

    // Life
    TInt iLife;

    // ScoreKeeper's observer, actually it is CTetrisGameEngine's object.
    // No own.
    MScorekeeperObserver& iObserver;
    };

#endif // C_SCOREKEEPER_H

// End of the file.
