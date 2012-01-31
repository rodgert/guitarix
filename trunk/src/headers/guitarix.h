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
 *
 *
 *    This is the main guitarix header file. It simply contains the
 *    more specific headers. Note that each header is trying to be
 *    self-contained, i.e. only depends on system declarations.  Let's
 *    try to keep it that way.
 *
 *
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef SRC_HEADERS_GUITARIX_H_
#define SRC_HEADERS_GUITARIX_H_

#include <gtk/gtk.h>
#include <gtkmm.h>

#include "engine.h"

#include "gx_cairo_callbacks.h"

#include "gx_threads.h"
#include "gx_gui_helpers.h"
#include "gx_ui_builder.h"
#include "gx_jack_options.h"
#include "gx_preset_options.h"
#include "gx_jconv_settings.h"
#include "gx_portmap.h"
#include "gx_main_midi.h"
#include "gx_main_boxes.h"
#include "gx_child_process.h"
#include "gx_main_interface.h"

#endif  // SRC_HEADERS_GUITARIX_H_
