#pragma once
//------------------------------------------------------------------------------
//
//   Copyright 2018-2020 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "core/periodic_runnable.hpp"

#include <functional>

namespace fetch {
namespace core {

/**
 * Simple wrapper around a periodic function that can be submitted to a reactor
 */
class PeriodicFunctor : public PeriodicRunnable
{
public:
  using Callback = std::function<void()>;

  // Construction / Destruction
  template <typename Class>
  PeriodicFunctor(std::string const &name, Duration const &interval, Class *instance,
                  void (Class::*member_function)());
  PeriodicFunctor(std::string const &name, Duration const &interval, Callback callback);
  PeriodicFunctor(PeriodicFunctor const &) = delete;
  PeriodicFunctor(PeriodicFunctor &&)      = delete;
  ~PeriodicFunctor() override              = default;

  void Periodically() override;

  // Operators
  PeriodicFunctor &operator=(PeriodicFunctor const &) = delete;
  PeriodicFunctor &operator=(PeriodicFunctor &&) = delete;

private:
  Callback callback_;
};

template <typename Class>
PeriodicFunctor::PeriodicFunctor(std::string const &name, Duration const &interval, Class *instance,
                                 void (Class::*member_function)())
  : PeriodicFunctor(name, interval,
                    [instance, member_function]() { (instance->*member_function)(); })
{}

}  // namespace core
}  // namespace fetch
