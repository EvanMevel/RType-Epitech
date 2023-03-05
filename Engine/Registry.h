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

#ifndef R_TYPE_SERVER_REGISTRY_H
#define R_TYPE_SERVER_REGISTRY_H

#include <unordered_map>
#include <memory>

/**
 * @brief Class that stores values in a map with an enum/int as key
 * @tparam Type Type of the values
 */
template<typename Type>
class Registry {
private:
    std::unordered_map<int, std::shared_ptr<Type>> _data;

public:
    template<typename EnumType>
    void registerValue(EnumType key, std::shared_ptr<Type> value) {
        _data[static_cast<int>(key)] = std::move(value);
    }

    template<class EnumType>
    std::shared_ptr<Type> &getValue(EnumType key) {
        return _data[static_cast<int>(key)];
    }
};


#endif //R_TYPE_SERVER_REGISTRY_H
