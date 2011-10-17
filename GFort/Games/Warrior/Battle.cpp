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

const float32 kWorldWidth           = 960;
const float32 kWorldHeight          = 320;
    
const b2Vec2 kPlayerStartPosition   = b2Vec2(100, 100);
const int kPlayerWidth              = 32;
const int kPlayerHeight             = 48;

const int kPlayerMoveSpeed          = 3;
const int kPlayerRunSpeed           = 5;
    
Battle::Battle()
    : ground_body_(NULL),
      player_body_(NULL),
      mouse_point_(NULL),
      mouse_joint_(NULL)
{
    GFort::Core::Physics::PhysicsController();
		
    phys_controller_.SetDefaultGravity(); 
	
    phys_controller_.World()->SetContinuousPhysics(true);                    
	
    b2BodyDef bodyDef;
    ground_body_ = phys_controller_.World()->CreateBody(&bodyDef);
	
    short boundary = 20;
    GFort::Core::Physics::PhysicsHelper::CreateBoundedArea(
        phys_controller_.World(),
        b2Vec2(boundary, boundary),
        kWorldWidth-boundary*2,
        kWorldHeight-boundary*2); 
        
    this->Reset();
}


Battle::~Battle()
{
    if (phys_controller_.World() != NULL)
    {
        if (ground_body_ != NULL)
        {
            phys_controller_.World()->DestroyBody(ground_body_);
            ground_body_ = NULL;
        }            
    }
}

void Battle::Initialize()
{        
    // Ground
    GFort::Core::Physics::PhysicsHelper::CreateBox(
        phys_controller_.World(),
        b2Vec2(kWorldWidth / 2, 50 / 2),
        kWorldWidth,
        50);

    // Create Player
    player_body_ = GFort::Core::Physics::PhysicsHelper::CreateBox(
                                                phys_controller_.World(),
                                                kPlayerStartPosition,
                                                kPlayerWidth,
                                                kPlayerHeight);

    player_body_->SetFixedRotation(false);
    
    // Set the dynamic body fixture.
	b2Fixture* fixture = player_body_->GetFixtureList();	
	fixture[0].SetDensity(1.0f);
	fixture[0].SetFriction(0.3f);
	fixture[0].SetRestitution(0.4f);	
	player_body_->ResetMassData();

    player_.SetBody(player_body_);    
}
    
bool Battle::MouseDown(const b2Vec2& p)
{
    phys_controller_.MouseDown(p);
        
    if (mouse_point_ == NULL)
    {
        mouse_point_ = GFort::Core::Physics::PhysicsHelper::CreateCircle(
            phys_controller_.World(),
            p,
            10);
        mouse_point_->SetType(b2_staticBody);
    }    
    
    mouse_world_ = b2Vec2(p.x/PTM_RATIO, p.y/PTM_RATIO);
    b2MouseJointDef md;
    {   
        md.bodyA = mouse_point_;
        md.bodyB = player_body_;
        md.target = mouse_world_;
        
        //md.maxForce = (player_->GetMass() < 16.0)? (1000.0f * player_->GetMass()) : float32(16000.0);
        
        md.maxForce = 1000.0f * 16;
        
        mouse_joint_ = (b2MouseJoint*) phys_controller_.World()->CreateJoint(&md);
        player_body_->SetAwake(true);
    }    
    
    
    return false;
}

void Battle::MouseUp(const b2Vec2& p)
{
    phys_controller_.MouseUp(p);	
    
    if (mouse_point_)
    {
        phys_controller_.World()->DestroyBody(mouse_point_);
        mouse_point_ = NULL;
    }    
    if (mouse_joint_)
    {
        phys_controller_.World()->DestroyJoint(mouse_joint_);
        mouse_joint_ = NULL;
    }    
    
}

void Battle::Reset()
{
    Initialize();
}

BPolygon Battle::GetBoundingRegion()
{
    BPolygon polygon;
    const b2Transform& xf = player_body_->GetTransform();
    for (b2Fixture* fixture = player_body_->GetFixtureList(); 
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

    if (player_.CanPerformAttack())
    {
        // 1. For all enemies within the range
        // 1.1. Check whether the trail collides with the enemy. Takes damage if exists
        // 2. Update maximum combo
        // 3. Notify system to play audio
    }

    if (combo > stat_.MaximumCombos)
    {
        stat_.MaximumCombos = combo;
    }
}
    
} // namespace
