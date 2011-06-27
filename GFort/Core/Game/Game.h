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

#ifndef GFORT_CORE_GAME_GAME_H_
#define GFORT_CORE_GAME_GAME_H_

#include <string>

namespace GFort { namespace Core { namespace Game 
{

/// Class that provide game logic.
class Game
{
public:
    /// Initialize the game.
    virtual bool Initialize() = 0;

    /// Initialize the game.
    /// @param filePath The path of config file
    virtual bool Initialize(const std::string& filePath) = 0;

    /// Takes actions for housekeeping. It should be called whenever necessary.
    virtual bool DoHousekeep() = 0;

    /// Exits the game.
    virtual void ExitGame() = 0;

protected:
private:
};

} } } // namespace

#endif // GFORT_CORE_GAME_GAME_H_