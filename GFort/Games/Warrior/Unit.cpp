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

#include "Unit.h"

namespace Warrior 
{  
    
Unit::Unit()
    : max_lives_(0),
      walk_speed_(0),
      run_speed_(0),
      lives_(0),
      facing_(kFacingRight),
      floating_in_the_air_(false)
{
}

const bool Unit::TakeDamage(const short& damage)
{
    lives_ -= damage;
    return (lives_ > 0);
}

void Unit::Reset()
{
    //max_lives_ = 0;
    //walk_speed_ = 0;
    //run_speed_ = 0;
    lives_ = 1;
    action_.Reset();
    facing_ = kFacingRight;
    floating_in_the_air_ = false;
}

void Unit::IssueCommand(const UnitAction& action, const bool& replace)
{
    if (replace)
    {
        if (this->action_.Interruptible)
        {
            //CCLOG("Replace current action");
            this->action_ = action;
            this->pending_actions_.clear();
            //UpdateAction();
            //UpdateActionLabel();
        }
        else
        {
            //CCLOG("Cannot replace current action as it cannot be interrupted");
        }
    }
    else
    {
        //CCLOG("Push a new pending action");
        this->pending_actions_.push_back(action); 
    }
}
    
} // namespace
