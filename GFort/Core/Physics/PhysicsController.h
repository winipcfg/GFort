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

#ifndef GFORT_CORE_PHYSICS_PHYSICS_CONTROLLER_H_
#define GFORT_CORE_PHYSICS_PHYSICS_CONTROLLER_H_

#include <Box2D/Box2D.h>
#include <string>

#include "Box2dSettings.h"

namespace GFort { namespace Core { namespace Physics
{

const int32 kMaxContactPoints = 2048;

struct ContactPoint
{
	b2Fixture*      fixtureA;
	b2Fixture*      fixtureB;
	b2Vec2          normal;
	b2Vec2          position;
	b2PointState    state;
};

/// Physics Controller
class PhysicsController : b2ContactListener
{
public:
    /// Constructor.
	PhysicsController();

    /// Destructor.
	~PhysicsController();

	/// Gets the world.
	b2World* World()                            { return world_; }
	
	/// Assign the world to controller.
    /// @param world The new world
	void SetWorld(b2World* world);
        
	/// Sets default download gravity.
	void SetDefaultGravity();

	/// Updates the gravity direction of the world while the magnitude does not change.
    /// @param direction
	void UpdateGravityDirection(const b2Vec2& direction);
	
	/// Do a single step.
    /// @param settings
    /// @param deltaTime
	virtual void Step(Box2dSettings* settings, const float32& deltaTime);
	
	virtual bool MouseDown(const b2Vec2& p)     { return false; }
	virtual void MouseUp(const b2Vec2& p)       {}
	virtual void MouseMove(const b2Vec2& p)     {}
		
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    
    /// Sets debug draw.
    /// @param debugDraw
	void SetDebugDraw(b2DebugDraw* debugDraw)   { if (world_ != NULL) world_->SetDebugDraw(debugDraw); }
	
    /// Draws debug data.
    void DrawDebugData()                        { if (world_ != NULL) world_->DrawDebugData(); }
	
protected:
    // Stores the world it handles
	b2World*			world_;	
	
    // Stores contact points
	ContactPoint		contact_points_[kMaxContactPoints];
	int32				num_contact_points_;
	
private:
};

} } } // namespace

#endif // GFORT_CORE_PHYSICS_PHYSICS_CONTROLLER_H_
