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
    : mouse_point_(NULL),
      mouse_joint_(NULL)
{		
    phys_controller_.SetDefaultGravity(); 	
    phys_controller_.World()->SetContinuousPhysics(true);                    
	
    this->Reset();
}


Battle::~Battle()
{
}

void Battle::Initialize()
{   
    b2Body* body;

    // Create boundary
    body = GFort::Core::Physics::PhysicsHelper::CreateBoundedArea(
        phys_controller_.World(),
        b2Vec2(kMapBoundary, kMapBoundary),
        map_.Width() - kMapBoundary * 2,
        map_.Height() - kMapBoundary * 2);

    // Ground
    body = GFort::Core::Physics::PhysicsHelper::CreateBox(
        phys_controller_.World(),
        b2_staticBody,
        b2Vec2(map_.Width() / 2, map_.Landscape() / 2),
        map_.Width(),
        map_.Landscape());
    map_.Contents().push_back(body);

    // Create Player
    body = GFort::Core::Physics::PhysicsHelper::CreateBox(
        phys_controller_.World(),
        kPlayerStartPosition,
        kPlayerWidth,
        kPlayerHeight);

    body->SetFixedRotation(false);
    
    // Set the dynamic body fixture.
	b2Fixture* fixture = body->GetFixtureList();	
	fixture[0].SetDensity(1.0f);
	fixture[0].SetFriction(0.3f);
	fixture[0].SetRestitution(0.4f);	
	body->ResetMassData();

    player_.SetBody(body);    
}
    
bool Battle::MouseDown(const b2Vec2& p)
{
    phys_controller_.MouseDown(p);
        
    //if (mouse_point_ == NULL)
    //{
    //    mouse_point_ = GFort::Core::Physics::PhysicsHelper::CreateCircle(
    //        phys_controller_.World(),
    //        b2_staticBody,
    //        p,
    //        10);
    //}    
    //
    //mouse_world_ = b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
    //b2MouseJointDef md;
    //{   
    //    md.bodyA = mouse_point_;
    //    md.bodyB = player_.Body();
    //    md.target = mouse_world_;
    //    
    //    //md.maxForce = (player_.Body()->GetMass() < 16.0)? (1000.0f * player_.Body()->GetMass()) : float32(16000.0);        
    //    md.maxForce = 1000.0f * 16;
    //    
    //    mouse_joint_ = (b2MouseJoint*) phys_controller_.World()->CreateJoint(&md);
    //    player_.Body()->SetAwake(true);
    //}    
    return false;
}

void Battle::MouseMove(const b2Vec2& p)
{
    phys_controller_.MouseMove(p);	
}

void Battle::MouseUp(const b2Vec2& p)
{
    phys_controller_.MouseUp(p);	
       
    //if (mouse_joint_)
    //{
    //    phys_controller_.World()->DestroyJoint(mouse_joint_);
    //    mouse_joint_ = NULL;
    //}  
    //if (mouse_point_)
    //{
    //    phys_controller_.World()->DestroyBody(mouse_point_);
    //    mouse_point_ = NULL;
    //}  
}

void Battle::Reset()
{
    Initialize();
}

BPolygon Battle::GetBoundingRegion()
{
    BPolygon polygon;
    const b2Transform& xf = player_.Body()->GetTransform();
    for (b2Fixture* fixture = player_.Body()->GetFixtureList(); 
        fixture; 
        fixture = fixture->GetNext())
	{
		switch (fixture->GetType())
	    {
	    case b2Shape::e_circle:
		    {
			    b2CircleShape* circle = (b2CircleShape*)fixture->GetShape();

			    b2Vec2 center = b2Mul(xf, circle->m_p);
			    float32 radius = circle->m_radius;
			    b2Vec2 axis = xf.R.col1;

			    //m_debugDraw->DrawSolidCircle(center, radius, axis, color);
		    }
		    break;

	    case b2Shape::e_polygon:
		    {
			    b2PolygonShape* poly = (b2PolygonShape*)fixture->GetShape();
			    int32 vertexCount = poly->m_vertexCount;
			    b2Assert(vertexCount <= b2_maxPolygonVertices);
			    b2Vec2 vertices[b2_maxPolygonVertices];
                                
                // Clockwise
                BPoint pt;
                for (int32 i = vertexCount - 1; i >= 0; --i)
			    {
                    vertices[i] = PTM_RATIO * b2Mul(xf, poly->m_vertices[i]);
                    pt.set<0>(vertices[i].x);
                    pt.set<1>(vertices[i].y);
                    boost::geometry::append(polygon, pt);
                }
                if (vertexCount > 1)
                {
                    pt.set<0>(vertices[vertexCount - 1].x);
                    pt.set<1>(vertices[vertexCount - 1].y);
                    boost::geometry::append(polygon, pt);
                }
		    }
		    break;
	    }
	}
    return polygon;
}

void Battle::DoSlice(const Trail& trail)
{
    short combo = 0;

}

void Battle::Update(const float& dt)
{
    phys_controller_.Step(&phys_settings_, dt);
}
    
} // namespace
