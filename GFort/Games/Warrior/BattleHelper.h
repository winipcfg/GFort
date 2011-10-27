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

#ifndef WARRIOR_BATTLE_HELPER_H_
#define WARRIOR_BATTLE_HELPER_H_

#include <GFort/Core/Physics/PhysicsHelper.h>
#include <GFort/Games/Warrior/Struct.h>
#include <GFort/Games/Warrior/Unit.h>
#include <GFort/Games/Warrior/Enemy.h>
#include <GFort/Games/Warrior/Trail.h>

namespace Warrior 
{

/// Helper class for battle
class BattleHelper
{
public:
    /// Returns clockwise polygon of given b2Body.
    /// @param body
    static BPolygon GetPolygon(const b2Body& body);

    /// Convert to Polygon.
    /// @param minX
    /// @param minY
    /// @param maxX
    /// @param maxY
    static BPolygon ConvertToPolygon(const float& minX, const float& minY, const float& maxX, const float& maxY);

	/// Find units that collide with the trail.
	/// @param trail
	/// @param units
	static std::set<Unit*> Collide(const Trail& trail, std::vector<Unit*>& units);

	/// Find units that collide with the trail.
	/// @param trail
	/// @param units
	static std::set<Enemy*> Collide(const Trail& trail, std::vector<Enemy*>& units);
};

} // namespace

#endif // WARRIOR_BATTLE_HELPER_H_
