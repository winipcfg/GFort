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

#ifndef GFORT_CORE_GAME_IWEAPON_H_
#define GFORT_CORE_GAME_IWEAPON_H_

namespace GFort { namespace Core { namespace Game 
{

/// Weapon interface
class IWeapon
{
public:
    /// Start attack.
    /// @param currentTime Current time
    /// @param instantAttack If true, the weapon will instantly do an attack if appropiate
    virtual void StartAttack(const double& currentTime, bool instantAttack)= 0;

    /// Stops attack.
    /// @param currentTime Current time
    virtual void StopAttack(const double& currentTime) = 0;

    /// Do a single attack.
    virtual void DoAttack() = 0;

    /// Reset the weapon.
    virtual void Reset() = 0;
};

} } } // namespace

#endif // GFORT_CORE_GAME_IWEAPON_H_
