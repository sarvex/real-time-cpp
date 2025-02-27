﻿///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_REG_ACCESS_STATIC_2010_12_01_H_
  #define MCAL_REG_ACCESS_STATIC_2010_12_01_H_

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Warray-bounds"
  #endif

  namespace mcal
  {
    namespace reg
    {
      template<typename RegisterAddressType,
               typename RegisterValueType,
               const RegisterAddressType address,
               const RegisterValueType value = static_cast<RegisterValueType>(UINT8_C(0))>
      struct reg_access_static final
      {
        using register_value_type   = RegisterValueType;
        using register_address_type = RegisterAddressType;

        static register_value_type
                    reg_get() { volatile register_value_type* pa = reinterpret_cast<register_value_type*>(address); return *pa; }

        static void reg_set() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa =       value; }
        static void reg_and() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & value; }
        static void reg_or () { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa | value; }
        static void reg_not() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & register_value_type(~value); }

        template<const register_value_type mask_value>
        static void reg_msk()
        {
          volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address);

          *pa =
            register_value_type
            (
                register_value_type(reg_get() & register_value_type(~mask_value))
              | register_value_type(value & mask_value)
            );
        }

        static void bit_set() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa | static_cast<register_value_type>(1ULL << value); }
        static void bit_clr() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa & static_cast<register_value_type>(~static_cast<register_value_type>(1ULL << value)); }
        static void bit_not() { volatile register_value_type* pa = reinterpret_cast<volatile register_value_type*>(address); *pa = *pa ^ static_cast<register_value_type>(1ULL << value); }
        static bool bit_get() { return (static_cast<register_value_type>(reg_get() & static_cast<register_value_type>(1ULL << value)) != static_cast<register_value_type>(0U)); }
      };
    }
  }

  #if defined(__GNUC__) && (__GNUC__ >= 12)
  // -Warray-bounds
  #pragma GCC diagnostic pop
  #endif

#endif // MCAL_REG_ACCESS_STATIC_2010_12_01_H_
