//Copyright (C) 2011 by Gavin Fong
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#ifndef WARRIOR_UNIT_H_
#define WARRIOR_UNIT_H_

#include "PlayerState.h"

namespace Warrior 
{

/// Class of basic unit
class Unit 
{
public:
    /// Constructor.
    Unit();
    
    /// Gets whether the unit is alive.
    const bool Alive() const                    { return lives_ >= 0; }

    /// Gets the health point of the unit.
    const short Lives() const                   { return lives_; }

    /// Kill the unit.
    virtual void Die();

    /// Sets lives of the unit.
    virtual void SetAlive(const bool& value)    { lives_ = value; }
    
protected:
    // Stores the live of the unit.
    short           lives_;

    // Stores the facing of the unit. (False - Left, True - Right)
    bool            facing_;
};  
    
inline Unit::Unit()
{
    lives_ = 1;
}
    
    
} // namespace

#endif // WARRIOR_UNIT_H_
