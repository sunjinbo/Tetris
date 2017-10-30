/* ====================================================================
 * File: engineobserver.h
 * Created: 01/10/08
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef M_ENGINEOBSERVER_H
#define M_ENGINEOBSERVER_H

enum TEngineState // for reporting to observer
    {
    EEnginePrimaryScreenUpdated = 0,
    EEngineSecondaryScreenUpdated,
    EEngineLevelUpdated,
    EEngineLineUpdated,
    EEngineScoreUpdated,
    EEngineLifeUpdated,
    EEngineAllUpdated,
    EEngineGameOver
    };

/**
* MEngineObserver class
*
* @since S60 3.1
*/
class MEngineObserver
    {
public:
    // Called when game engine state changes and observer needs to be notified.
    virtual void StateChangedL( TEngineState aNewState ) = 0;
    };

#endif // M_ENGINEOBSERVER_H

// End of the file.
