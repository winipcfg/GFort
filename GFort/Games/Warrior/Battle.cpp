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

#include "Battle.h"

#include <Box2D/Box2D.h>
#include <GFort/Core/Physics/Box2dSettings.h>
#include <GFort/Core/Physics/PhysicsHelper.h>

namespace Warrior 
{

const b2Vec2 kPlayerStartPosition   = b2Vec2(100, 150);
const int kPlayerWidth              = 32;
const int kPlayerHeight             = 48;

const int kPlayerMoveSpeed          = 3;
const int kPlayerRunSpeed           = 5;

const short kMapBoundary            = 20;
    
Battle::Battle()
{		
    phys_controller_.SetDefaultGravity(); 	
    phys_controller_.World()->SetContinuousPhysics(true);                    
	
    this->Reset();
}


Battle::~Battle()
{
	for (unsigned int i = 0; i < enemies_.size(); ++i)
	{
		delete enemies_[i];
		enemies_[i] = NULL;
	}
	enemies_.clear();
}

void Battle::Initialize()
{   
 //   b2Body* body;

 //   // Create boundary
 //   body = GFort::Core::Physics::PhysicsHelper::CreateBoundedArea(
 //       phys_controller_.World(),
 //       b2Vec2(kMapBoundary, kMapBoundary),
 //       map_.Width() - kMapBoundary * 2,
 //       map_.Height() - kMapBoundary * 2);

 //   // Ground
 //   body = GFort::Core::Physics::PhysicsHelper::CreateBox(
 //       phys_controller_.World(),
 //       b2_staticBody,
 //       b2Vec2(map_.Width() / 2, map_.Landscape() / 2),
 //       map_.Width(),
 //       map_.Landscape());
 //   map_.Contents().push_back(body);

 //   // Create Player
 //   body = GFort::Core::Physics::PhysicsHelper::CreateBox(
 //       phys_controller_.World(),
 //       kPlayerStartPosition,
 //       kPlayerWidth,
 //       kPlayerHeight);

 //   body->SetFixedRotation(false);
 //   
 //   // Set the dynamic body fixture.
	//b2Fixture* fixture = body->GetFixtureList();	
	//fixture[0].SetDensity(1.0f);
	//fixture[0].SetFriction(0.3f);
	//fixture[0].SetRestitution(0.4f);	
	//body->ResetMassData();

 //   player_.SetBody(body);    
}
    
bool Battle::MouseDown(const b2Vec2& p)
{
    phys_controller_.MouseDown(p);        
    return false;
}

void Battle::MouseMove(const b2Vec2& p)
{
    phys_controller_.MouseMove(p);	
}

void Battle::MouseUp(const b2Vec2& p)
{
    phys_controller_.MouseUp(p);	
}

void Battle::Reset()
{
    Initialize();
}

void Battle::DoSlice(const Trail& trail, std::vector<Unit>& affectedUnits)
{    
    std::set<Enemy* > damaged_enemies; 
    Enemy* enemy;
    std::vector<BTurnInfo> turns;
    for (unsigned int j = 0; j < enemies_.size(); ++j)
    {
        enemy = enemies_[j];
        if (enemy->Alive())
        {         
            turns.clear();
            if (trail.Collide(enemy->GetBoundingRegion(), turns))
            {
                damaged_enemies.insert(enemy);
            }
        }
    }

    if (damaged_enemies.size() > 0)
    {
        std::set<Enemy* >::iterator it;
        for (it = damaged_enemies.begin(); it != damaged_enemies.end(); ++it)
        {
            (*it)->Die();
        }

        stat_.TotalKills += damaged_enemies.size();

        //audio_handler_.PlayKillEffect();
    }

    turns.clear();
    BPolygon poly = player_.GetBoundingRegion();
    if (trail.Within(poly) || trail.Collide(poly, turns))
    {
        b2Vec2 impulse = b2Vec2(600.0f, 1200.0f);
        b2Vec2 center = player_.Body()->GetWorldCenter();
        player_.Body()->ApplyForce(impulse, player_.Body()->GetWorldCenter());
        player_.Body()->ApplyTorque(400);
    }     
}

void Battle::Update(const float& dt)
{
    phys_controller_.Step(&phys_settings_, dt);
}

void Battle::ResolveAttack(Unit& attacker, Unit& target)
{
    target.TakeDamage(&attacker, 1);
}

Enemy* Battle::SpawnEnemy(const b2Vec2& position)
{
    Enemy* enemy = new Enemy();
    enemies_.push_back(enemy);
    return enemy;
}
    
} // namespace
