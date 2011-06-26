#ifndef GFORT_PHYSICS_PHYSICS_HELPER_H_
#define GFORT_PHYSICS_PHYSICS_HELPER_H_

#include <Box2D/Box2D.h>

namespace GFort { namespace Physics
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
	static float32 GetAngle(b2Vec2 center, b2Vec2 target);
	
	/// Create an object that has single fixture.
    /// @param bodyDef The body definition.
    /// @param fixtureDef The fixture definition.
	static b2Body* CreateBody(b2World* world, const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	
	/// Create circle
    static b2Body* CreateCircle(b2World* world, const b2BodyDef& bodyDef, const float32& radius);
	static b2Body* CreateCircle(b2World* world, const b2Vec2& position, float32 radius);
	static b2Body* CreateCircle(b2World* world, const b2Vec2& position, float32 radius, float32 angle);
	static b2Body* CreateCircle(b2World* world, b2Vec2 start, b2Vec2 end);
	
	/// Create box    
	static b2Body* CreateBox(b2World* world, const b2Vec2& start, const b2Vec2& end);
	static b2Body* CreateBox(b2World* world, const b2Vec2& start, const b2Vec2& end, const b2Vec2& rcenter, float32 angle);
	static b2Body* CreateBox(b2World* world, const b2Vec2& position, float32 width, float32 height);
	static b2Body* CreateBox(b2World* world, const b2Vec2& position, float32 width, float32 height, const b2Vec2& rcenter, float32 angle);
 	static b2Body* CreateBox(b2World* world, const b2BodyType& bodyType, const b2Vec2& start, const b2Vec2& end);
    static b2Body* CreateBox(b2World* world, const b2BodyType& bodyType, const b2Vec2& position, const float32& width, const float32& height, const b2Vec2& rcenter, const float32& angle);
    static b2Body* CreateBox(b2World* world, const b2BodyDef& bodyDef, const b2Vec2& size, const b2Vec2& rcenter, const float32& angle);

	/// Create bounded area
	static b2Body* CreateBoundedArea(b2World* world, float32 width, float32 height);
	static b2Body* CreateBoundedArea(b2World* world, const b2Vec2& position, float32 width, float32 height);
};


} } // namespace

#endif // GFORT_PHYSICS_PHYSICS_HELPER_H_
