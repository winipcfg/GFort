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

#include "GameViewer.h"

#include <cassert>

namespace GFort { namespace Core { namespace Game 
{


GameViewer::GameViewer()
{
    needs_update_ = true;
}

GameViewer::~GameViewer()
{
}

bool GameViewer::Initialize(const short& width, const short& height)
{
    assert(width > 0 && height > 0);
    width_ = width;
    height_ = height;
    Invalidate();
    return true;
}

void GameViewer::Update(const std::string& gameState)
{
    data_ = gameState;
    Invalidate();
}

void GameViewer::Invalidate()
{
    needs_update_ = true;
}

void GameViewer::SetWidth(const short& width)
{
    assert(width > 0);
    if (width_ != width)
    {
        width_ = width;
        Invalidate();
    }
}

void GameViewer::SetHeight(const short& height)
{
    assert(height > 0);
    if (height_ != height)
    {
        height_ = height;
        Invalidate();
    }
}

void GameViewer::Reset()
{
    if (needs_update_)
    {
        asepect_ratio_ = (float) width_ / (float) height_;
        ParseGameState();
        needs_update_ = false;
    }
}

void GameViewer::ParseGameState()
{
}

} } } // namespace
