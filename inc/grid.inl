/* ====================================================================
 * File: grid.inl
 * Created: 12/20/07
 * Author: Sun Jinbo
 * Copyright (c): TietoEnator, All rights reserved
 * ==================================================================== */

#include "grid.h"

// Get the position
TPoint TGrid::Pos() const
    {
    return iPos;
    }

// Set the position
void TGrid::SetPos( TPoint aPos )
    {
    iPos = aPos;
    }

// Get the color
TRgb TGrid::Color() const
    {
    return iColor;
    }

// Set the color
void TGrid::SetColor( TRgb aColor )
    {
    iColor = aColor;
    }

// End of the file.
