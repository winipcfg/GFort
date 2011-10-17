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

#ifndef WARRIOR_BATTLE_H_
#define WARRIOR_BATTLE_H_

#include <vector>
#include <deque>
#include <GFort/Core/Physics/PhysicsController.h>
#include <GFort/Core/Physics/PhysicsHelper.h>
#include <GFort/Games/Warrior/Struct.h>
#include "Player.h"
#include "Enemy.h"
#include "Trail.h"
#include "GameStat.h"

namespace Warrior 
{

class Battle
{
public:	
    /// Constructor
    Battle();    

    /// Destructor
    ~Battle();
        
    /// Initialize a battle
    void Initialize();
        
    bool MouseDown(const b2Vec2& p);
    void MouseMove(const b2Vec2& p);
    void MouseUp(const b2Vec2& p);
        
    /// Reset the battle.
    void Reset();	

    /// Gets the bounding region.
    BPolygon GetBoundingRegion();

    /// Perform slice.
    void DoSlice(const Trail& trail);
        
protected:
public:
    GFort::Core::Physics::PhysicsController     phys_controller_;
    GFort::Core::Physics::Box2dSettings         phys_settings_;

    b2Vec2                                      mouse_world_;
    b2Body*                                     ground_body_;
    b2Body*                                     player_body_;
        
    b2Body*                                     mouse_point_;
    b2MouseJoint*                               mouse_joint_;
            
    // Stores the player and enemies.
    Player                                      player_;
    std::vector<Enemy>                          enemies_;

    GameStat                                    stat_;
};

}

#endif // WARRIOR_BATTLE_H_
