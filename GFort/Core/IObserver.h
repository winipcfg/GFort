#ifndef GFORT_IOBSERVER_H_
#define GFORT_IOBSERVER_H_

#include <list>
#include <string>

namespace GFort
{

typedef std::string State;

class IObserver;

//=================================================================================
/// Subject Interface
class ISubject
{
public:
    /// Destructor
    virtual ~ISubject();

    /// Attach observer to the subject
    /// @param observer
    virtual void Attach(IObserver* observer);

    /// Detach observer from the subject
    /// @param observer
    virtual void Detach(IObserver* observer);

    /// Notify all observers that the subject is updated
    virtual void Notify();

    virtual void SetState(const State& state) = 0;

    virtual State GetState() const = 0;

protected:
    /// Constructor
    ISubject();

private:
    // Stores list of observer
    std::list<IObserver* > observer_list_;
};

void ISubject::Attach(IObserver* observer)
{
    if (observer != NULL)
        observer_list_.push_back(observer);
}

void ISubject::Detach(IObserver* observer)
{
    if (observer != NULL)
        observer_list_.remove(observer);
}

void ISubject::Notify()
{
    std::list<IObserver* >::iterator it;
    for (it = observer_list_.begin(); it != observer_list_.end(); ++it)
    {
        (*it)->Update(this);
    }
}

//=================================================================================
/// Observer Interface
class IObserver
{
public:
    /// Constructor
    /// @param subject The object to observe
    IObserver(ISubject* subject);

    /// Destructor
    virtual ~IObserver();

    /// Update observer
    /// @param subject The subject that notify the observer
    virtual void Update(ISubject* subject);
    
protected:
    /// Constructor
    IObserver();

    ISubject*   subject_;
    State       state_;

private:

};

IObserver::IObserver(ISubject* subject)
{
    subject_ = subject;
    subject_->Attach(this);
}

IObserver::~IObserver()
{
    subject_->Detach(this);
}

void IObserver::Update(ISubject* subject)
{
    state_ = subject->GetState();
}

} // namespace

#endif //GFORT_IOBSERVER_H_
