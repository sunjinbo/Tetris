/* ====================================================================
 * File: Tetris.pan
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#ifndef __TETRIS_PAN__
#define __TETRIS_PAN__

/** Tetris application panic codes */
enum TTetrisPanics 
    {
    ETetrisBasicUi = 8048
    // add further panics here
    };

inline void Panic(TTetrisPanics aReason)
    {
    _LIT(applicationName,"Tetris");
    User::Panic(applicationName, aReason);
    }

#endif // __TETRIS_PAN__
