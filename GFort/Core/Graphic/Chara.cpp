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

#include "Chara.h"

#include <cassert>

namespace GFort { namespace Core { namespace Graphic
{

	
const short kDefaultCharaSequence[] = { 1, 2, 1, 0 };
const short kDefaultCharaSequenceXP[] = { 0, 1, 2, 3, 2, 1 };

void Chara::Initialize(Charaset* charaset, short charaIndex)
{
    assert(charaset != NULL);
        
    p_charaset_ = charaset;
    SetCharaIndex(charaIndex);
    chara_direction_ = kDown;

	if (p_charaset_->GetCharasetVersion() == kRMXP)
    {
		p_motion_sequence_ = kDefaultCharaSequenceXP;
        num_motions_in_sequence_ = sizeof(kDefaultCharaSequenceXP) / sizeof(*kDefaultCharaSequenceXP);
    }
	else
    {
		p_motion_sequence_ = kDefaultCharaSequence;
        num_motions_in_sequence_ = sizeof(kDefaultCharaSequence) / sizeof(*kDefaultCharaSequence);
    }
}
    
void Chara::SetCharaIndex(short charaIndex)
{
    if (chara_index_ != charaIndex)
    {
        chara_index_ = charaIndex;
        needs_update_tile_index_ = true;
    }
}
    
void Chara::SetDirection(CharaDirection charaDirection)
{
    if (chara_direction_ != charaDirection)
    {
        chara_direction_ = charaDirection;
        needs_update_tile_index_ = true;
    }
}

void Chara::StepForward()
{
    this->Step(1);
}

void Chara::StepBackward()
{
    this->Step(-1);
}

void Chara::Step(const short& numSteps)
{
    // Shift the sequence index, and update the motion
    motion_sequence_index_ = (short)((num_motions_in_sequence_ + motion_sequence_index_ + numSteps) 
                                    % num_motions_in_sequence_);
    motion_index_ = p_motion_sequence_[motion_sequence_index_];

    needs_update_tile_index_ = true;
}

} } } // namespace
