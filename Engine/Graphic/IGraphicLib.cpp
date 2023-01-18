//
// Created by evans on 18/01/2023.
//

#include "IGraphicLib.h"
#include "Engine.h"

template<class Event>
void IGraphicLib::registerEventConsumer(IConsumer<Event> consumer) {
    this->eventConsumers.insert(std::type_index(typeid(Event)), consumer);
}

template<class Event>
void consumeEvent(Engine engine, Event event, std::any consumer) {
    std::any_cast<IConsumer<Event>&>(consumer).consume(engine, event);
}

void IGraphicLib::processEvents(Engine engine) {
    std::vector<std::any> events = retrieveEvents();
    for (const auto &event: events) {
        auto consumer = eventConsumers.find(std::type_index(typeid(event.type())));
        if (consumer != eventConsumers.end()) {
            consumeEvent(engine, event, consumer->second);
        }
    }
}
