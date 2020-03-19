/******************************************************************************
*  Filename:       i2s_doc.h
*  Revised:        $$
*  Revision:       $$
*
*  Copyright (c) 2015 - 2017, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/
//! \addtogroup i2s_api
//! @{
//! \section sec_i2s Introduction
//!
//! The I2S API provides a set of functions for using the I2S module.
//! This module provides a standardized serial interface to transfer
//! audio samples from and to external audio devices such as a codec,
//! DAC, or ADC.
//!
//! The I2S module has the following features:
//!  - Audio clock signals are internally generated by the PRCM module
//!    or externally by another device.
//!  - One or two data pins, which can be configured independently as
//!    input or output
//!  - Various data formats according to the settings of the module
//!  - Up to two channels per data pin for dual phase formats and up
//!    to eight channels per data pin for single phase formats
//!  - DMA with double-buffered pointers
//!  - Error detection for DMA and audio clock signal integrity
//!  - A Samplestamp generator that allows maintaining of constant
//!    audio latency
//!
//! The I2S module is configured through the functions \ref I2SFormatConfigure(),
//! \ref I2SFrameConfigure() and \ref I2SWclkConfigure().
//! Transfers are enabled using \ref I2SStart(). Transfers are disabled  using
//! \ref I2SStop(). Please note that a specific procedure exists in order
//! to disable transfers without losing data (refer to \ref I2SStop()).
//!
//! Data are transmitted using the two double-buffered pointers.
//! For each interface, two registers are set with the address of the data to
//! transfer. These registers are named INPTR and INPTRNEXT for the input
//! interface and OUTPTR and OUTPTRNEXT for the output. When PTR is consumed,
//! the hardware copies the content of PTRNEXT into PTR and the next transfer
//! begins.
//! The address of the next value to write or to read in memory (i.e. to receive
//! or to send out) is set using \ref I2SInPointerSet() and \ref I2SOutPointerSet().
//! The values contented by INPTRNEXT, OUTPTRNEXT, INPTR and OUTPTR can be read using
//! \ref I2SInPointerNextGet(), \ref I2SOutPointerNextGet(), \ref I2SInPointerGet() and
//! \ref I2SOutPointerGet() functions.
//!
//! Interrupts can help the user to refresh pointers on time. Interrupts can also
//! be used to detect I2S errors. \ref I2SIntEnable() and \ref I2SIntDisable()
//! activate and deactivate interrupt(s). Interrupt status can be read through
//! \ref I2SIntStatus() and a pending interrupt can be acquitted by
//! \ref I2SIntClear() function.
//!
//! The sample stamps generator can be configured to slightly delay the
//! emission or the reception of the data (based on the number of WCLK
//! cycles) using \ref I2SSampleStampInConfigure(), \ref I2SSampleStampOutConfigure(),
//! \ref I2SWclkCounterReset() and \ref I2SWclkCounterConfigure(). The current sample stamp
//! can be computed using \ref I2SSampleStampGet().
//! To finish, the sample stamps generator can be enable and disable using
//! the following functions: \ref I2SSampleStampEnable() and
//! \ref I2SSampleStampDisable().
//! The sample stamps generator must be enabled prior to any transfer.
//!
//! Note: Other functions contained in the PRCM API are required to handle I2S.
//!
//! \section sec_i2s_api API
//!
//! Two APIs are coexisting.
//! It is recommended to only use the new API as the old one is deprecated and
//! will be removed soon.
//!
//! New API:
//!   Functions to perform I2S configuration:
//!   - \ref I2SStart()
//!   - \ref I2SStop()
//!   - \ref I2SFormatConfigure()
//!   - \ref I2SFrameConfigure()
//!   - \ref I2SWclkConfigure()
//!
//!   Functions to perform transfers:
//!   - \ref I2SInPointerSet()
//!   - \ref I2SOutPointerSet()
//!   - \ref I2SInPointerGet()
//!   - \ref I2SOutPointerGet()
//!   - \ref I2SInPointerNextGet()
//!   - \ref I2SOutPointerNextGet()
//!
//!   Functions to handle interruptions:
//!   - \ref I2SIntEnable()
//!   - \ref I2SIntDisable()
//!   - \ref I2SIntStatus()
//!   - \ref I2SIntClear()
//!
//!   Functions to handle sample stamps
//!   - \ref I2SSampleStampEnable()
//!   - \ref I2SSampleStampDisable()
//!   - \ref I2SSampleStampInConfigure()
//!   - \ref I2SSampleStampOutConfigure()
//!   - \ref I2SSampleStampGet()
//!   - \ref I2SWclkCounterConfigure()
//!   - \ref I2SWclkCounterReset()
//!
//! Old API:
//!   \ref I2SEnable(), \ref I2SDisable(), \ref I2SAudioFormatConfigure(),
//!   \ref I2SChannelConfigure(), \ref I2SClockConfigure(),
//!   \ref I2SBufferConfig(), \ref I2SIntEnable(), \ref I2SIntDisable(),
//!   \ref I2SIntStatus(), \ref I2SIntClear(), \ref I2SSampleStampEnable(),
//!   \ref I2SSampleStampDisable(), \ref I2SSampleStampGet(),
//!   \ref I2SPointerSet (), \ref I2SPointerUpdate(),
//!   \ref I2SSampleStampConfigure(), \ref I2SIntRegister(),
//!   \ref I2SIntUnregister()
//!
//! @}
