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

#ifndef GFORT_CORE_IOBSERVER_H_
#define GFORT_CORE_IOBSERVER_H_

#include <cstdarg>
#include <list>
#include <string>

namespace GFort { namespace Core
{

template <typename T> class ISubject;

//=================================================================================
/// Observer Interface
template <typename T>
class IObserver
{
public:
    /// Constructor.
    IObserver() {}

    /// Destructor.
    virtual ~IObserver() {}

    /// Update observer.
    /// @param subject The subject that notify the observer
    virtual void Update(T* subject) = 0;   
};

//=================================================================================
/// Subject Interface
template <typename T>
class ISubject
{
public:
    /// Destructor.
    virtual ~ISubject();

    /// Attach observer to the subject.
    /// @param observer
    virtual void Attach(IObserver<T>* observer);

    /// Detach observer from the subject.
    /// @param observer
    virtual void Detach(IObserver<T>* observer);

    /// Notify all observers that the subject is updated.
    virtual void Notify();
        
protected:
    /// Constructor.
    ISubject() {}

private:
    // Stores list of observer
    std::list<IObserver<T>* > observer_list_;
};

template <typename T>
inline ISubject<T>::~ISubject()
{
    observer_list_.clear();
}

template <typename T>
inline void ISubject<T>::Attach(IObserver<T>* observer)
{
    if (observer != NULL)
        observer_list_.push_back(observer);
}

template <typename T>
inline void ISubject<T>::Detach(IObserver<T>* observer)
{
    if (observer != NULL)
        observer_list_.remove(observer);
}

template <typename T>
inline void ISubject<T>::Notify()
{
    std::list<IObserver<T>* >::iterator it;
    for (it = observer_list_.begin(); it != observer_list_.end(); ++it)
    {
        (*it)->Update(static_cast<T*>(this));
    }
}

} } // namespace

#endif //GFORT_CORE_IOBSERVER_H_
