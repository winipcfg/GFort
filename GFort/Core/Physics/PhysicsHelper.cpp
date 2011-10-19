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

#include "PhysicsHelper.h"

namespace GFort { namespace Core { namespace Physics
{

inline float32 PhysicsHelper::GetAngle(const b2Vec2& center, const b2Vec2& target)
{
	b2Vec2 diff = target - center;
	return -atan2(-diff.y, diff.x);
}

b2Body* PhysicsHelper::CreateBody(
    b2World* world, 
    const b2BodyDef& bodyDef, 
    const b2FixtureDef& fixture_def)
{
	b2Body *body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixture_def);
	return body;
}

b2Body* PhysicsHelper::CreateCircle(
    b2World* world, 
    const b2BodyDef& bodyDef,
    const float32& radius)
{    
	b2Body *body = world->CreateBody(&bodyDef);

	// Define shape for our dynamic body.
	b2CircleShape shape;
	shape.m_radius = radius/PTM_RATIO;
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
	
	return body;
}

b2Body* PhysicsHelper::CreateCircle(
    b2World* world, 
    const b2Vec2& position, 
    const float32& radius)
{
	return CreateCircle(world, position, radius, 0);
}

b2Body* PhysicsHelper::CreateCircle(
    b2World* world, 
    const b2Vec2& position, 
    const float32& radius, 
    const float32& angle)
{	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
	bodyDef.angle = angle;
	
	b2Body *body = world->CreateBody(&bodyDef);
	
	// Define shape for our dynamic body.
	b2CircleShape shape;
	shape.m_radius = radius/PTM_RATIO;
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
	
	return body;
}

b2Body* PhysicsHelper::CreateCircle(
    b2World* world, 
    const b2Vec2& start, 
    const b2Vec2& end)
{
	// Get the center and the radius of the circle
	float32 radius = (end - start).Length();
	b2Vec2 pos = start;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
	bodyDef.angle = GetAngle(start, end);
	
	b2Body *body = world->CreateBody(&bodyDef);
	
	// Define shape for our dynamic body.
	b2CircleShape shape;
	shape.m_radius = radius/PTM_RATIO;
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	body->CreateFixture(&fixtureDef);
	
	return body;
}

b2Body* PhysicsHelper::CreateCircle(
    b2World* world, 
    const b2BodyType& bodyType, 
    const b2Vec2& position, 
    const float32& radius)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
	bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
    return CreateCircle(world, bodyDef, radius);
}

b2Body* PhysicsHelper::CreateBox(b2World* world, const b2Vec2& start, const b2Vec2& end)
{
	// Get the center and the size of the box
	b2Vec2 size = end - start;
	b2Vec2 pos = b2Vec2((start + end).x/2, (start + end).y/2);			
	return CreateBox(world, pos, size.x, size.y, b2Vec2_zero, 0);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2Vec2& start, 
    const b2Vec2& end, 
    const b2Vec2& rcenter, 
    const float32& angle)
{
	// Get the center and the size of the box
	b2Vec2 size = end - start;
	b2Vec2 pos = b2Vec2((start + end).x/2, (start + end).y/2);	
	return CreateBox(world, pos, size.x, size.y, rcenter, angle);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2Vec2& position, 
    const float32& width, 
    const float32& height)
{
	return CreateBox(world, position, width, height, b2Vec2_zero, 0);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2Vec2& position, 
    const float32& width, 
    const float32& height, 
    const b2Vec2& rcenter, 
    const float32& angle)
{
	// Define the dynamic body.
	b2BodyDef bodyDef;

	//bodyDef.type = b2_staticBody;
	//bodyDef.type = b2_kinematicBody;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);

	b2Body *body = world->CreateBody(&bodyDef);

	// Define shape for our dynamic body.
	b2PolygonShape dynamicBox;
	float midX = (width / PTM_RATIO) / 2;
	float midY = (height / PTM_RATIO) / 2;
	b2Vec2 rotationCenter(rcenter.x/PTM_RATIO, rcenter.y/PTM_RATIO);
	dynamicBox.SetAsBox(midX, midY, rotationCenter, angle);
		
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	body->CreateFixture(&fixtureDef);
		
	return body;
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2BodyType& bodyType, 
    const b2Vec2& start, 
    const b2Vec2& end)
{
    // Get the center and the size of the box
	b2Vec2 size = end - start;
	b2Vec2 pos = b2Vec2((start + end).x/2, (start + end).y/2);	

    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
	bodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);
    return CreateBox(world, bodyDef, size, b2Vec2_zero, 0);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2BodyType& bodyType, 
    const b2Vec2& position, 
    const float32& width,
    const float32& height)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
	bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
	return CreateBox(world, bodyDef, b2Vec2(width, height), b2Vec2_zero, 0);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2BodyType& bodyType, 
    const b2Vec2& position, 
    const float32& width,
    const float32& height, 
    const b2Vec2& rcenter, 
    const float32& angle)
{
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
	bodyDef.position.Set(position.x/PTM_RATIO, position.y/PTM_RATIO);
	return CreateBox(world, bodyDef, b2Vec2(width, height), rcenter, angle);
}

b2Body* PhysicsHelper::CreateBox(
    b2World* world, 
    const b2BodyDef& bodyDef, 
    const b2Vec2& size, 
    const b2Vec2& rcenter, 
    const float32& angle)
{
	b2Body *body = world->CreateBody(&bodyDef);

	// Define shape for our dynamic body.
	b2PolygonShape dynamicBox;
	float midX = (size.x / PTM_RATIO) / 2;
	float midY = (size.y / PTM_RATIO) / 2;
	b2Vec2 rotationCenter(rcenter.x/PTM_RATIO, rcenter.y/PTM_RATIO);
	dynamicBox.SetAsBox(midX, midY, rotationCenter, angle);
	
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	body->CreateFixture(&fixtureDef);
		
	return body;
}

b2Body* PhysicsHelper::CreateBoundedArea(
    b2World* world, 
    const float32& width, 
    const float32& height)
{
	return CreateBoundedArea(world, b2Vec2(0, 0), width, height);
}

b2Body* PhysicsHelper::CreateBoundedArea(
    b2World* world, 
    const b2Vec2& position, 
    const float32& width, 
    const float32& height)
{	
	// Calculate the position
	float32 left_x = position.x/PTM_RATIO;
	//float32 right_x = (position.x + width)/PTM_RATIO;
	float32 bottom_y = position.y/PTM_RATIO;
	//float32 top_y = (position.y + height)/PTM_RATIO;
	float32 width_t = width/PTM_RATIO;
	float32 height_t = height/PTM_RATIO;
	
	
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(left_x, bottom_y); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Define the ground box shape.
	b2PolygonShape groundBox;					
	
	// bottom
	groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(width_t,0));
	groundBody->CreateFixture(&groundBox,0);
	
	// top
	groundBox.SetAsEdge(b2Vec2(0,height_t), b2Vec2(width_t,height_t));
	groundBody->CreateFixture(&groundBox,0);
	
	// left
	groundBox.SetAsEdge(b2Vec2(0,height_t), b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox,0);
	
	// right
	groundBox.SetAsEdge(b2Vec2(width_t,height_t), b2Vec2(width_t,0));
	groundBody->CreateFixture(&groundBox,0);	
	
	return groundBody;
}

} } } // namespace
