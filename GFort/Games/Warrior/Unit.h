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

#include <vector>
#include <GFort/Core/Game/IEntity.h>
#include <GFort/Games/Warrior/UnitAction.h>
#include "Struct.h"

namespace Warrior 
{
    
/// Class of basic unit
class Unit : public GFort::Core::Game::IEntity
{
public:
    typedef short LifeType;

public:
    /// Constructor.
    Unit();
    
    /// Gets whether the unit is alive.
    const bool Alive() const                        { return lives_ > 0; }
        
    /// Gets the state of the unit.
    const UnitActionType CurrentAction() const      { return current_action_; }

    /// Gets whether the unit can perform attack.
    virtual const bool CanPerformAttack() const     { return false; }

    /// Gets whether the unit is under control and able to do action assigned.
    virtual const bool IsUnderControl() const       { return true; }

    /// Takes damage. Returns true if it is still alive.
    /// @param damage
    virtual const bool TakeDamage(const short& damage);

    /// Kill the unit.
    virtual void Die()                              { lives_ = 0; }

    /// Reset all parameters.
    virtual void Reset();    

    /// Sets the action of the unit. Returns true if action changed.
    /// @param value
    const bool SetAction(const UnitActionType& value);

    //---------------------------------------------------------------
    // Properties
    //---------------------------------------------------------------
    /// Gets maximum health point of the unit.
    const LifeType MaxLives() const                         { return max_lives_; }

    /// Gets the walk speed of the unit.
    const float WalkSpeed() const                           { return walk_speed_; }

    /// Gets the run speed of the unit.
    const float RunSpeed() const                            { return run_speed_; }

    /// Gets the health point of the unit.
    const LifeType Lives() const                            { return lives_; }

    /// Gets facing direction.
    const FacingDirection& Facing()                         { return facing_; }

    /// Gets whether the unit is floating in the air.
    const bool& FloatingInTheAir() const                    { return floating_in_the_air_; }

    /// Sets maximum lives of the unit.
    /// @param value
    virtual void SetMaxLives(const LifeType& value)         { max_lives_ = value; }

    /// Sets walk speed of the unit.
    /// @param value
    virtual void SetWalkSpeed(const float& value)           { walk_speed_ = value; }

    /// Sets run speed of the unit.
    /// @param value
    virtual void SetRunSpeed(const float& value)            { run_speed_ = value; }

    /// Sets the lives of the unit.
    /// @param value
    virtual void SetLives(const LifeType& value)            { lives_ = value; }

    /// Sets facing dircection of the unit.
    /// @param value
    virtual void SetFacing(const FacingDirection& value)    { facing_ = value; }

    /// Sets whether the unit is floating in the air.
    /// @param value
    virtual void SetFloatingInTheAir(const bool& value)     { floating_in_the_air_ = value; }
    
protected:
    // Attributes
    LifeType                    max_lives_;
    float                       walk_speed_;
    float                       run_speed_;

    // Instances
    LifeType                    lives_;
    FacingDirection             facing_;
    UnitActionType              current_action_;
    std::vector<UnitAction>     actions_;
    bool                        floating_in_the_air_;   
};  
    
inline Unit::Unit()
    : max_lives_(0),
      walk_speed_(0),
      run_speed_(0),
      lives_(0),
      current_action_(kUnitActionTypeIdle),
      facing_(kFacingRight),
      floating_in_the_air_(false)
{
}

inline const bool Unit::TakeDamage(const short& damage)
{
    lives_ -= damage;
    return (lives_ > 0);
}

inline void Unit::Reset()
{
    //max_lives_ = 0;
    //walk_speed_ = 0;
    //run_speed_ = 0;
    lives_ = 1;
    current_action_ = kUnitActionTypeIdle;
    facing_ = kFacingRight;
    floating_in_the_air_ = false;
}
    
inline const bool Unit::SetAction(const UnitActionType& value)
{
    if (current_action_ != value)
    {
        current_action_ = value;    
        return true;
    }
    return false;
}
    
} // namespace

#endif // WARRIOR_UNIT_H_
