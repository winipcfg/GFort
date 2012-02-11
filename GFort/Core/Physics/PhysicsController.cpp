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

#include "PhysicsController.h"

namespace GFort { namespace Core { namespace Physics
{

const float	kGravitationalField	= 9.81f;

PhysicsController::PhysicsController()
    : world_(NULL),
      num_contact_points_(0)
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	bool doSleep = true;
	
	world_ = new b2World(gravity);
    world_->SetAllowSleeping(doSleep);
	world_->SetContactListener(this);
}

PhysicsController::~PhysicsController()
{
	if (world_ != NULL) 
    {
		delete world_;
		world_ = NULL;
	}
}

void PhysicsController::SetWorld(b2World* world)
{
	if (world_ != world)
	{
		b2World* tmp = world_;	
		world_ = world;		
		if (tmp != NULL) 
        {
			delete tmp;
			tmp = NULL;
		}
	}
}

void PhysicsController::SetDefaultGravity()
{
	b2Vec2 gravity(0, -kGravitationalField);		
	world_->SetGravity(gravity);
}

void PhysicsController::UpdateGravityDirection(const b2Vec2& direction)
{
	if (world_ != NULL)
	{
        b2Vec2 dir = direction;
        dir.Normalize();
        b2Vec2 newGravity = world_->GetGravity().Length() * direction;
        world_->SetGravity(newGravity);	
	}
}

/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. disable contact).
/// A copy of the old manifold is provided so that you can detect changes.
/// Note: this is called only for awake bodies.
/// Note: this is called even when the number of contact points is zero.
/// Note: this is not called for sensors.
/// Note: if you set the number of contact points to zero, you will not
/// get an EndContact callback. However, you may get a BeginContact callback
/// the next step.
void PhysicsController::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	b2ContactListener::PreSolve(contact, oldManifold);
	
	const b2Manifold* manifold = contact->GetManifold();
	
	if (manifold->pointCount == 0)
	{
		return;
	}
	
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
	b2GetPointStates(state1, state2, oldManifold, manifold);
	
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);
		
	for (int32 i = 0; 
        i < manifold->pointCount && num_contact_points_ < kMaxContactPoints; 
        ++i)
	{
		ContactPoint* cp = &contact_points_[num_contact_points_];
		cp->fixtureA = fixtureA;
		cp->fixtureB = fixtureB;
		cp->position = worldManifold.points[i];
		cp->normal = worldManifold.normal;
		cp->state = state2[i];
		++num_contact_points_;
	}	
}

void PhysicsController::Step(Box2dSettings* settings, const float32& deltaTime)
{	
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	float32 timeStep = settings->hz > 0.0f ? 1.0f / settings->hz : float32(0.0f);
	
	if (settings->Paused())
	{
		if (settings->singleStep)
		{
			settings->singleStep = 0;
		}
		else
		{
			timeStep = 0.0f;
		}
	}
	
	world_->SetWarmStarting(settings->enableWarmStarting > 0);
	world_->SetContinuousPhysics(settings->enableContinuous > 0);
		
	world_->Step(timeStep, settings->velocityIterations, settings->positionIterations);
}


} } } // namespace
