///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_PWM_BASE_2020_04_12_H
  #define MCAL_PWM_BASE_2020_04_12_H

  #include <cstdint>

  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace pwm {

  class pwm_base : private util::noncopyable
  {
  public:
    virtual ~pwm_base() noexcept = default;

    virtual auto init() noexcept -> bool = 0;

    virtual auto set_duty(const std::uint16_t duty_cycle) noexcept -> void { my_duty_cycle = duty_cycle; }

    auto get_duty() const noexcept -> std::uint16_t { return my_duty_cycle; }

  protected:
    pwm_base() noexcept = default;

  private:
    std::uint16_t my_duty_cycle { };
  };

  } // namespace pwm
  } // namespace mcal

#endif // MCAL_PWM_BASE_2020_04_12_H
