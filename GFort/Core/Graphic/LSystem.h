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

#ifndef GFORT_CORE_GRAPHIC_L_SYSTEM_H_
#define GFORT_CORE_GRAPHIC_L_SYSTEM_H_

 
#include <map>
#include <string>

namespace GFort { namespace Core { namespace Graphic
{

/// Simple L-System
class LSystem  
{
public:
    typedef char                                Element;
    typedef std::string                         Sequence;
    typedef std::map<Element, Sequence>         Rules;
    typedef std::pair<Element, Sequence>        RulePair;

public:
    /// Iterate L-System
    /// @param axiom
    /// @param rules
    /// @param steps
    /// @param angle Angle in degree
    static std::string Iterate(const Sequence& axiom, 
                               const Rules& rules, 
                               const int& steps,
                               const float& angle);

public:  
    /// Constructor
    LSystem();  

    /// Destructor
    ~LSystem();  
    
    /// Gets the axiom of the system
    Sequence Axiom() const                      { return axiom_; }  

    /// Sets the axiom of the system
    /// @param axiom
    void SetAxiom(const Sequence& axiom)        { axiom_ = axiom; Reset(); }
        
    /// Add a new rule to the system
    /// @param from
    /// @param to
    void AddRule(const Element& from, const Sequence& to);  

    /// Gets current state
    std::string State() const                   { return state_; }

    /// Reset state
    void Reset();
    
    /// Iterate
    void Iterate();

    /// Iterate
    /// @param numSteps
    void Iterate(const int& numSteps);

private:
    // Stores L-System definition
    Sequence            axiom_;
    Rules               rules_;

    // Stores current state of L-System
    std::string         state_;
    int                 num_iterations_;
};  


inline std::string LSystem::Iterate(
    const std::string& axiom, 
    const Rules& rules, 
    const int& steps,                       
    const float& angle)
{
    std::string temp = "";
    
    if (steps <= 0)
        return axiom;
    
    Rules::const_iterator it;
    std::string state = Iterate(axiom, rules, steps - 1, angle);
    for (unsigned int i = 0; i < state.size(); ++i)
    {
        Element e = state[i];
        it = rules.find(e);
        if (it != rules.end())
            temp += (*it).second;
        else
            temp += e;
    }
    return temp;
}


inline LSystem::LSystem()
{
    Reset();
}

inline LSystem::~LSystem()
{
}
        
inline void LSystem::AddRule(const Element& from, const Sequence& to)
{
    if (rules_.find(from) == rules_.end())
    {
        rules_.insert(RulePair(from, to));
        Reset();
    }
}

inline void LSystem::Reset()
{
    state_ = axiom_;
    num_iterations_ = 0;
}

inline void LSystem::Iterate()
{
    std::string temp = "";
    
    Rules::iterator it;
    for (unsigned int i = 0; i < state_.size(); ++i)
    {
        Element e = state_[i];
        it = rules_.find(e);
        if (it != rules_.end())
            temp += (*it).second;
        else
            temp += e;
    }

    state_ = temp;
    num_iterations_++;
}

inline void LSystem::Iterate(const int& numSteps)
{
    for (int i = 0; i < numSteps; ++i)
    {
        Iterate();
    }
}
  
//void initLSystem()
//{
//    LSystem ls;
//    ls.SetAxiom("A");
//    ls.AddRule('A', "AB");
//    ls.AddRule('B', "A");
//
//    for (int i=0;i<8;++i)
//    {
//        std::string s = ls.Iterate("A", i);
//        std::cout << "n = " << i << s << std::endl << std::endl;
//    }
//
//    LSystem ls;
//    ls.SetAxiom("A");
//    ls.AddRule('A', "B");
//    ls.AddRule('B', "AB");
//
//    for (int i=0;i<8;++i)
//    {
//        std::string s = ls.Iterate("A", i);
//        std::cout << "n = " << i << s << std::endl << std::endl;
//    }
//
//    LSystem ls;
//    ls.SetAxiom("F");
//    ls.AddRule('F', "F+F-F-F+F");
//
//    for (int i=0;i<4;++i)
//    {
//        std::string s = ls.Iterate("F", i);
//        std::cout << "n = " << i << s << std::endl << std::endl;
//    }
//}

} } } // namespace

#endif // GFORT_CORE_GRAPHIC_L_SYSTEM_H_
