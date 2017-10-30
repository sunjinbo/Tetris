/* ====================================================================
 * File: sceneobserver.h
 * Created: 12/21/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef M_SCENEOBSERVER_H
#define M_SCENEOBSERVER_H

enum TSceneState // for reporting to observer
    {
    EScenePrimaryScreenUpdated,
    ESceneSecondaryScreenUpdated
    };

/**
* MSceneObserver class
*
* @since S60 3.1
*/
class MSceneObserver
    {
public:
    // Called when figure state changes and observer needs to be notified.
    virtual void StateChangedL( TSceneState aNewState ) = 0;
    };

#endif // M_SCENEOBSERVER_H

// End of the file.
