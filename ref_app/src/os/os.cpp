﻿///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <iterator>

#include <mcal_irq.h>
#include <os/os.h>
#include <os/os_task_control_block.h>

namespace local
{
  using task_list_type  = std::array<os::task_control_block, OS_TASK_COUNT>;

  using task_index_type = std::uint_fast8_t;

  // The one (and only one) operating system task list.
  task_list_type os_task_list(OS_TASK_LIST); // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cert-err58-cpp)

  // The index of the running task.
  task_index_type os_task_index; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
} // namespace local

OS_NORETURN auto os::start_os() -> void
{
  // Initialize each task once (and only once) before the task scheduling begins.
  const auto it_init_func = std::for_each(local::os_task_list.cbegin(),
                                          local::os_task_list.cend(),
                                          [](const task_control_block& the_tcb)
                                          {
                                            the_tcb.initialize();
                                          });

  static_cast<void>(it_init_func);

  // Initialize the idle task.
  OS_IDLE_TASK_INIT();

  // Enter the endless loop of the multitasking scheduler...
  // ...and never return.
  for(;;)
  {
    // Find the next ready task using a priority-based search algorithm.
    // Use a constant time-point based on the timer mark of now.
    // In this way, each task in the loop will be checked for being
    // ready using the same time-point.

    const os::tick_type timepoint_of_ckeck_ready = os::timer_type::get_mark();

    local::os_task_index = static_cast<local::task_index_type>(0U);

    const auto it_ready_task = // NOLINT(llvm-qualified-auto,readability-qualified-auto)
      std::find_if(local::os_task_list.begin(),
                   local::os_task_list.end(),
                   [&timepoint_of_ckeck_ready](task_control_block& tcb) // NOLINT(modernize-use-trailing-return-type)
                   {
                     const auto task_is_ready = tcb.execute(timepoint_of_ckeck_ready);

                     ++local::os_task_index;

                     return task_is_ready;
                   });

    // If no ready-task was found, then service the idle task.
    if(it_ready_task == local::os_task_list.end())
    {
      OS_IDLE_TASK_FUNC();
    }
  }
}

auto os::set_event(const task_id_type task_id, const event_type& event_to_set) -> bool
{
  bool result_set_is_ok { };

  if(task_id < task_id_type::task_id_end)
  {
    // Get the iterator of the control block corresponding to
    // the task id that has been supplied to this subroutine.
    const auto it_task_id = (  local::os_task_list.begin() // NOLINT(llvm-qualified-auto,readability-qualified-auto)
                             + static_cast<local::task_list_type::size_type>(task_id));

    // Set the event of the corresponding task.
    mcal::irq::disable_all();

    it_task_id->my_event |= event_to_set;

    mcal::irq::enable_all();

    result_set_is_ok = true;
  }

  return result_set_is_ok;
}

auto os::get_event(event_type& event_to_get) -> void
{
  // Get the iterator of the control block of the running task.
  const auto it_running_task = (local::os_task_list.cbegin() + local::os_task_index); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

  if(it_running_task != local::os_task_list.cend())
  {
    // Get the event of the running task.
    mcal::irq::disable_all();

    const volatile event_type the_event = it_running_task->my_event;

    mcal::irq::enable_all();

    event_to_get = the_event;
  }
  else
  {
    event_to_get = event_type { };
  }
}

auto os::clear_event(const event_type& event_to_clear) -> void
{
  // Get the iterator of the control block of the running task.
  const auto it_running_task = (local::os_task_list.begin() + local::os_task_index); // NOLINT(llvm-qualified-auto,readability-qualified-auto)

  if(it_running_task != local::os_task_list.end())
  {
    volatile const auto event_clear_mask = static_cast<event_type>(~event_to_clear);

    // Clear the event of the running task.
    mcal::irq::disable_all();

    it_running_task->my_event = static_cast<event_type>(it_running_task->my_event & event_clear_mask);

    mcal::irq::enable_all();
  }
}
