/*/////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2018.           */
/*  Distributed under the Boost Software License,          */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt    */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)       */
/*/////////////////////////////////////////////////////////*/

#include <math/checksums/crc/Crc16_CcittFalse.h>
#include <mcal_cpu.h>
#include <mcal/mcal_progmem.h>

void Crc16_CcittFalse_Initialize(Crc16_CcittFalse_Context_Type* Crc_Context)
{
  /* Set the initial value. */
  Crc_Context->Crc_Value = UINT16_C(0xFFFF);
}

void Crc16_CcittFalse_ProcessBytes(const uint8_t*                 DataIn,
                                   const size_t                   DataLength,
                                   Crc16_CcittFalse_Context_Type* Crc_Context)
{
  /* Name            : CRC-16/CCITT-FALSE */
  /* Width in bits   : 16                 */
  /* Polynomial      : 0x1021             */
  /* Initial value   : 0xFFFF             */
  /* Final XOR       : 0x0000             */
  /* Test: '1'...'9' : 0x29B1             */
  /* See also AUTOSAR Version 4.3.        */

  size_t LoopCnt;

  /* Loop through the input data stream */
  for(LoopCnt = 0U; LoopCnt < DataLength; ++LoopCnt)
  {
    /* CRC-16/CCITT-FALSE Table based on 16-bit WORDs. */

    static const uint16_t Crc16_CcittFalse_Table[256U] MY_PROGMEM =
    {
      UINT16_C(0x0000), UINT16_C(0x1021), UINT16_C(0x2042), UINT16_C(0x3063), UINT16_C(0x4084), UINT16_C(0x50A5), UINT16_C(0x60C6), UINT16_C(0x70E7),
      UINT16_C(0x8108), UINT16_C(0x9129), UINT16_C(0xA14A), UINT16_C(0xB16B), UINT16_C(0xC18C), UINT16_C(0xD1AD), UINT16_C(0xE1CE), UINT16_C(0xF1EF),
      UINT16_C(0x1231), UINT16_C(0x0210), UINT16_C(0x3273), UINT16_C(0x2252), UINT16_C(0x52B5), UINT16_C(0x4294), UINT16_C(0x72F7), UINT16_C(0x62D6),
      UINT16_C(0x9339), UINT16_C(0x8318), UINT16_C(0xB37B), UINT16_C(0xA35A), UINT16_C(0xD3BD), UINT16_C(0xC39C), UINT16_C(0xF3FF), UINT16_C(0xE3DE),
      UINT16_C(0x2462), UINT16_C(0x3443), UINT16_C(0x0420), UINT16_C(0x1401), UINT16_C(0x64E6), UINT16_C(0x74C7), UINT16_C(0x44A4), UINT16_C(0x5485),
      UINT16_C(0xA56A), UINT16_C(0xB54B), UINT16_C(0x8528), UINT16_C(0x9509), UINT16_C(0xE5EE), UINT16_C(0xF5CF), UINT16_C(0xC5AC), UINT16_C(0xD58D),
      UINT16_C(0x3653), UINT16_C(0x2672), UINT16_C(0x1611), UINT16_C(0x0630), UINT16_C(0x76D7), UINT16_C(0x66F6), UINT16_C(0x5695), UINT16_C(0x46B4),
      UINT16_C(0xB75B), UINT16_C(0xA77A), UINT16_C(0x9719), UINT16_C(0x8738), UINT16_C(0xF7DF), UINT16_C(0xE7FE), UINT16_C(0xD79D), UINT16_C(0xC7BC),
      UINT16_C(0x48C4), UINT16_C(0x58E5), UINT16_C(0x6886), UINT16_C(0x78A7), UINT16_C(0x0840), UINT16_C(0x1861), UINT16_C(0x2802), UINT16_C(0x3823),
      UINT16_C(0xC9CC), UINT16_C(0xD9ED), UINT16_C(0xE98E), UINT16_C(0xF9AF), UINT16_C(0x8948), UINT16_C(0x9969), UINT16_C(0xA90A), UINT16_C(0xB92B),
      UINT16_C(0x5AF5), UINT16_C(0x4AD4), UINT16_C(0x7AB7), UINT16_C(0x6A96), UINT16_C(0x1A71), UINT16_C(0x0A50), UINT16_C(0x3A33), UINT16_C(0x2A12),
      UINT16_C(0xDBFD), UINT16_C(0xCBDC), UINT16_C(0xFBBF), UINT16_C(0xEB9E), UINT16_C(0x9B79), UINT16_C(0x8B58), UINT16_C(0xBB3B), UINT16_C(0xAB1A),
      UINT16_C(0x6CA6), UINT16_C(0x7C87), UINT16_C(0x4CE4), UINT16_C(0x5CC5), UINT16_C(0x2C22), UINT16_C(0x3C03), UINT16_C(0x0C60), UINT16_C(0x1C41),
      UINT16_C(0xEDAE), UINT16_C(0xFD8F), UINT16_C(0xCDEC), UINT16_C(0xDDCD), UINT16_C(0xAD2A), UINT16_C(0xBD0B), UINT16_C(0x8D68), UINT16_C(0x9D49),
      UINT16_C(0x7E97), UINT16_C(0x6EB6), UINT16_C(0x5ED5), UINT16_C(0x4EF4), UINT16_C(0x3E13), UINT16_C(0x2E32), UINT16_C(0x1E51), UINT16_C(0x0E70),
      UINT16_C(0xFF9F), UINT16_C(0xEFBE), UINT16_C(0xDFDD), UINT16_C(0xCFFC), UINT16_C(0xBF1B), UINT16_C(0xAF3A), UINT16_C(0x9F59), UINT16_C(0x8F78),
      UINT16_C(0x9188), UINT16_C(0x81A9), UINT16_C(0xB1CA), UINT16_C(0xA1EB), UINT16_C(0xD10C), UINT16_C(0xC12D), UINT16_C(0xF14E), UINT16_C(0xE16F),
      UINT16_C(0x1080), UINT16_C(0x00A1), UINT16_C(0x30C2), UINT16_C(0x20E3), UINT16_C(0x5004), UINT16_C(0x4025), UINT16_C(0x7046), UINT16_C(0x6067),
      UINT16_C(0x83B9), UINT16_C(0x9398), UINT16_C(0xA3FB), UINT16_C(0xB3DA), UINT16_C(0xC33D), UINT16_C(0xD31C), UINT16_C(0xE37F), UINT16_C(0xF35E),
      UINT16_C(0x02B1), UINT16_C(0x1290), UINT16_C(0x22F3), UINT16_C(0x32D2), UINT16_C(0x4235), UINT16_C(0x5214), UINT16_C(0x6277), UINT16_C(0x7256),
      UINT16_C(0xB5EA), UINT16_C(0xA5CB), UINT16_C(0x95A8), UINT16_C(0x8589), UINT16_C(0xF56E), UINT16_C(0xE54F), UINT16_C(0xD52C), UINT16_C(0xC50D),
      UINT16_C(0x34E2), UINT16_C(0x24C3), UINT16_C(0x14A0), UINT16_C(0x0481), UINT16_C(0x7466), UINT16_C(0x6447), UINT16_C(0x5424), UINT16_C(0x4405),
      UINT16_C(0xA7DB), UINT16_C(0xB7FA), UINT16_C(0x8799), UINT16_C(0x97B8), UINT16_C(0xE75F), UINT16_C(0xF77E), UINT16_C(0xC71D), UINT16_C(0xD73C),
      UINT16_C(0x26D3), UINT16_C(0x36F2), UINT16_C(0x0691), UINT16_C(0x16B0), UINT16_C(0x6657), UINT16_C(0x7676), UINT16_C(0x4615), UINT16_C(0x5634),
      UINT16_C(0xD94C), UINT16_C(0xC96D), UINT16_C(0xF90E), UINT16_C(0xE92F), UINT16_C(0x99C8), UINT16_C(0x89E9), UINT16_C(0xB98A), UINT16_C(0xA9AB),
      UINT16_C(0x5844), UINT16_C(0x4865), UINT16_C(0x7806), UINT16_C(0x6827), UINT16_C(0x18C0), UINT16_C(0x08E1), UINT16_C(0x3882), UINT16_C(0x28A3),
      UINT16_C(0xCB7D), UINT16_C(0xDB5C), UINT16_C(0xEB3F), UINT16_C(0xFB1E), UINT16_C(0x8BF9), UINT16_C(0x9BD8), UINT16_C(0xABBB), UINT16_C(0xBB9A),
      UINT16_C(0x4A75), UINT16_C(0x5A54), UINT16_C(0x6A37), UINT16_C(0x7A16), UINT16_C(0x0AF1), UINT16_C(0x1AD0), UINT16_C(0x2AB3), UINT16_C(0x3A92),
      UINT16_C(0xFD2E), UINT16_C(0xED0F), UINT16_C(0xDD6C), UINT16_C(0xCD4D), UINT16_C(0xBDAA), UINT16_C(0xAD8B), UINT16_C(0x9DE8), UINT16_C(0x8DC9),
      UINT16_C(0x7C26), UINT16_C(0x6C07), UINT16_C(0x5C64), UINT16_C(0x4C45), UINT16_C(0x3CA2), UINT16_C(0x2C83), UINT16_C(0x1CE0), UINT16_C(0x0CC1),
      UINT16_C(0xEF1F), UINT16_C(0xFF3E), UINT16_C(0xCF5D), UINT16_C(0xDF7C), UINT16_C(0xAF9B), UINT16_C(0xBFBA), UINT16_C(0x8FD9), UINT16_C(0x9FF8),
      UINT16_C(0x6E17), UINT16_C(0x7E36), UINT16_C(0x4E55), UINT16_C(0x5E74), UINT16_C(0x2E93), UINT16_C(0x3EB2), UINT16_C(0x0ED1), UINT16_C(0x1EF0)
    };

    /* Perform the CRC-16/CCITT-False algorithm. */

    const uint_fast8_t DataIndex =
      (uint_fast8_t) ((uint8_t) (  (Crc_Context->Crc_Value >> 8U)
                                 ^ DataIn[LoopCnt]));

    const uint16_t TableValue =
      mcal_cpu_read_program_memory_word((const uint8_t*) &Crc16_CcittFalse_Table[DataIndex]);

    Crc_Context->Crc_Value = (uint16_t) (Crc_Context->Crc_Value << 8) ^ TableValue;
  }
}

void Crc16_CcittFalse_Finalize(Crc16_CcittFalse_Context_Type* Crc_Context)
{
  (void) Crc_Context;
}
