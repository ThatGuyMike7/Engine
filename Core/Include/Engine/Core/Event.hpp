#ifndef ENGINE_CORE_EVENT_INCLUDED
#define ENGINE_CORE_EVENT_INCLUDED

#include <Engine/Core/Common.hpp>
#include <functional>
#include <algorithm>
#include <string>

namespace Engine::Core
{
    template <typename EventDataT>
    class EventOwner;

    template <typename EventDataT>
    class EventHandler
    {
        friend class EventOwner<EventDataT>;

    public:
        /**
         * We use vanilla function pointers because `std::function` is not comparable.
         */
        using EventFunctionT = void (*)(EventDataT const&);

        EventHandler(EventFunctionT eventFunction)
                : eventFunction(eventFunction)
        {
            ENGINE_ASSERT(eventFunction != nullptr);
        }

        // `friend` makes this a non-member function with access to private fields.
        friend bool operator==(EventHandler const &lhs, EventHandler const &rhs)
        {
            return lhs.eventFunction == rhs.eventFunction;
        }

    private:
        EventFunctionT eventFunction;
    };

    template <typename EventDataT>
    class Event
    {
        friend class EventOwner<EventDataT>;

    public:
        /**
         * Add an event handler. If the event handler already exists, do nothing.
         * \returns `true` if the event handler was added, otherwise `false`.
         */
        bool Subscribe(EventHandler<EventDataT> const eventHandler)
        {
            auto it = std::find(eventHandlers.begin(), eventHandlers.end(), eventHandler);
            if (it != eventHandlers.end())
            {
                return false;
            }
            eventHandlers.push_back(eventHandler);
            return true;
        }

        /**
         * \returns `true` if the event handler was removed, otherwise `false`.
         */
        bool Unsubscribe(EventHandler<EventDataT> const eventHandler)
        {
            auto it = std::find(eventHandlers.begin(), eventHandlers.end(), eventHandler);
            if (it != eventHandlers.end())
            {
                eventHandlers.erase(it);
                return true;
            }
            return false;
        }

    private:
        Event() = default;

        std::vector<EventHandler<EventDataT>> eventHandlers;
    };

    template <typename EventDataT>
    class EventOwner
    {
    public:
        void Fire(EventDataT eventData)
        {
            for (auto &&eventHandler : event.eventHandlers)
            {
                eventHandler.eventFunction(eventData);
            }
        }

        Event<EventDataT>& GetEvent()
        {
            return event;
        }

    private:
        Event<EventDataT> event;
    };
}

#endif
