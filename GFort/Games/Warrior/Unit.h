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
#include <GFort/Core/Physics/PhysicsController.h>
#include <GFort/Core/Physics/PhysicsHelper.h>
#include "Struct.h"

namespace Warrior 
{
    
/// Class of basic unit
class Unit : public GFort::Core::Game::IEntity
{
public:
    /// Constructor.
    Unit();
    
    /// Gets whether the unit is alive.
    const bool Alive() const                                { return lives_ > 0; }
        
    /// Gets whether the unit can perform attack.
    virtual const bool CanPerformAttack() const             { return false; }

    /// Gets whether the unit is under control and able to do action assigned.
    virtual const bool IsUnderControl() const               { return true; }

    /// Takes damage. Returns true if it is still alive.
    /// @param damage
    virtual const bool TakeDamage(const short& damage);

    /// Kill the unit.
    virtual void Die()                                      { lives_ = 0; }

    /// Reset all parameters.
    virtual void Reset();    

    //---------------------------------------------------------------
    // Physics
    //---------------------------------------------------------------
    /// Gets the physics body.
    b2Body* Body()                                          { return body_; }

    /// Assign physics body to the unit.
    /// @param body
    void SetBody(b2Body* body)                              { body_ = body; }
    
    //---------------------------------------------------------------
    // Actions
    //---------------------------------------------------------------
    /// Gets current action of the unit.
    const UnitAction CurrentAction() const                  { return action_; }

    /// Issue command to the unit. 
    /// If replace is set as true, the action will replace current and pending actions.
    /// If replace is set as false, the action will go to pending list.
    /// @param action
    /// @param replace
    void IssueCommand(const UnitAction& action, const bool& replace);

    //---------------------------------------------------------------
    // Properties
    //---------------------------------------------------------------
    /// Gets maximum health point of the unit.
    const short MaxLives() const                            { return max_lives_; }

    /// Gets the walk speed of the unit.
    const float WalkSpeed() const                           { return walk_speed_; }

    /// Gets the run speed of the unit.
    const float RunSpeed() const                            { return run_speed_; }

    /// Gets the health point of the unit.
    const short Lives() const                               { return lives_; }

    /// Gets facing direction.
    const FacingDirection& Facing()                         { return facing_; }

    /// Gets whether the unit is floating in the air.
    const bool& FloatingInTheAir() const                    { return floating_in_the_air_; }

    /// Sets maximum lives of the unit.
    /// @param value
    virtual void SetMaxLives(const short& value)            { max_lives_ = value; }

    /// Sets walk speed of the unit.
    /// @param value
    virtual void SetWalkSpeed(const float& value)           { walk_speed_ = value; }

    /// Sets run speed of the unit.
    /// @param value
    virtual void SetRunSpeed(const float& value)            { run_speed_ = value; }

    /// Sets the lives of the unit.
    /// @param value
    virtual void SetLives(const short& value)               { lives_ = value; }

    /// Sets facing dircection of the unit.
    /// @param value
    virtual void SetFacing(const FacingDirection& value)    { facing_ = value; }

    /// Sets whether the unit is floating in the air.
    /// @param value
    virtual void SetFloatingInTheAir(const bool& value)     { floating_in_the_air_ = value; }
    
protected:
    // Physics body
    b2Body*                     body_;

    // Attributes
    short                       max_lives_;
    float                       walk_speed_;
    float                       run_speed_;

    // Instances
    short                       lives_;
    FacingDirection             facing_;

public:
    UnitAction                  action_;
    std::deque<UnitAction >     pending_actions_;

    bool                        floating_in_the_air_;   
};    
    
} // namespace

#endif // WARRIOR_UNIT_H_
