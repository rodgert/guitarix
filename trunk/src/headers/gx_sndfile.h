/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */

/* ------- This is the SNDFILE namespace ------- */

#pragma once

#include <sndfile.hh>

namespace gx_sndfile
{
// --------------- a simple resampling status
typedef enum {
	kNoError     = 0,
	kErrorInput  = 1,
	kErrorOutput = 2
} GxResampleStatus;

SNDFILE* openOutputSoundFile(const char*, int,  int);
SNDFILE* openInputSoundFile (const char*, int*, int*, int*);
void     closeSoundFile     (SNDFILE*);

sf_count_t writeSoundOutput(SNDFILE*, float*, int);
sf_count_t readSoundInput  (SNDFILE*, float*, int);

GxResampleStatus resampleSoundFile(const char*, const char*, int);

} /* end of gx_sndfile namespace */
