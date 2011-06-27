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

#ifndef GFORT_CORE_GRAPHIC_CHARA_H_
#define GFORT_CORE_GRAPHIC_CHARA_H_

#include "Charaset.h"

namespace GFort { namespace Core { namespace Graphic
{

enum CharaDirection
{
    kDown,
    kLeft,
    kRight,
    kUp,
};
    
class Chara
{
public:
    void Initialize(Charaset* charaset, short charaIndex);
        
    // Gets chara index
    short CharaIndex()              { return chara_index_; };
        
    // Gets chara direction
    CharaDirection Direction()		{ return chara_direction_; };

    void SetCharaIndex(short charaIndex);
    void SetDirection(CharaDirection charaDirection);

    // Motion
    void StepForward();
    void StepBackward();
    void Step(const short& numSteps);
    void Stop();
    void Pause();
    void Resume();
        
protected:
    short               chara_index_;
    CharaDirection      chara_direction_;
        
private:
    // Stores pointer to charaset
    Charaset*           p_charaset_;
        
    // Stores whether it is needed to update the tile index
    bool                needs_update_tile_index_;

    short               motion_index_;
    const short*        p_motion_sequence_;
    short               num_motions_in_sequence_;
    short               motion_sequence_index_;
};
    

} } } // namespace

#endif // GFORT_GRAPHIC_CHARA_H_
