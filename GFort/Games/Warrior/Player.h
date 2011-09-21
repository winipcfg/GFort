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

#ifndef WARRIOR_PLAYER_H_
#define WARRIOR_PLAYER_H_

#include "Unit.h"
#include "Weapon.h"
#include "PlayerState.h"

namespace Warrior 
{
    
const short kDefaultLives       = 5;
const short kMaxLives           = 10;

/// Stores player information
class Player : public Unit 
{
public:
    /// Constructor.
    Player();

    /// Destructor.
    ~Player();
        
    /// Gets the state of Player
    const PlayerState State() const             { return state_; }
    
    /// Gets whether Player is landing.
    bool IsLanding() const                      { return state_ == kLanding; }

    /// Gets whether Player can perform attack.
    virtual const bool CanPerformAttack() const;
    
    /// Sets the state of Player.
    /// @param state
    void SetState(const PlayerState& state)     { state_ = state; }
        
private:    
    // Stores the state of the Player
    PlayerState     state_;

    // Stores the weapon information
    Weapon          weapon_;
};  

    
inline Player::Player()
    : state_(kPlayerStateIdle)
{
    lives_ = kDefaultLives;
}

inline Player::~Player()
{
}

inline const bool Player::CanPerformAttack() const
{
    if (current_action_ == kUnitActionTypeIdle ||
        current_action_ == kUnitActionTypeWalk ||
        current_action_ == kUnitActionTypeRun)
        return true;
    return false;
}    
            
} // namespace

#endif // WARRIOR_PLAYER_H_
