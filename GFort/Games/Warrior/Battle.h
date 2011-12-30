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
#include "Battlefield.h"
#include "Player.h"
#include "Enemy.h"
#include "Trail.h"
#include "GameStat.h"

namespace Warrior 
{

/// The controller class that handles battle.
class Battle : public GFort::Core::ISubject<Battle>
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

    /// Gets the physics world.
    b2World* World()                                        { return phys_controller_.World(); }

    /// Gets the physics settings.
    GFort::Core::Physics::Box2dSettings& PhysicsSettings()  { return phys_settings_; }

    /// Gets the map.
    Battlefield& Map()                                      { return map_; }

    /// Gets the player.
    Player& GetPlayer()                                     { return player_; }

    /// Gets the statistic of battle.
    GameStat& Stat()                                        { return stat_; }
    
    /// Perform slice by specified trail.
    /// @param trail
    /// @param[out] affectedUnits
    void DoSlice(const Trail& trail, std::vector<Unit>& affectedUnits);

    /// Update the battle.
    void Update(const float& dt);

public:
    /// Spawn player at specified location.
    /// @param position
    void SpawnPlayer(const b2Vec2& position);

    /// Spawn enemy at specified location.
    /// @param position
    Enemy* SpawnEnemy(const b2Vec2& position);

    /// Resolve attack.
    /// @param attacker
    /// @param target
    void ResolveAttack(Unit& attacker, Unit& target);
        
protected:
    GFort::Core::Physics::PhysicsController     phys_controller_;
    GFort::Core::Physics::Box2dSettings         phys_settings_;
    
    // Stores the player and enemies.
    Battlefield                                 map_;
    Player                                      player_;
    std::vector<Enemy* >                        enemies_;

    GameStat                                    stat_;
};

}

#endif // WARRIOR_BATTLE_H_
