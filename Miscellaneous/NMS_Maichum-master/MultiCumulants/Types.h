#ifndef MULTICUMULANTS_TYPES_H
#define MULTICUMULANTS_TYPES_H

#include <vector>
#include <unordered_map>
#include <bitset> 
#include <complex>

#define MAX_SET_SIZE 8

/**
 * @file   correlations/Types.hh
 * @author Christian Holm Christensen <cholm@nbi.dk>
 * @date   Thu Oct 24 23:45:40 2013
 *
 * @brief  Declarations of types
 */
/*
 * Multi-particle correlations 
 * Copyright (C) 2013 K.Gulbrandsen, A.Bilandzic, C.H. Christensen.
 * 
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 */

typedef double Real;
/** Type of real array */
typedef std::vector<Real> RealVector;
/** Type defintion of the kind of complex we use */
typedef std::complex<Real> Complex;
/** Type definition of our internal storage */
typedef std::vector<Complex> ComplexVector;
/** Type of harmonics */
typedef short Harmonic;
/** Type definition of vector of harmonics **/
typedef std::vector<Harmonic> HarmonicVector;
/** Type of Sizes */
typedef unsigned short Size;
/** Type of Powers */
typedef unsigned short Power;
/** Type of Native QMask **/
typedef unsigned long long NativeMask; 
/** Type of the NativeMask LUT **/
typedef std::vector< std::vector< NativeMask > > NativeMaskLUT;
/** Type of Q Term Coefficient **/
typedef long int Coefficient;
typedef std::vector< Coefficient > CoefficientLUT;
/**
 *  enum to contain the particle charge
**/
enum pCharge {kNeg = -1, kNull = 0, kPos = 1, kCharged = 2, kAll = 3};


#endif
