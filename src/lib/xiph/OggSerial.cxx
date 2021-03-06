/*
 * Copyright 2003-2016 The Music Player Daemon Project
 * http://www.musicpd.org
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "OggSerial.hxx"
#include "system/Clock.hxx"
#include "Compiler.h"

#include <atomic>

static std::atomic_uint next_ogg_serial;

int
GenerateOggSerial()
{
	unsigned serial = ++next_ogg_serial;
	if (gcc_unlikely(serial < 16)) {
		/* first-time initialization: seed with a clock value,
		   which is random enough for our use */

		/* this code is not race-free, but good enough */
		const unsigned seed = MonotonicClockMS();
		next_ogg_serial = serial = seed;
	}

	return serial;
}

