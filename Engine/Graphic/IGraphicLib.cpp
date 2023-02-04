// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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

IGraphicLib::~IGraphicLib() {

}

std::vector<std::function<void()>> &IGraphicLib::getExecs() {
    return execs;
}

