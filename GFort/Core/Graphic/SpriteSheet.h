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

#ifndef GFORT_CORE_GRAPHIC_SPRITE_SHEET_H_
#define GFORT_CORE_GRAPHIC_SPRITE_SHEET_H_

#include <string>
#include <GFort/Core/Structs.h>

namespace GFort { namespace Core { namespace Graphic
{


class SpriteSheet
{
public:
    void Initialize(std::string filePath, 
                    short spriteWidth, 
                    short spriteHeight, 
                    short textureWidth, 
                    short textureHeight);        
        
    // Gets the file path of texture
    std::string FilePath()			{ return file_path_; };
        
    // Gets width and height of texture
    short TextureWidth()			{ return texture_width_; };
    short TextureHeight()			{ return texture_height_; };
        
    // Gets number of sprites in row/column
    short NumSpritesInRow()			{ return num_sprites_in_row_; };
    short NumSpritesInColumn()		{ return num_sprites_in_column_; };
        
    // Gets total number of sprites
    short GetTotalSprites()			{ return num_sprites_in_row_ * num_sprites_in_column_; };

	// Returns the region of a sprite, given the sprite index
	Rectangle<short> GetSpriteRegion(const short& index) const;

	// Returns the region of a sprite, given the column and row index
	Rectangle<short> GetSpriteRegion(const short& column, const short& row) const;
        
protected:
    std::string     file_path_;
        
    short           texture_width_;
    short           texture_height_;

	short           sprite_width_;
    short           sprite_height_;
        
    short           num_sprites_in_row_;
    short           num_sprites_in_column_;
};


} } } // namespace

#endif // GFORT_GRAPHIC_SPRITE_SHEET_H_
