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

#include "SpriteSheet.h"

#include <cassert>

namespace GFort { namespace Core { namespace Graphic
{

void SpriteSheet::Initialize(std::string filePath, 
                                short spriteWidth, 
                                short spriteHeight, 
                                short textureWidth, 
                                short textureHeight)
{
    assert(spriteWidth && spriteHeight && textureWidth && textureHeight);
    assert((textureWidth % spriteWidth) == 0);
    assert((textureHeight % spriteHeight) == 0);

    file_path_ = filePath;
    texture_width_ = textureWidth;
    texture_height_ = textureHeight;
    sprite_width_ = spriteWidth;
    sprite_height_ = spriteHeight;
    num_sprites_in_row_ = textureWidth / spriteWidth;
    num_sprites_in_column_ = textureHeight / spriteHeight;
}

Rectangle<short> SpriteSheet::GetSpriteRegion(const short& index) const
{
    short row = (short)(index / num_sprites_in_row_);
    short column = (short)(index % num_sprites_in_row_);

    return GetSpriteRegion(column, row);
}

Rectangle<short> SpriteSheet::GetSpriteRegion(const short& column, const short& row) const
{
    return Rectangle<short>(column * sprite_width_,
                            row * sprite_height_,
                            sprite_width_,
                            sprite_height_);
}


} } } // namespace
