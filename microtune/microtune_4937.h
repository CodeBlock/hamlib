/* -*-C++-*-
*******************************************************************************
*
* File:         microtune_4937.h
* Description:  
*
*******************************************************************************
*/

/*
 * Copyright 2001 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef _MICROTUNE_4937_H_
#define _MICROTUNE_4937_H_

/*!
 * \brief abstract class for controlling microtune 4937 tuner module
 */
class microtune_4937 {
public:
  microtune_4937 () :
    i2c_addr (0xC2/2), reference_divider(640), fast_tuning_p (false) {};

  virtual ~microtune_4937 ();

  /*!
   * \brief select RF frequency to be tuned to output frequency.
   * \p freq is the requested frequency in Hz, \p actual_freq
   * is set to the actual frequency tuned.  It takes about 100 ms
   * for the PLL to settle.
   *
   * \returns true iff sucessful.
   */
  bool set_RF_freq (double freq, double *actual_freq);
  
  /*!
   * \returns true iff PLL is locked
   */
  bool pll_locked_p ();
  
  /*!
   * \returns the output frequency of the tuner in Hz.
   */
  double get_output_freq ();

 private:
  //! \returns true iff successful
  virtual bool i2c_write (int addr, const unsigned char *buf, int nbytes) = 0;

  //! \returns number of bytes read or -1 if error
  virtual int i2c_read (int addr, unsigned char *buf, int max_bytes) = 0;

  int	i2c_addr;
  int	reference_divider;
  bool	fast_tuning_p;		/* if set, higher charge pump current:
				   faster tuning, worse phase noise
				   for distance < 10kHz to the carrier */
};


#endif /* _MICROTUNE_4937_H_ */
