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

#ifndef GFORT_CORE_PHYSICS_PHYSICS_HELPER_H_
#define GFORT_CORE_PHYSICS_PHYSICS_HELPER_H_

#include <vector>
#include <Box2D/Box2D.h>
#include <GFort/Core/Physics/Box2dSettings.h>

namespace GFort { namespace Core { namespace Physics
{

//Pixel to metres ratio. Box2D uses metres as the unit for measurement.
//This ratio defines how many pixels correspond to 1 Box2D "metre"
//Box2D is optimized for objects of 1x1 metre therefore it makes sense
//to define the ratio so that your most common object type is 1x1 metre.
#define         PTM_RATIO	        32.0f
const float32   kINV_PTM_RATIO      = 1.0/PTM_RATIO;

// Class that provide static methods for game
class PhysicsHelper 
{
public:
	/// Returns rotation angle given center and target point.
	/// @param center The center position.
	/// @param target The target position.
	static float32 GetAngle(const b2Vec2& center, const b2Vec2& target);
	
	/// Create an object that has single fixture.
    /// @param bodyDef The body definition.
    /// @param fixtureDef The fixture definition.
	static b2Body* CreateBody(b2World* world, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	
	/// Create circle
    static b2Body* CreateCircle(b2World* world, const b2BodyDef& bodyDef, const float32& radius);
	static b2Body* CreateCircle(b2World* world, const b2Vec2& position, const float32& radius);
	static b2Body* CreateCircle(b2World* world, const b2Vec2& position, const float32& radius, const float32& angle);
	static b2Body* CreateCircle(b2World* world, const b2Vec2& start, const b2Vec2& end);
    static b2Body* CreateCircle(b2World* world, const b2BodyType& bodyType, const b2Vec2& position, const float32& radius);
	
	/// Create box    
	static b2Body* CreateBox(b2World* world, const b2Vec2& start, const b2Vec2& end);
	static b2Body* CreateBox(b2World* world, const b2Vec2& start, const b2Vec2& end, const b2Vec2& rcenter, const float32& angle);
	static b2Body* CreateBox(b2World* world, const b2Vec2& position, const float32& width, const float32& height);
	static b2Body* CreateBox(b2World* world, const b2Vec2& position, const float32& width, const float32& height, const b2Vec2& rcenter, const float32& angle);
 	static b2Body* CreateBox(b2World* world, const b2BodyType& bodyType, const b2Vec2& start, const b2Vec2& end);
    static b2Body* CreateBox(b2World* world, const b2BodyType& bodyType, const b2Vec2& position, const float32& width, const float32& height);
    static b2Body* CreateBox(b2World* world, const b2BodyType& bodyType, const b2Vec2& position, const float32& width, const float32& height, const b2Vec2& rcenter, const float32& angle);
    static b2Body* CreateBox(b2World* world, const b2BodyDef& bodyDef, const b2Vec2& size, const b2Vec2& rcenter, const float32& angle);

	/// Create bounded area
	static b2Body* CreateBoundedArea(b2World* world, const float32& width, const float32& height);
	static b2Body* CreateBoundedArea(b2World* world, const b2Vec2& position, const float32& width, const float32& height);

    /// Projectile

    /// Get the position of projectile, assuming there is no other obstacles and forces.
    /// @param world
    /// @param settings
    /// @param startingPosition
    /// @param startingVelocity
    /// @param steps
    static b2Vec2 GetTrajectoryPoint(b2World* world, Box2dSettings* settings, const b2Vec2& startingPosition, const b2Vec2& startingVelocity, const float& steps);

    static std::vector<b2Vec2> GetTrajectory(
        b2World* world, 
        Box2dSettings* settings, 
        b2Body* body, 
        const b2Vec2& startingPosition, 
        const b2Vec2& startingVelocity, 
        const float& maxSteps);

    static float GetTrajectoryMaxHeight(b2World* world, Box2dSettings* settings, const b2Vec2& startingPosition, const b2Vec2& startingVelocity);

    /// Get the projectile velocity.
    /// @param world
    /// @param settings
    /// @param startingPosition
    /// @param targetPosition
    /// @param duration Fixed duration
    static b2Vec2 GetTrajectoryVelocity(
        b2World* world, 
        Box2dSettings* settings, 
        const b2Vec2& startingPosition, 
        const b2Vec2& targetPosition, 
        const float32& duration);

    /// Get appropriate velocity
    //static b2Vec2 GetTrajectoryVelocity(
    //    b2World* world, 
    //    Box2dSettings* settings, 
    //    const b2Vec2& startingPosition, 
    //    const b2Vec2& targetPosition, 
    //    const float32& horizontalSpeed);

};

} } } // namespace

#endif // GFORT_CORE_PHYSICS_PHYSICS_HELPER_H_
