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

#ifndef GFORT_CORE_GRAPHIC_CHARASET_H_
#define GFORT_CORE_GRAPHIC_CHARASET_H_

#include "SpriteSheet.h"

namespace GFort { namespace Core { namespace Graphic
{

// Version of Charaset
enum CharasetVersion {
    kRM2k,
    kRMXP,
    kRMVX,
};
    
            
class Charaset : public SpriteSheet
{
public:
        
    void Initialize(CharasetVersion version);
        
    // Gets number of Chara in a row
    short NumCharasInRow()                      { return num_charas_in_row_; }
        
    // Gets number of Chara in a column
    short NumCharasInColumn()                   { return num_charas_in_column_; }

    // Gets total number of Chara
    short GetTotalCharas()                      { return num_charas_in_row_ * num_charas_in_column_; }
        
    // Gets the tiles index (topleft corner) of given chara index
    short GetSpriteIndex(short charaIndex);

	// Gets the Charaset version
	CharasetVersion GetCharasetVersion() const  { return charaset_version_; }
        
protected:        
	// Version of Charaset
	CharasetVersion     charaset_version_;

    // Number of sprites in row and column for a Chara
    short               num_sprites_per_chara_in_row_;
    short               num_sprites_per_chara_in_column_;
        
    // Number of Charas in row and column for a Charaset
    short               num_charas_in_row_;
    short               num_charas_in_column_;
};

} } } // namespace

#endif // GFORT_CORE_GRAPHIC_CHARASET_H_
