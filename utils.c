/*  Molch, an implementation of the axolotl ratchet based on libsodium
 *  Copyright (C) 2015  Max Bruckner (FSMaxB)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>

#include "utils.h"

void print_hex(const unsigned char * const data, const size_t length, unsigned short width) {
	//buffer for hex string
	unsigned char hex[2 * length + 1];

	if (sodium_bin2hex((char *) hex, 2 * length + 1, data, length) == NULL) {
		fprintf(stderr, "ERROR: Failed printing hex.\n");
		sodium_memzero(hex, sizeof(hex));
		return;
	}

	width += width % 2; //only allow widths that are multiples of three
	size_t i;
	for (i = 0; i < 2 * length; i++) {
		if ((width != 0) && (i % width == 0) && (i != 0)) {
			putchar('\n');
		} else if ((i % 2 == 0) && (i != 0)) {
			putchar(' ');
		}
		putchar(hex[i]);
	}

	putchar('\n');

	//cleanup
	sodium_memzero(hex, sizeof(hex));
}
