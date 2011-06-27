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

#ifndef GFORT_CORE_GAME_GAME_VIEWER_H_
#define GFORT_CORE_GAME_GAME_VIEWER_H_

#include <string>

namespace GFort { namespace Core { namespace Game 
{

/// Viewer class of a Game
class GameViewer
{
public:
    /// Constructor
    GameViewer();

    /// Destructor
    ~GameViewer();

    /// Initialize the viewer
    /// @param width The width of the viewer
    /// @param height The height of the viewer
    bool Initialize(const short& width, const short& height);

    /// Update the viewer for the game state
    /// @param gameState The input game state
    void Update(const std::string& gameState);

    /// Invalidate current visual settings. 
    /// Next time when display is needed, the system will reset first
    void Invalidate();

    /// Gets the size of viewer
    short Width()               { return width_; }
    short Height()              { return height_; }

    /// Sets the width of viewer
    /// @param width New width
    virtual void SetWidth(const short& width);

    /// Sets the height of viewer
    /// @param height New height
    virtual void SetHeight(const short& height);

    /// Returns true if it needs update
    bool NeedsUpdate()          { return needs_update_; }
    
    /// Reset all visual settings immediately if update is needed
    virtual void Reset();

protected:
    /// Parse game state and update necessary information
    virtual void ParseGameState();

protected:
    // Stores the input data
    std::string     data_;

    // Stores the width and height of the visual panel
    short           width_;
    short           height_;

private:
    // Stores whether it is needed to update
    bool            needs_update_;

    // Stores the aspect ratio of the region
    float           asepect_ratio_;
};


} } } // namespace

#endif // GFORT_CORE_GAME_GAME_VIEWER_H_
