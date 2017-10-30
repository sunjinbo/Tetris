/* ====================================================================
 * File: figureobserver.h
 * Created: 12/21/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef M_FIGUREOBSERVER_H
#define M_FIGUREOBSERVER_H

// Enumeration for specifying, which figure state chaged.
enum TFigureState // for reporting to observer
    {
    EFixedFigureReleaseOneLine,
    EFixedFigureReleaseTwoLines,
    EFixedFigureReleaseThreeLines,
    EFixedFigureReleaseFourLines,
    EFixedFigureMerged,
    EFixedFigureOverflowed,
    ENextRemovableFigureUpdated,
    ERemovableFigureUpdated,
    ERemovableFigureLeftMoved,
    ERemovableFigureRightMoved,
    ERemovableFigureRotated,
    ERomovableFigureDropped,
    ERomovableFigureDropEnded,
    EAnimationFigureStarted,
    EAnimationFigureUpdated,
    EAnimationFigureEnded
    };

/**
* MFigureObserver class
*
* @since S60 3.1
*/
class MFigureObserver
    {
public:
    // Called when figure state changes and observer needs to be notified.
    virtual void StateChangedL( TFigureState aNewState ) = 0;
    };

#endif // M_FIGUREOBSERVER_H

// End of the file.
