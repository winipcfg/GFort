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

#include "Charaset.h"

namespace GFort { namespace Core { namespace Graphic 
{

const short kNumTilesPerCharaInRow = 3;
const short kNumTilesPerCharaInColumn = 4;
const short kNumTilesPerCharaInRowXP = 4;
const short kNumTilesPerCharaInColumnXP = 4;

void Charaset::Initialize(CharasetVersion version)
{
    charaset_version_ = version;
    if (version == kRMXP)
    {
        num_sprites_per_chara_in_row_ = kNumTilesPerCharaInRowXP;
        num_sprites_per_chara_in_column_ = kNumTilesPerCharaInColumnXP;
    }
    else 
    {
        num_sprites_per_chara_in_row_ = kNumTilesPerCharaInRow;
        num_sprites_per_chara_in_column_ = kNumTilesPerCharaInColumn;
    }

    num_charas_in_row_ = num_sprites_in_row_ / num_sprites_per_chara_in_row_;
    num_charas_in_column_ = num_sprites_in_column_ / num_sprites_per_chara_in_column_;
}
    
    
short Charaset::GetSpriteIndex(short charaIndex)
{
    short row = charaIndex / num_charas_in_row_;
    short column = charaIndex % num_charas_in_column_;
        
    return (row * num_sprites_per_chara_in_column_ * num_sprites_in_row_ +
            column * num_sprites_per_chara_in_row_);
}


} } } // namespace
