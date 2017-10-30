/* ====================================================================
 * File: scorekeeper.cpp
 * Created: 12/29/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

// INCLUDES
#include "scorekeeper.h"

// CONSTANTS
const TInt KDefaultLevelValue = 0;
const TInt KDefaultLineValue = 0;
const TInt KDefaultScoreValue = 0;
const TInt KDefaultLifeValue = 4;
const TInt KScoreIncreaseRadix1 = 100; // 100 cent.
const TInt KScoreIncreaseRadix2 = 300; // 300 cent.
const TInt KScoreIncreaseRadix3 = 600; // 600 cent.
const TInt KScoreIncreaseRadix4 = 1000; // 1000 cent.
const TInt KLevelIncreaseRadix = 10000; // increase one level per 10000 cent.

// Creates a new Scorekeeper object, 
// and leaves if there is insufficient memory to create it.
CScorekeeper* CScorekeeper::NewL( MScorekeeperObserver& aObserver )
    {
    CScorekeeper* self = new( ELeave ) CScorekeeper( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// gets level
TInt CScorekeeper::Level() const
    {
    return iLevel;
    }

// gets line
TInt CScorekeeper::Line() const
    {
    return iLine;
    }

// gets score
TInt CScorekeeper::Score() const
    {
    return iScore;
    }

// gets life
TInt CScorekeeper::Life() const
    {
    return iLife;
    }

// deletes lines
void CScorekeeper::DeleteLines( TInt aLines )
    {
    // updates line
    iLine += aLines;
    iObserver.StateChangedL( EScorekeeperLineUpdated );
    
    // updates score
    switch ( aLines )
        {
        case 1:
            iScore += KScoreIncreaseRadix1;
            break;
        case 2:
            iScore += KScoreIncreaseRadix2;
            break;
        case 3:
            iScore += KScoreIncreaseRadix3;
            break;
        case 4:
            iScore += KScoreIncreaseRadix4;
        default:
            break;
        }
    iObserver.StateChangedL( EScorekeeperScoreUpdated );
    
    // updates level
    if ( ( iScore / KLevelIncreaseRadix ) != iLevel  )
        {
        iLevel = iScore / KLevelIncreaseRadix;
        iObserver.StateChangedL( EScorekeeperLevelUpdated );
        }
    }

// kills one life
void CScorekeeper::KillLife()
    {
    iLife = iLife - 1;
    iObserver.StateChangedL( EScorekeeperLifeUpdated );
    if ( !iLife )
        {
        iObserver.StateChangedL( EScorekeeperAllLifeOver );
        }
    }

// resets all data.
void CScorekeeper::Reset()
    {
    iLevel = KDefaultLevelValue;
    iLine = KDefaultLineValue;
    iScore = KDefaultScoreValue;
    iLife = KDefaultLifeValue;
    }

// Constructor.
CScorekeeper::CScorekeeper( MScorekeeperObserver& aObserver )
    : iObserver( aObserver )
    { // no implementation required   
    }

// Completes construction of the CScorekeeper object.
void CScorekeeper::ConstructL()
    {
    Reset();
    }

// End of the file.
