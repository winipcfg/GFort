#ifndef GFORT_POOL_H_
#define GFORT_POOL_H_

#include <map>
#include <stack>
#include <string>

namespace GFort 
{
    
/// Pool for resource management
class Pool
{    
public:
    typedef std::stack<void*>                       QueueType;      
    typedef std::map<std::string, QueueType >       ContainerType;
    typedef std::pair<std::string, QueueType >      ContainerPairType;

public:
    /// Constructor
    Pool() {}

    //template<typename ObjectType>
    //std::stack<ObjectType*> GetContainer() const
    //{
    //    std::string name(typeid(ObjectType).name());
    //    ContainerType::const_iterator it = containers_.find(name);
    //    if (it != containers_.end())
    //    {
    //        std::stack<ObjectType*> queue = reinterpret_cast<std::stack<ObjectType*> >(it->second);
    //        return queue;
    //    }
    //    else
    //    {
    //        QueueType queue;
    //        it = containers_.begin();
    //        containers_.insert(it, ContainerPairType(name, queue));
    //        return queue;
    //    }
    //}
    //
    //template <typename ObjectType>
    //void Push(ObjectType* object)
    //{
    //    std::stack<ObjectType*> queue = GetContainer<ObjectType>();        
    //    queue.push(object);
    //}

    template <typename ObjectType>
    void Push(ObjectType* object)
    {
        std::string name(typeid(ObjectType).name());
        ContainerType::iterator it;
        it = containers_.find(name);
        if (it != containers_.end())
        {
            it->second.push(object);
        }
        else
        {
            QueueType queue;
            queue.push(object);
            it = containers_.begin();
            containers_.insert(it, ContainerPairType(name, queue));
        }
    }


    template <typename ObjectType>
    ObjectType* Pop()
    {
        std::string name(typeid(ObjectType).name());
        ContainerType::iterator it;
        it = containers_.find(name);
        if (it != containers_.end())
        {
            if (!it->second.empty())
            {
                void* obj = it->second.top();
                ObjectType* object = static_cast<ObjectType*>(obj);
                it->second.pop();
                return object;
            }
            else
            {
                return new ObjectType();
            }
        }
        else
        {
            return new ObjectType();
        }
    }

private:
    // Stores containers for unused items
    ContainerType       containers_;
};

// ERROR
///// Pool for resource management
//class Pool
//{    
//public:
//    typedef std::map<std::string, std::stack<void*> >           ContainerType;
//    typedef std::pair<std::string, std::stack<void*> >          ContainerPairType;
//
//public:
//    /// Constructor
//    Pool() {}
//
//    template <typename ObjectType>
//    void Push(ObjectType object)
//    {
//        std::stack<ObjectType> container = GetContainer<ObjectType>();
//        container.push(object);
//    }
//
//    template<typename ObjectType>
//    std::stack<ObjectType> GetContainer() const
//    {
//        std::string name(typeid(ObjectType).name());
//        ContainerType::const_iterator it = containers_.find(name);
//        if (it != containers_.end())
//        {
//            return std::stack<ObjectType>((const std::stack<ObjectType>&)it->second);
//        }
//        else
//        {
//            std::stack<ObjectType> container;
//            it = containers_.begin();
//            ContainerPairType pair = ContainerPairType(name, container);
//            containers_.insert(it, pair);
//            return container;
//        }        
//
//        std::stack<ObjectType> container;
//        return container;
//    }
//
//private:
//    // Stores containers for unused items
//    ContainerType       containers_;
//};

} // namespace

#endif // GFORT_POOL_H_
