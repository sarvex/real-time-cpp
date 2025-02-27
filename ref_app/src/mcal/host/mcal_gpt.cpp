///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <chrono>
#include <cstdint>
#include <thread>

#include <mcal_gpt.h>

namespace local
{
  using mcal_gpt_time_point_type = std::chrono::high_resolution_clock::time_point;

  auto mcal_gpt_time_point_init() noexcept -> const mcal_gpt_time_point_type&;

  std::uint_fast16_t mcal_gpt_sleep_prescaler; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
} // namespace local

auto local::mcal_gpt_time_point_init() noexcept -> const mcal_gpt_time_point_type&
{
  static const mcal_gpt_time_point_type init = std::chrono::high_resolution_clock::now();

  return init;
}

auto mcal::gpt::secure::get_time_elapsed() -> mcal::gpt::value_type
{
  ++local::mcal_gpt_sleep_prescaler;

  if((local::mcal_gpt_sleep_prescaler % UINT16_C(8192)) == 0U)
  {
    // Sleep in order to reduce the load on a PC target.
    std::this_thread::sleep_for(std::chrono::milliseconds(3U));
  }
  else
  {
    std::this_thread::yield();
  }

  const std::chrono::microseconds duration_in_microseconds =
    std::chrono::duration_cast<std::chrono::microseconds>
      (std::chrono::high_resolution_clock::now() - local::mcal_gpt_time_point_init());

  // Return the system tick with a resolution of 1us.
  return static_cast<mcal::gpt::value_type>(duration_in_microseconds.count());
}
