/*
 * MiracleCast - Wifi-Display/Miracast Implementation
 *
 * Copyright (c) 2013-2014 David Herrmann <dh.herrmann@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>
#include "shl_log.h"
#include "shl_macro.h"

#ifndef MIRACLE_H
#define MIRACLE_H

static inline void cleanup_free(void *p)
{
	free(*(void**)p);
}

static inline void cleanup_sd_bus_message(sd_bus_message **ptr)
{
	sd_bus_message_unref(*ptr);
}

#define _cleanup_free_ _shl_cleanup_(cleanup_free)
#define _cleanup_sd_bus_error_ _shl_cleanup_(sd_bus_error_free)
#define _cleanup_sd_bus_message_ _shl_cleanup_(cleanup_sd_bus_message)

static inline const char *bus_error_message(const sd_bus_error *e, int error)
{
	if (e) {
		if (sd_bus_error_has_name(e, SD_BUS_ERROR_ACCESS_DENIED))
			return "Access denied";
		if (e->message)
			return e->message;
	}

	return strerror(error < 0 ? -error : error);
}

static inline int log_bus_parser(int r)
{
	log_error("cannot parse dbus message: %s", strerror(r < 0 ? -r : r));
	return r;
}

#endif /* MIRACLE_H */