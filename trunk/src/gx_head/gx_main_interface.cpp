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
 * ---------------------------------------------------------------------------
 *
 *    This is the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"         // NOLINT


#include <gdk/gdkkeysyms.h>   // NOLINT
#include <glibmm/i18n.h>      // NOLINT

#include <iomanip>            // NOLINT
#include <cstring>            // NOLINT
#include <string>             // NOLINT
#include <gtkmm/menushell.h>
#include <gtkmm/separatormenuitem.h>

namespace gx_gui {

GuiVariables guivar;
// Stock Items for Gxw::Switch

const char *sw_led =             "led";
const char *sw_switch =          "switch";
const char *sw_switchit =        "switchit";
const char *sw_minitoggle =      "minitoggle";
const char *sw_button =          "button";
const char *sw_pbutton =         "pbutton";
const char *sw_rbutton =         "rbutton";

// Paint Functions for Gxw::PaintBox

const char *pb_amp_expose =                  "amp_expose";
const char *pb_conv_widget_expose =          "conv_widget_expose";
const char *pb_upper_widget_expose =         "upper_widget_expose";
const char *pb_rectangle_expose =            "rectangle_expose";
const char *pb_rectangle_skin_color_expose = "rectangle_skin_color_expose";
const char *pb_convolver_icon_expose =       "convolver_icon_expose";
const char *pb_AmpBox_expose =               "AmpBox_expose";
const char *pb_tribal_box_expose =           "tribal_box_expose";
const char *pb_vbox_expose =                 "vbox_expose";
const char *pb_filter_box_expose =           "filter_box_expose";
const char *pb_plug_box_expose =             "plug_box_expose";
const char *pb_info_box_expose_on =          "info_box_expose_on";
const char *pb_info_box_expose_off =         "info_box_expose_off";
const char *pb_slooper_expose =              "slooper_expose";
const char *pb_zac_expose =                  "zac_expose";
const char *pb_gxhead_expose =               "gxhead_expose";
const char *pb_RackBox_expose =              "RackBox_expose";
const char *pb_gxrack_expose =               "gxrack_expose";
const char *pb_eq_expose =                   "eq_expose";
const char *pb_main_expose =                 "main_expose";

/****************************************************************
 ** register GUI parameter to save/load them within the settigs file
 */

inline void registerNonMidiParam(const char*a, float*c, bool d,
                                 float std = 0, float lower = 0, float upper = 1) {
    parameter_map.insert(new FloatParameter(a, "", Parameter::None, d, *c, std,
                                            lower, upper, 0, false));
}

void GuiVariables::register_gui_parameter() {
    registerNonMidiParam("ui.main_xorg",           &main_xorg, true, 300, 0, 10000);
    registerNonMidiParam("ui.main_yorg",           &main_yorg, true, 300, 0, 10000);

    // unused!! for file format compatibility
    ParameterGroups& group = get_group_table();
    group.insert("MultiBandFilter", "");
    group.insert("eq", "");
    static bool dialogbox[3];
    registerNonMidiParam("eq.dialog",              &dialogbox[0],  false);
    registerNonMidiParam("MultiBandFilter.dialog", &dialogbox[1],  false);
    registerNonMidiParam("midi_out.dialog",        &dialogbox[2], false);
    static float viv;
    registerNonMidiParam("system.waveview",          &viv, false);
    parameter_map.insert(new SwitchParameter("system.select_tube", true));
    parameter_map.insert(new SwitchParameter("system.select_tube2", true));
    parameter_map.insert(new SwitchParameter("system.select_tube3", true));
    parameter_map.insert(new SwitchParameter("system.select_tube4", true));
    parameter_map.insert(new SwitchParameter("system.select_tube5", true));
    parameter_map.insert(new SwitchParameter("system.select_tube6", true));
    parameter_map.insert(new SwitchParameter("system.select_tube7", true));
    parameter_map.insert(new SwitchParameter("system.select_tube8", true));
    parameter_map.insert(new SwitchParameter("system.select_tube9", true));
    parameter_map.insert(new SwitchParameter("system.select_tube10", true));
    parameter_map.insert(new SwitchParameter("system.select_tube11", true));
    parameter_map.insert(new SwitchParameter("system.select_tube12", true));
    parameter_map.insert(new SwitchParameter("system.select_tube13", true));
    parameter_map.insert(new SwitchParameter("system.select_tube14", true));
    parameter_map.insert(new SwitchParameter("system.select_tube15", true));
    parameter_map.insert(new SwitchParameter("system.select_tube16", true));
    parameter_map.insert(new SwitchParameter("system.select_tube17", true));
    //---
    static bool dialog[29];
    gx_gui::registerNonMidiParam("IR.dialog", &dialog[0], false);
    gx_gui::registerNonMidiParam("amp.tonestack.dialog", &dialog[1], false);
    gx_gui::registerNonMidiParam("ampmodul.dialog", &dialog[2], false);
    gx_gui::registerNonMidiParam("biquad.dialog", &dialog[3], false);
    gx_gui::registerNonMidiParam("cab.dialog", &dialog[4], false);
    gx_gui::registerNonMidiParam("chorus.dialog", &dialog[5], false);
    gx_gui::registerNonMidiParam("chorus_mono.dialog", &dialog[6], false);
    gx_gui::registerNonMidiParam("compressor.dialog", &dialog[7], false);
    gx_gui::registerNonMidiParam("crybaby.dialog", &dialog[8], false);
    gx_gui::registerNonMidiParam("delay.dialog", &dialog[9], false);
    gx_gui::registerNonMidiParam("echo.dialog", &dialog[10], false);
    gx_gui::registerNonMidiParam("eqs.dialog", &dialog[11], false);
    gx_gui::registerNonMidiParam("feedback.dialog", &dialog[12], false);
    gx_gui::registerNonMidiParam("flanger.dialog", &dialog[13], false);
    gx_gui::registerNonMidiParam("flanger_mono.dialog", &dialog[14], false);
    gx_gui::registerNonMidiParam("freeverb.dialog", &dialog[15], false);
    gx_gui::registerNonMidiParam("gx_distortion.dialog", &dialog[16], false);
    gx_gui::registerNonMidiParam("jconv.dialog", &dialog[17], false);
    gx_gui::registerNonMidiParam("low_highpass.dialog", &dialog[18], false);
    gx_gui::registerNonMidiParam("moog.dialog", &dialog[19], false);
    gx_gui::registerNonMidiParam("oscilloscope.dialog", &dialog[20], false);
    gx_gui::registerNonMidiParam("overdrive.dialog", &dialog[21], false);
    gx_gui::registerNonMidiParam("phaser.dialog", &dialog[22], false);
    gx_gui::registerNonMidiParam("phaser_mono.dialog", &dialog[23], false);
    gx_gui::registerNonMidiParam("stereodelay.dialog", &dialog[24], false);
    gx_gui::registerNonMidiParam("stereoecho.dialog", &dialog[25], false);
    gx_gui::registerNonMidiParam("stereoverb.dialog", &dialog[26], false);
    gx_gui::registerNonMidiParam("tonemodul.dialog", &dialog[27], false);
    gx_gui::registerNonMidiParam("tremolo.dialog", &dialog[28], false);
    // end unused

    show_patch_info = 0;

    /* rack handlig */
    mono_plugs = 1;
    stereo_plugs = 1;
    refresh_size = 0;

    for (unsigned int i = 0; i < sizeof(g_threads)/sizeof(g_threads[0]); i++) g_threads[i] = 0;

    /* for level display */
    meter_falloff = 27; // in dB/sec.
    meter_display_timeout = 60; // in millisec
    /* midi_in preset switch */
    program_change = -1;
}

/****************************************************************
 ** format controller values
 */

int precision(double n) {
    if (n < 0.009999)
        return 3;
    else if (n < 0.099999)
        return 2;
    else if (n < 0.999999)
        return 1;
    else
        return 0;
}

string fformat(float value, float step) {
    ostringstream buf;
    buf << fixed << setprecision(precision(step)) << value;
    return buf.str();
}

/****************************************************************
 ** GxMidiController definitions and connecting method
 */

gboolean button_press_cb(GtkWidget *widget, GdkEventButton *event, gpointer data) {
    if (event->button != 2)
        return FALSE;
    if (controller_map.get_config_mode())
        return TRUE;
    new gx_main_midi::MidiConnect(event, *reinterpret_cast<Parameter*>(data));
    return TRUE;
}


/****************************************************************
 ** GxMainInterface widget and method definitions
 */

/*set global GUI widgets class */
GlobalWidgets gw;

// static member
bool GxMainInterface::fInitialized = false;

/* set initial window position*/
int gx_set_mx_oriantation() {
    return gx_gui::guivar.main_xorg;
}

int gx_set_my_oriantation() {
    return gx_gui::guivar.main_yorg;
}

void GxMainInterface::save_window_position() {
    if (!fWindow.get_visible()) {
	return;
    }
    fWindow.get_position(guivar.main_xorg, guivar.main_yorg);
}

// ----- we must make sure that the images for the status icon be there
static void gx_pixmap_check(gx_system::CmdlineOptions& opt) {
    struct stat my_stat;

    string gx_pix   = opt.get_pixmap_filepath("gx_head.png");
    string midi_pix = opt.get_pixmap_filepath("gx_head-midi.png");
    string warn_pix = opt.get_pixmap_filepath("gx_head-warn.png");

    if ((stat(gx_pix.c_str(), &my_stat) != 0)   ||
        (stat(midi_pix.c_str(), &my_stat) != 0) ||
        (stat(warn_pix.c_str(), &my_stat) != 0)) {
        gx_system::gx_print_fatal("gx_pixmap_check", _("cannot find installed pixmaps"));
    }

    GtkWidget *ibf =  gtk_image_new_from_file(gx_pix.c_str());
    gw.ib = gtk_image_get_pixbuf(GTK_IMAGE(ibf));

    GtkWidget *stim = gtk_image_new_from_file(midi_pix.c_str());
    gw.ibm = gtk_image_get_pixbuf(GTK_IMAGE(stim));

    GtkWidget *stir = gtk_image_new_from_file(warn_pix.c_str());
    gw.ibr = gtk_image_get_pixbuf(GTK_IMAGE(stir));
}


GxMainInterface* GxMainInterface::instance = 0;

/* create main window*/
GxMainInterface::GxMainInterface(gx_engine::GxEngine& engine_, gx_system::CmdlineOptions& options_)
    : fWindow(Gtk::WINDOW_TOPLEVEL),
      options(options_),
      fAccelGroup(fWindow.get_accel_group()),
      portmap_window(0),
      portmap_item(_("Jack _Ports "), true),
      fLoggingWindow(_("Logging Window")),
      fTuner(engine_.tuner),
      engine(engine_),
      jack(engine_),
      gx_settings(options_, jack, engine.convolver, midi_std_ctr, controller_map, engine_),
      report_xrun(jack) {
    engine.set_jack(&jack);
    jack.xrun.connect(sigc::mem_fun(report_xrun, &ReportXrun::run));
    jack.session.connect(sigc::mem_fun(*this, &GxMainInterface::jack_session_event));
    jack.shutdown.connect(sigc::mem_fun(*this, &GxMainInterface::gx_jack_is_down));
    jack.connection.connect(sigc::mem_fun(*this, &GxMainInterface::jack_connection_change));
    gx_settings.signal_selection_changed().connect(
	sigc::mem_fun(*this, &GxMainInterface::on_settings_selection_changed));
    gx_settings.signal_selection_changed().connect(
	sigc::ptr_fun(gx_jconv::gx_reload_jcgui));
    fLoggingWindow.signal_delete_event().connect(
	sigc::mem_fun(*this, &GxMainInterface::on_logger_delete_event));

    fLoggingWindow.set_transient_for(fWindow);

    /*---------------- set window defaults ----------------*/
    // fWindow.size_request(600,205);
    fWindow.set_resizable(false);
    fWindow.set_title("gx_head");
    fWindow.set_gravity(Gdk::GRAVITY_STATIC);

    /*---------------- signals ----------------*/
    fWindow.signal_delete_event().connect(
	sigc::bind_return<bool>(
	    sigc::hide(
		sigc::mem_fun(*this, &GxMainInterface::save_window_position)),
	    false));
    fWindow.signal_delete_event().connect(
	sigc::bind_return<bool>(
	    sigc::hide(sigc::ptr_fun(Gtk::Main::quit)),
	    false));

    /*---------------- status icon ----------------*/
    gx_pixmap_check(options);
    gw.status_icon =    gtk_status_icon_new_from_pixbuf(GDK_PIXBUF(gw.ib));
    fWindow.set_icon(Glib::wrap(GDK_PIXBUF(gw.ib)));
    g_signal_connect(G_OBJECT(gw.status_icon), "activate",
		     G_CALLBACK(gx_hide_extended_settings), this);
    g_signal_connect(G_OBJECT(gw.status_icon), "popup-menu",
		     G_CALLBACK(gx_systray_menu), this);

    /*---------------- create boxes ----------------*/
    fTop = 0;
    fBox[fTop] = gtk_vbox_new(homogene, 4);
    fMode[fTop] = kBoxMode;

    /*---------------- add mainbox to main window ---------------*/
    fWindow.add(*Glib::wrap(fBox[fTop]));

    engine.oscilloscope.post_pre_signal.changed.connect(
	sigc::mem_fun(*this, &GxMainInterface::on_oscilloscope_post_pre));
    engine.oscilloscope.visible.changed.connect(
	sigc::mem_fun(*this, &GxMainInterface::on_show_oscilloscope));
    engine.oscilloscope.activation.connect(
	sigc::mem_fun(*this, &GxMainInterface::on_oscilloscope_activate));
    engine.oscilloscope.size_change.connect(
	sigc::mem_fun(*this, &GxMainInterface::set_waveview_buffer));
    jack.signal_buffersize_change().connect(
	sigc::mem_fun(*this, &GxMainInterface::refresh_latency_menu));

    fStopped = false;
    instance = this;
}

GxMainInterface::~GxMainInterface() {
    engine.start_ramp_down();
    engine.wait_ramp_down_finished();
    engine.set_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    engine.set_jack(0);
    instance = 0;
}

void GxMainInterface::on_settings_selection_changed() {
    string title = gx_settings.get_displayname();
    if (title.empty()) {
	title = jack.get_instancename();
    } else {
	title = jack.get_instancename() + " - " + title;
    }
    fWindow.set_title(title);
}

void GxMainInterface::portmap_connection_changed(string port1, string port2, bool conn) {
    if (portmap_window) {
	portmap_window->connection_changed(port1, port2, conn);
    }
}

void GxMainInterface::jack_connection_change() {
    if (jack.is_jack_exit()) {
        // we bring down jack capture and meterbridge
        gx_child_process::Meterbridge::stop();
        //gx_child_process::JackCapture::stop(); unused
        if (gx_gui::gw.gx_jackd_on_image) {
            gtk_widget_hide(gx_gui::gw.gx_jackd_on_image);
            gtk_widget_show(gx_gui::gw.gx_jackd_off_image);
        }
	gx_system::gx_print_info(_("Jack Server"), _("Disconnected from Jack Server"));
    } else {
	if (gx_gui::gw.gx_jackd_on_image) {
	    gtk_widget_show(gx_gui::gw.gx_jackd_on_image);
	    gtk_widget_hide(gx_gui::gw.gx_jackd_off_image);
	}
	gx_system::gx_print_info(_("Jack Server"), _("Connected to Jack Server"));
    }
}

/****************************************************************
 ** virtual GUI discriptions
 */

// ------- retrieve jack latency menu item
GtkWidget* const GxMainInterface::getJackLatencyItem(jack_nframes_t bufsize) const {
    if (bufsize & (bufsize-1)) {
        return NULL; // not power of 2
    }
    const int minbuf = 5; // 2**5 = 32 // FIXME magic value
    int index = -(minbuf+1);
    while (bufsize) {
        bufsize >>= 1;
        index++;
    }
    if (index >= 0 && index < NJACKLAT) {
        return fJackLatencyItem[index];
    }
    return NULL;
}

// ------- box stacking up
void GxMainInterface::pushBox(int mode, GtkWidget* w) {
    ++fTop;
    assert(fTop < stackSize);
    fMode[fTop]     = mode;
    fBox[fTop]         = w;
}

void GxMainInterface::closeBox() {
    --fTop;
    assert(fTop >= 0);
}

GtkWidget* GxMainInterface::addWidget(const char* label, GtkWidget* w) {
    switch (fMode[fTop]) {
    case kSingleMode    :
        gtk_container_add(GTK_CONTAINER(fBox[fTop]), w);
        break;
    case kBoxMode         :
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), w, expand, fill, 0);
        break;
    case kTabMode         :
        gtk_notebook_append_page(GTK_NOTEBOOK(fBox[fTop]), w, gtk_label_new(label));
        break;
    }
    gtk_widget_show(w);
    return w;
}


/****************************************************************
 ** class TextLoggingBox
 */

// color depending on msg type
TextLoggingBox::tab_table TextLoggingBox::tagdefs[] = {
    {"colinfo", "#0000ff"},
    {"colwarn", "#ff8800"},
    {"colerr", "#ff0000"},
};

TextLoggingBox::TextLoggingBox(const char* label)
    : box(),
      scrollbox(),
      frame(label),
      tbox(),
      highest_unseen_msg_level(-1) {

    set_size_request(600, -1);
    set_decorated(true);
    set_icon(Glib::wrap(GDK_PIXBUF(gw.ib)));
    set_resizable(true);
    set_gravity(Gdk::GRAVITY_SOUTH);
    set_keep_below(false);
    set_title(_("Logging Window"));
    set_type_hint(Gdk::WINDOW_TYPE_HINT_UTILITY);

    box.set_border_width(0);
    scrollbox.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

    frame.add(box);
    add(frame);
    frame.show();
    frame.set_expanded(true);

    tbox.set_wrap_mode(Gtk::WRAP_WORD_CHAR);
    tbox.set_border_width(0);
    tbox.set_editable(false);
    tbox.set_cursor_visible(false);
    tbox.set_pixels_above_lines(0);
    tbox.set_pixels_below_lines(2);
    tbox.set_justification(Gtk::JUSTIFY_LEFT);
    tbox.set_left_margin(5);
    tbox.set_indent(0);

    Glib::RefPtr<Gtk::TextBuffer> buffer = tbox.get_buffer();
    for (int i = 0; i < gx_system::kMessageTypeCount; i++) {
	tags[i] = buffer->create_tag(tagdefs[i].tagname);
	tags[i]->property_foreground() = tagdefs[i].tag_color;
    }

    box.add(scrollbox);
    scrollbox.add(tbox);
    tbox.show();
    scrollbox.show();
    tbox.set_size_request(-1, 100);
    frame.property_expanded().signal_changed().connect(
	sigc::mem_fun(*this, &TextLoggingBox::set_color));
    box.show();
    gx_system::Logger::get_logger().signal_message().connect(
	sigc::mem_fun(*this, &TextLoggingBox::show_msg));
}

TextLoggingBox::~TextLoggingBox() {
}

/* loging box handling*/
void TextLoggingBox::set_color() {
    if (!frame.get_expanded()) {
        // expander will be opened
        highest_unseen_msg_level = gx_system::kMessageTypeCount;
        set_expander_color("#ffffff");
    } else {
        highest_unseen_msg_level = -1;
    }
}

void TextLoggingBox::set_expander_color(const char *color) {
    if (!frame.get_expanded()) {
	Gdk::Color c(color);
        frame.modify_fg(Gtk::STATE_NORMAL, c);
        frame.get_label_widget()->modify_fg(Gtk::STATE_NORMAL, c);
    }
}

void TextLoggingBox::show_msg(string msgbuf, gx_system::GxMsgType msgtype) {
    assert(0 <= msgtype && msgtype < gx_system::kMessageTypeCount);

    // retrieve gtk text buffer
    Glib::RefPtr<Gtk::TextBuffer> buffer = tbox.get_buffer();

    // how many lines to keep
    const int nlines = 50;

    // delete first line when window filled up
    int linecount = buffer->get_line_count(); // empty buffer == 1 line
    if (linecount >= nlines) {
	Gtk::TextIter iter1 = buffer->get_iter_at_line(0);
	Gtk::TextIter iter2 = buffer->get_iter_at_line(1);
        buffer->erase(iter1, iter2);
    }

    Gtk::TextIter iter = buffer->end();
    if (buffer->get_char_count() > 0) {
        iter = buffer->insert(iter, "\n");
    }

    buffer->insert_with_tag(iter, msgbuf, tags[msgtype]);
    scrollbox.get_vadjustment()->set_value(10000);
    // scroll to end (big value, gets clamped to max)

    // modify expander bg color is closed
    if (msgtype > highest_unseen_msg_level) {
        set_expander_color(tagdefs[msgtype].tag_color);
        highest_unseen_msg_level = msgtype;
    }
}

bool GxMainInterface::on_logger_delete_event(GdkEventAny*) {
    fLoggingWindow.hide();
    fShowLogger.set_active(false);
    return true;
}

/* create level meter*/
void GxMainInterface::openLevelMeterBox(const char* label) {
    GtkWidget* box1 = addWidget(label, gtk_alignment_new(0.5, 0.5, 0, 0));
    GtkWidget* box = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(box1), box);

    gint boxheight = 125;
    gint boxwidth  = 47;

    gtk_container_set_border_width(GTK_CONTAINER(box), 3);
    gtk_box_set_spacing(GTK_BOX(box), 1);

    gtk_widget_set_size_request(GTK_WIDGET(box), boxwidth, boxheight);
    g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::level_meter_expose), NULL);
    g_signal_connect(GTK_CONTAINER(box), "check-resize",
                     G_CALLBACK(gx_cairo::level_meter_expose), NULL);

    // width of meter
    int width    = 8;

    // how long we hold the peak bar = hold * thread call timeout
    // Note: 30 * 80 = 2.4 sec
    int hold     = 20;

    // gx_head output levels
    GtkWidget* gxbox = gtk_hbox_new(FALSE, 0);
    gtk_container_set_border_width(GTK_CONTAINER(gxbox), 0);
    // gtk_box_set_spacing(GTK_BOX(gxbox), 6);

    for (int i = 0; i < 2; i++) {
        Gxw::FastMeter& fastmeter = fLevelMeters[i];
        fastmeter.set_hold_count(hold);
        fastmeter.property_dimen() = width;
        fastmeter.set_size_request(width, boxheight);
        fastmeter.signal_button_release_event().connect(
            sigc::mem_fun(*this, &GxMainInterface::on_meter_button_release));
        gtk_box_pack_start(GTK_BOX(gxbox), GTK_WIDGET(fastmeter.gobj()), FALSE, FALSE, 0);
        if (i == 0) {
                gtk_box_pack_start(GTK_BOX(gxbox), (UiRegler::create(*this,
                    new Gxw::LevelSlider(), "amp.out_master" , FALSE)), FALSE, FALSE, 0);
            }
        fastmeter.show();
        fastmeter.set_tooltip_text(_("gx_head output"));
    }

    gtk_box_pack_start(GTK_BOX(box), gxbox, FALSE, TRUE, 0);
    gtk_widget_show(gxbox);

    // show main box
    gtk_widget_show(box);
    gtk_widget_show(box1);
}

// --------------------------- reorder effect chain button ---------------------------
struct uiOrderButton : public gx_ui::GxUiItemInt {
    GtkButton*     fButton;
    uiOrderButton(gx_ui::GxUI* ui, int* zone, GtkButton* b)
                   : gx_ui::GxUiItemInt(ui, zone), fButton(b) {}

    // box move to the right
    static void pressed_right(GtkWidget *widget, gpointer   data) {
	GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
	GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
	GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
	if (!GTK_IS_CONTAINER(parent)) {
	    return;
	}
	GValue  pos = {0};
	g_value_init(&pos, G_TYPE_INT);
	static int move = 0;
	gtk_container_child_get_property(GTK_CONTAINER(parent),
					 GTK_WIDGET(box), "position", &pos);
	GList* child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
	guint max_client = g_list_length(child_list)-1;
	guint per = g_value_get_int(&pos);
	if (per >= max_client-1) {
	    g_list_free(child_list);
	    return;
	}
	GtkWidget *obi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, per+1));
	g_list_free(child_list);
	if (!GTK_IS_CONTAINER(obi)) {
	    return;
	}
	child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
	GtkWidget *obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
	g_list_free(child_list);
	child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
	GtkWidget *obibi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
	g_list_free(child_list);

	gtk_box_reorder_child(GTK_BOX(parent), GTK_WIDGET(box), per +1);
	((gx_ui::GxUiItemInt*)data)->modifyZone(per+1);
	/*child_list =  gtk_container_get_children(GTK_CONTAINER(box));
	  GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
	  string name = gtk_widget_get_name(plug);
	  fprintf(stderr, " %i %s .pressed right\n",per,name.c_str()); */
	if (GTK_IS_BUTTON(obibi)) {
	    gtk_button_clicked(GTK_BUTTON(obibi));
	} else {
	    child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
	    obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
	    // name = gtk_widget_get_name(obib);
	    // fprintf(stderr, " %i %s .next child right\n",per,name.c_str());
	    if (!GDK_IS_WINDOW(obib->window)|| !gtk_widget_is_drawable(obib)) {
		// fprintf(stderr, " %i %s.hidden\n",per,name.c_str());
		move = 1;
	    } else {
		move = 0;
	    }
	    obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 3));
	    g_list_free(child_list);

	    if (GTK_IS_CONTAINER(obib)) {
		child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
		obibi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
		g_list_free(child_list);
		if (GTK_IS_BUTTON(obibi)) {
		    gtk_button_clicked(GTK_BUTTON(obibi));
		    if (move) gtk_button_pressed(GTK_BUTTON(widget));
		}
	    }
	}
	GxMainInterface::get_instance().engine.set_rack_changed();
    }
    // box move to the left
    static void pressed_left(GtkWidget *widget, gpointer data) {
        GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
        GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
        GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
        if (!GTK_IS_CONTAINER(parent)) {
            return;
        }
        GValue  pos = {0};
        g_value_init(&pos, G_TYPE_INT);
        static int move = 0;
        gtk_container_child_get_property(GTK_CONTAINER(parent),
                                         GTK_WIDGET(box), "position", &pos);
        guint per = g_value_get_int(&pos);
        if (per <= 1) {
	    return;
	}
	GList* child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
	GtkWidget *obi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, per-1));
	g_list_free(child_list);
	if (!GTK_IS_CONTAINER(obi)) {
	    return;
	}
	child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
	GtkWidget *obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
	g_list_free(child_list);
	child_list =  gtk_container_get_children(GTK_CONTAINER(obib));
	GtkWidget *obibi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
	g_list_free(child_list);

	gtk_box_reorder_child(GTK_BOX(parent), GTK_WIDGET(box), per -1);
	((gx_ui::GxUiItemInt*)data)->modifyZone(per-1);
	/*child_list =  gtk_container_get_children(GTK_CONTAINER(box));
	  GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
	  string name = gtk_widget_get_name(plug);
	  fprintf(stderr, " %i %s .pressed left\n",per,name.c_str()); */
	if (GTK_IS_BUTTON(obibi)) {
	    gtk_button_clicked(GTK_BUTTON(obibi));
	} else {
	    child_list =  gtk_container_get_children(GTK_CONTAINER(obi));
	    obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
	    // name = gtk_widget_get_name(obib);
	    // fprintf(stderr, " %i %s .next child left\n",per,name.c_str());
	    if (!GDK_IS_WINDOW(obib->window)|| !gtk_widget_is_drawable(obib)) {
		// fprintf(stderr, " %i %s.hidden\n",per,name.c_str());
		move =1;
	    } else {
		move= 0;
	    }
	    obib = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 3));
	    g_list_free(child_list);
		
	    if (GTK_IS_CONTAINER(obib)) {
		child_list = gtk_container_get_children(GTK_CONTAINER(obib));
		obibi = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
		g_list_free(child_list);
		if (GTK_IS_BUTTON(obibi)) {
		    gtk_button_clicked(GTK_BUTTON(obibi));
		    if (move) {
			gtk_button_pressed(GTK_BUTTON(widget));
		    }
		}
	    }
	}
	GxMainInterface::get_instance().engine.set_rack_changed();
    }
    // resize the effect box
    static void resize(GtkWidget *widget, gpointer data) {
            GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
            GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
            GtkWidget *parent = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 1));
            child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
            box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
            child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
            box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
            child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
            box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
            child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
            box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
            child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
            box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
            g_list_free(child_list);

            int width, height;
            gtk_widget_get_size_request(parent, &width, &height);
            if (width != -1) {
                gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                               GTK_POLICY_NEVER, GTK_POLICY_NEVER);
                gtk_widget_set_size_request(parent, -1, -1);
            } else {
                width = box1->allocation.width;
                gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(parent),
                                               GTK_POLICY_AUTOMATIC, GTK_POLICY_NEVER);
                gtk_widget_set_size_request(parent, width*5, -1);
            }
        }

    // save order for neigbor box
    static void clicked(GtkWidget *widget, gpointer   data) {
	GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(widget));
	GtkWidget * box = gtk_widget_get_parent(GTK_WIDGET(box1));
	GtkWidget * parent = gtk_widget_get_parent(GTK_WIDGET(box));
	if (GTK_IS_CONTAINER(parent)) {
	    GValue  pos = {0};
	    g_value_init(&pos, G_TYPE_INT);

	    gtk_container_child_get_property(GTK_CONTAINER(parent),
					     GTK_WIDGET(box), "position", &pos);
	    guint per = g_value_get_int(&pos);
	    gtk_box_reorder_child(GTK_BOX(parent), GTK_WIDGET(box), per);
	    if (GDK_IS_WINDOW (box->window))
		gdk_window_invalidate_rect(box->window, NULL, true);

	    ((gx_ui::GxUiItemInt*)data)->modifyZone(per);
	    /*GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(box));
	      GtkWidget *plug = (GtkWidget *) g_list_nth_data(child_list,1);
	      const gchar *name = gtk_widget_get_name(plug);
	      fprintf(stderr, " %i %s .clicked\n",per,name); 
                
	      g_list_free(child_list);*/
	}
    }
    // set the init order
    virtual void reflectZone() {

            int v = *fZone;
            fCache = v;
            GValue  pos = {0};

            g_value_init(&pos, G_TYPE_INT);
            g_value_set_int(&pos, v);
            GtkWidget *box1 = gtk_widget_get_parent(GTK_WIDGET(fButton));
            GtkWidget *box = gtk_widget_get_parent(GTK_WIDGET(box1));
            GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(box));
            if (GTK_IS_CONTAINER(parent)) {
                gtk_container_child_set_property(GTK_CONTAINER(parent),
                                                 GTK_WIDGET(box), "position", &pos);
                guint per = g_value_get_int(&pos);
                gtk_box_reorder_child(GTK_BOX(parent), GTK_WIDGET(box), per);
            }
        }
};


// ----- boxes to move inside a other box (mono effects)
GtkWidget *GxMainInterface::openHorizontalOrderBox(const char* label, int* posit) {
    GxMoveBox * box =  new GxMoveBox(*this);
    uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(box->m_button.gobj()));

    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_right), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_left), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    gtk_box_pack_start(GTK_BOX(rBox), GTK_WIDGET(box->m_paintbox.gobj()), expand, false, 0);
    GValue  pos = {0};
    g_value_init(&pos, G_TYPE_INT);
    g_value_set_int(&pos, *posit);
    string tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" up");
    box->m_button1.set_tooltip_text(tooltip);
    box->m_button1.get_accessible()->set_description(tooltip);
    box->m_button1.get_accessible()->set_name(label);
    tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" down");
    box->m_button.set_tooltip_text(tooltip);
    box->m_button.get_accessible()->set_description(tooltip);
    box->m_button.get_accessible()->set_name(label);
    gtk_container_child_set_property(GTK_CONTAINER(rBox),
                                     GTK_WIDGET(box->m_paintbox.gobj()), "position", &pos);
    GtkWidget* mainbox = GTK_WIDGET(box->m_paintbox.gobj());
    pushBox(kBoxMode, mainbox);
    return mainbox;
}

// ----- boxes to move inside a other box (stereo effects)
GtkWidget* GxMainInterface::openHorizontalRestetBox(const char* label, int* posit) {
    GxMoveBox * box =  new GxMoveBox(*this);
    uiOrderButton* c = new uiOrderButton(this, posit, GTK_BUTTON(box->m_button.gobj()));

    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_right), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "pressed",
                      G_CALLBACK(uiOrderButton::pressed_left), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    g_signal_connect(GTK_OBJECT(box->m_button1.gobj()), "clicked",
                      G_CALLBACK(uiOrderButton::clicked), (gpointer) c);
    gtk_box_pack_start(GTK_BOX(sBox), GTK_WIDGET(box->m_paintbox.gobj()), expand, false, 0);
    GValue  pos = {0};
    g_value_init(&pos, G_TYPE_INT);
    g_value_set_int(&pos, *posit);
    string tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" up");
    box->m_button1.set_tooltip_text(tooltip);
    box->m_button1.get_accessible()->set_description(tooltip);
    box->m_button1.get_accessible()->set_name(label);
    tooltip = _("Move ");
    tooltip += label;
    tooltip += _(" down");
    box->m_button.set_tooltip_text(tooltip);
    box->m_button.get_accessible()->set_description(tooltip);
    box->m_button.get_accessible()->set_name(label);
    gtk_container_child_set_property(GTK_CONTAINER(sBox),
                                     GTK_WIDGET(box->m_paintbox.gobj()), "position", &pos);
    GtkWidget* mainbox = GTK_WIDGET(box->m_paintbox.gobj());
    pushBox(kBoxMode, mainbox);
    return mainbox;
}

// -------- different gtk(x)mm container (virtuell discription)
void GxMainInterface::openEventBox(const char* label) {
    GxEventBox * box =  new GxEventBox(*this);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_hbox.gobj()), false, fill, 0);
    box->m_box.set_size_request(600, 182); // main window size
    box->m_box.set_border_width(2);
    box->m_eventbox.set_name("main_window");
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_hbox.show_all();
}

void GxMainInterface::openMainBox(const char* label, const char* expose_funk) {
    GxMainBox * box =  new GxMainBox(*this, expose_funk);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_hbox.gobj()), false, fill, 0);
    box->m_box.set_border_width(2);
    // box->m_eventbox.set_name("main_window");
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_hbox.show_all();
}

void GxMainInterface::openFrameBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(2);
    box->m_box.set_border_width(2);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openHorizontalBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openHorizontalTableBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_frame.set_label(label);
        box->m_frame.set_shadow_type(Gtk::SHADOW_NONE);
        box->m_frame.add(box->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_frame.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_frame.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openVerticalBox(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_label.set_text(label);
        box->m_label.set_name("rack_effect_label");
        GtkStyle *style = gtk_widget_get_style(GTK_WIDGET(box->m_label.gobj()));
        pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
        pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
        gtk_widget_modify_font(GTK_WIDGET(box->m_label.gobj()), style->font_desc);
        box->m_box.pack_start(box->m_label, false, false, 0 );
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
        box->m_box.show();
        box->m_label.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openSetLabelBox(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    box->m_label.set_text(label);
    box->m_label.set_name("beffect_label");
    gw.set_label = GTK_WIDGET(box->m_label.gobj());
    GtkStyle *style = gtk_widget_get_style(GTK_WIDGET(box->m_label.gobj()));
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(GTK_WIDGET(box->m_label.gobj()), style->font_desc);
    box->m_box.pack_start(box->m_label, false, false, 0 );
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
    box->m_box.show();
    box->m_label.show();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void GxMainInterface::openFlipLabelBox(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        GxVBox * vbox =  new GxVBox(*this);
        vbox->m_box.set_homogeneous(false);
        vbox->m_box.set_spacing(0);
        vbox->m_box.set_border_width(0);

        GxHBox * hbox =  new GxHBox(*this);
        hbox->m_box.set_homogeneous(false);
        hbox->m_box.set_spacing(0);
        hbox->m_box.set_border_width(0);

        hbox->m_label.set_text(label);
        hbox->m_label.set_name("effekt_label");
        hbox->m_label.set_angle(90);
        hbox->m_label.set_size_request(15, -1);

        Pango::FontDescription font = hbox->m_label.get_style()->get_font();
        font.set_size(8*Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        hbox->m_label.modify_font(font);

        hbox->m_box.add(hbox->m_label);
        hbox->m_box.add(vbox->m_box);
        box->m_box.add(hbox->m_box);
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), false, fill, 0);
        box->m_box.show_all();

        pushBox(kBoxMode, GTK_WIDGET(vbox->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openSpaceBox(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(true);
    box->m_box.set_spacing(2);
    box->m_box.set_border_width(4);
    box->m_box.show_all();
    if (fMode[fTop] != kTabMode && label[0] != 0) {
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openPaintBox(const char* label, const char* name) {
    GxPaintBox * box =  new GxPaintBox(*this, pb_rectangle_skin_color_expose);
    box->m_box.set_border_width(4);
    if (name) {
        box->m_paintbox.set_name(name);
    }
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_paintbox.gobj()), false, fill, 0);
    box->m_paintbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void GxMainInterface::openpaintampBox(const char* label) {
    GxPaintBox * box =  new GxPaintBox(*this, pb_RackBox_expose);
    box->m_box.set_border_width(4);
    box->m_paintbox.set_name(label);
    box->m_paintbox.set_tooltip_text(label);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_paintbox.gobj()), expand, fill, 0);
    box->m_paintbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void GxMainInterface::openPaintBox1(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    box->m_box.show_all();
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void GxMainInterface::openPaintBox2(const char* label) {
    GxEventBox * box =  new GxEventBox(*this);
    box->m_eventbox.set_name(label);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_hbox.gobj()), false, false, 0);
    box->m_hbox.show_all();
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
}

void GxMainInterface::openVerticalBox1(const char* label) {
    GxVBox * box =  new GxVBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);

    if (fMode[fTop] != kTabMode && label[0] != 0) {
        box->m_label.set_text(label);
        box->m_label.set_name("effekt_label");
        box->m_box.pack_start(box->m_label, false, false, 0 );
        gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()), expand, fill, 0);
        box->m_box.show();
        box->m_label.show();
        pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    } else {
        pushBox(kBoxMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
    }
}

void GxMainInterface::openTabBox(const char* label) {
    GxNotebookBox * box =  new GxNotebookBox(*this);
    pushBox(kTabMode, addWidget(label, GTK_WIDGET(box->m_box.gobj())));
}

void GxMainInterface::openVerticalMidiBox(const char* label) {
    GxMidiBox * box =  new GxMidiBox(*this, pb_eq_expose);
    gw.midibox = GTK_WIDGET(box->m_eventbox.gobj());
    // gtk_container_add (GTK_CONTAINER(rBox), gw.midibox);
    gtk_box_pack_end(GTK_BOX(rBox), GTK_WIDGET(gw.midibox) , false, false, 0);
    gtk_widget_show(gw.midibox);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    gtk_widget_hide(gw.midibox);

    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(gw.rack_tool_bar));
    GtkWidget *box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);
    box->m_tcb.set_parameter(fShowMidiOut.get_parameter());
    box->m_tcb.m_label.set_text(_("MIDI out"));
    gtk_container_add(GTK_CONTAINER(box1), GTK_WIDGET(box->m_bbox.gobj()));
}

void GxMainInterface::openHorizontalhideBox(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->m_box.gobj()) , false, false, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_box.hide();
    if (label[0] != 0) box->m_box.show();
}

void GxMainInterface::openHorizontalhideBox1(const char* label) {
    GxHBox * box =  new GxHBox(*this);
    box->m_box.set_homogeneous(false);
    box->m_box.set_spacing(0);
    box->m_box.set_border_width(0);
    gtk_box_pack_end(GTK_BOX(sBox), GTK_WIDGET(box->m_box.gobj()) , false, false, 0);
    pushBox(kBoxMode, GTK_WIDGET(box->m_box.gobj()));
    box->m_box.hide();
    if (label[0] != 0) box->m_box.show();
}

/* add mono effect to the mono rack, increase mono effect counter*/
void GxMainInterface::openDialogBox(const char *id_dialog, const char *id_switch,
                                    const char *expose_funk, GtkWidget* box) {
    Parameter& param_dialog = parameter_map[id_dialog];
    Parameter& param_switch = parameter_map[id_switch];
    GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);
    guivar.mono_plugs++;
    gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(bbox->box.gobj()), false, false, 0);
    GxDialogWindowBox *dialog = new GxDialogWindowBox(*this, expose_funk, param_dialog,
                                param_switch, bbox->show_dialog, gw.rack_widget);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(dialog->paintbox.gobj()) , true, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(dialog->box.gobj()));

    const gchar * title = gtk_widget_get_name(GTK_WIDGET(dialog->paintbox.gobj()));
    string p = "ui.";
    p +=title;
    dialog->menuitem.set_label(title);
    guint accel_key = GDK_a + guivar.mono_plugs;
    dialog->menuitem.add_accelerator(
	"activate", fAccelGroup, accel_key,
	Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);  // FIXME MOD1_MASK
    gtk_menu_shell_append(GTK_MENU_SHELL(fMenuList["PluginsMono"]),
                          GTK_WIDGET(dialog->menuitem.gobj()));
    dialog->menuitem.show();
    //dialog->menuitem.set_parameter(new SwitchParameter(p, true, false));

    //dialog->m_tcb.set_parameter(&param_dialog);
    gtk_box_pack_start(GTK_BOX(tBox), GTK_WIDGET(dialog->box1.gobj()) , false, false, 0);
    dialog->box1.pack_start(dialog->m_tcb, true, true);
    string tooltip = "Show ";
    tooltip +=title;
    dialog->m_tcb.set_tooltip_text(tooltip.c_str());
    dialog->box1.show_all();
}

/* add stereo effect to the stereo rack, increase stereo effect counter*/
void GxMainInterface::opensDialogBox(const char *id_dialog, const char *id_switch,
                                     const char *expose_funk, GtkWidget* box) {
    Parameter& param_dialog = parameter_map[id_dialog];
    Parameter& param_switch = parameter_map[id_switch];
    GxDialogButtonBox *bbox = new GxDialogButtonBox(*this, param_dialog);

    guivar.stereo_plugs++;
    gtk_box_pack_end(GTK_BOX(box), GTK_WIDGET(bbox->box.gobj()), false, false, 0);
    GxDialogWindowBox *bdialog = new GxDialogWindowBox(*this, expose_funk, param_dialog,
                                 param_switch, bbox->show_dialog, gw.srack_widget);
    gtk_box_pack_start(GTK_BOX(box), GTK_WIDGET(bdialog->paintbox.gobj()) , true, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(bdialog->box.gobj()));

    const gchar * title = gtk_widget_get_name(GTK_WIDGET(bdialog->paintbox.gobj()));
    bdialog->menuitem.set_label(title);
    string p = "ui.";
    p +=title;
    string s;

    guint accel_key = GDK_r  + guivar.stereo_plugs;
    bdialog->menuitem.add_accelerator(
	"activate", fAccelGroup, accel_key,
	Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(fMenuList["PluginsStereo"]),
                          GTK_WIDGET(bdialog->menuitem.gobj()));
    bdialog->menuitem.show();
    //bdialog->menuitem.set_parameter(new SwitchParameter(p, true, false));

    //bdialog->m_tcb.set_parameter(&param_dialog);
    gtk_box_pack_start(GTK_BOX(tBox), GTK_WIDGET(bdialog->box1.gobj()) , false, false, 0);
    bdialog->box1.pack_start(bdialog->m_tcb, true, true);
    string tooltip = "Show ";
    tooltip +=title;
    bdialog->m_tcb.set_tooltip_text(tooltip.c_str());
    bdialog->box1.show_all();
    // gtk_box_pack_start (GTK_BOX(tBox),GTK_WIDGET(bdialog->m_tcb.gobj()) , false, false, 0);
}

/* button box for the (show)effect buttons*/
void GxMainInterface::openToolBar(const char* label) {
    GxToolBox *box =  new GxToolBox(*this,
        pb_gxrack_expose, _("Plugin Bar"), GTK_WIDGET(fShowToolBar.gobj()));

    // box->window.set_size_request(-1,524);
    gw.rack_tool_bar = GTK_WIDGET(box->window.gobj());
    tBox = GTK_WIDGET(box->rbox.gobj());
    box->rbox.add(box->box1);
    box->m_tmono_rack.set_parameter(fShowRack.get_parameter());
    box->m_tstereo_rack.set_parameter(fShowSRack.get_parameter());
    box->m_tmono_rack.m_label.set_text(_("mono rack"));
    box->m_tstereo_rack.m_label.set_text(_("stereo rack"));

    box->box1.pack_start(box->m_tmono_rack, true, true);
    box->box1.pack_end(box->m_tstereo_rack, true, true);
    box->m_tmono_rack.set_tooltip_text(_("Show mono rack"));
    box->m_tstereo_rack.set_tooltip_text(_("Show stereo rack"));
    box->box1.show_all();
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->window.gobj()), expand, fill, 0);
    pushBox(kBoxMode, GTK_WIDGET(tBox));
}

/* the mono rack*/
void GxMainInterface::openPlugBox(const char* label) {
    GxWindowBox *plugbox =  new GxWindowBox(*this,
        label, GTK_WIDGET(fShowRack.gobj()));
    gw.rack_widget = GTK_WIDGET(plugbox->window.gobj());
    plugbox->box.pack_start(plugbox->rbox, true, true, 0);
    plugbox->window.set_name("MonoRack");
    plugbox->window.set_tooltip_text(_("Mono Rack, right click pop up the plugin menu"));
    rBox = GTK_WIDGET(plugbox->rbox.gobj());
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(plugbox->window.gobj()), false, true, 0);
    pushBox(kBoxMode, GTK_WIDGET(rBox));
}

/* the main rack widget for all racks*/
void GxMainInterface::openScrollBox(const char* label) {
    GxScrollBox *scrollbox =  new GxScrollBox(*this,
        pb_gxrack_expose, label, GTK_WIDGET(fShowRack.gobj()));
    scrollbox->box.pack_start(scrollbox->rbox, true, true, 0);
    // scrollbox->box.pack_start(scrollbox->vbox, false, false, 0);
    scrollbox->vbox.pack_start(scrollbox->box1, false, false, 0);

    RBox = GTK_WIDGET(scrollbox->window.gobj());
    scrollbox->window.set_name("Rack");
    scrollbox->window.set_size_request(-1, 460);
    scrollbox->rbox.show();
    scrollbox->box1.show();
    scrollbox->vbox.show();
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(scrollbox->window.gobj()), expand, true, 0);
    pushBox(kBoxMode, GTK_WIDGET(scrollbox->rbox.gobj()));
}

/* the stereo rack*/
void GxMainInterface::openAmpBox(const char* label) {
    GxWindowBox *box =  new GxWindowBox(*this,
        label, GTK_WIDGET(fShowSRack.gobj()));
    box->box.pack_start(box->rbox, true, true, 0);
    gw.srack_widget = GTK_WIDGET(box->window.gobj());
    box->window.set_name("StereoRack");
    box->window.set_tooltip_text(_("Stereo Rack, right click pop up the plugin menu"));
    sBox = GTK_WIDGET(box->rbox.gobj());
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->window.gobj()), false, true, 0);
    pushBox(kBoxMode, GTK_WIDGET(sBox));
}

void GxMainInterface::openStereoRackBox(const char* label, int* posit, const char *id_on_off,
				      const char *id_dialog) {
    fBox[++fTop] = fStereoRackContainer;
    fMode[fTop] = kBoxMode;
    GtkWidget* box = openHorizontalRestetBox(label, posit);
    openVerticalBox(label);
    openHorizontalTableBox("");
    openPaintBox1("");
    openHorizontalBox("");
    openSpaceBox("");
    closeBox();
    openFrameBox("");
    closeBox();
    create_switch_no_caption(sw_switchit, id_on_off);
    openSpaceBox("");
    closeBox();
    openFrameBox("");
    closeBox();
    closeBox();
    closeBox();
    opensDialogBox(id_dialog, id_on_off, "RackBox_expose", box);
}

void GxMainInterface::closeStereoRackBox() {
    closeBox();
    closeBox();
    closeBox();
    closeBox();
    --fTop;
}

void GxMainInterface::openMonoRackBox(const char* label, int* posit, const char *id_on_off,
				      const char *id_pre_post, const char *id_dialog) {
    fBox[++fTop] = fMonoRackContainer;
    fMode[fTop] = kBoxMode;
    GtkWidget* box = openHorizontalOrderBox(label, posit);
    openVerticalBox(label);
    openHorizontalBox("");
    openPaintBox1("");
    create_switch_no_caption(sw_switchit, id_on_off);
    create_selector(id_pre_post);
    closeBox();
    openDialogBox(id_dialog, id_on_off, "RackBox_expose", box);
}

void GxMainInterface::closeMonoRackBox() {
    closeBox();
    closeBox();
    closeBox();
    closeBox();
    --fTop;
}

void GxMainInterface::loadRackFromGladeData(const char *xmldesc) {
    Glib::RefPtr<Gtk::Builder> bld = load_builder_from_data(xmldesc, *this);
    Gtk::Widget* w = 0;
    bld->get_widget("rackbox", w);
    if (!w) {
        gx_system::gx_print_error("load_ui Error", "can't find widget 'rackbox'");
	return;
    }
    Gtk::Container *c = w->get_parent();
    c->remove(*w);
    delete c;
    addWidget("", w->gobj());
}

// --------------------------- Press button ---------------------------

/*
void GxMainInterface::addPToggleButton(const char* label) {
    GtkWidget*     button = gtk_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");

    addWidget(label, GTK_WIDGET(button));
    gtk_widget_show(lab);
    uipButton* c = new uipButton(this, zone, GTK_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(uipButton::pressed),
                     (gpointer) c);
    //
            guint32 tim = gtk_get_current_event_time();
            gtk_menu_popup(GTK_MENU(gx_preset::gxpreset.presmenu[0]), NULL, NULL, NULL,
                          (gpointer) gx_preset::gxpreset.presmenu[0] , 2, tim);
        }

    //
}
*/

struct uiButton : public gx_ui::GxUiItemFloat {
    GtkButton*     fButton;
    uiButton(gx_ui::GxUI* ui, float* zone, GtkButton* b) : gx_ui::GxUiItemFloat(ui, zone),
             fButton(b) {}
    static void pressed(GtkWidget *widget, gpointer   data) {
            gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*)data;
            c->modifyZone(1.0);
        }

    static void released(GtkWidget *widget, gpointer   data) {
            gx_ui::GxUiItemFloat* c = (gx_ui::GxUiItemFloat*) data;
            c->modifyZone(0.0);
        }

    virtual void reflectZone() {
            float     v = *fZone;
            fCache = v;
            if (v > 0.0) {
                gtk_button_pressed(fButton);
            } else {
                gtk_button_released(fButton);
            }
        }
};

void GxMainInterface::addJConvButton(const char* label, float* zone) {
    *zone = 0.0;
    GtkWidget*     button = gtk_button_new();

    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");
    addWidget(label, button);
    gtk_widget_show(lab);

    uiButton* c = new uiButton(this, zone, GTK_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "clicked",
                      G_CALLBACK(gx_jconv::gx_show_jconv_dialog_gui),
                      (gpointer) c);
}

void GxMainInterface::addJConvFavButton(const char* label) {
    
    GtkWidget*     button = gtk_button_new();

    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");
    addWidget(label, button);
    gtk_widget_show(lab);

    
    g_signal_connect(GTK_OBJECT(button), "clicked",
                      G_CALLBACK(gx_jconv::gx_show_fav),
                      (gpointer) NULL);
}
// ---------------------------    Toggle Buttons ---------------------------

struct uiToggleButton : public gx_ui::GxUiItemBool {
    GtkToggleButton* fButton;
    uiToggleButton(gx_ui::GxUI* ui, bool* zone, GtkToggleButton* b)
                   : gx_ui::GxUiItemBool(ui, zone), fButton(b) {}
    static void toggled(GtkWidget *widget, gpointer data) {
            ((gx_ui::GxUiItemBool*)data)->modifyZone(GTK_TOGGLE_BUTTON(widget)->active);
        }

    virtual void reflectZone() {
            bool v = *fZone;
            fCache = v;
            gtk_toggle_button_set_active(fButton, v);
        }
};

#if 0 // unused
void GxMainInterface::addToggleButton(const char* label, float* zone) {
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse("#d56161", &colorRed);
    gdk_color_parse("#7f7f7f", &colorOwn);
    GtkWidget*     button = gtk_toggle_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);

    gtk_widget_set_name(lab, "beffekt_label");
    addWidget(label, button);

    gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg(button, GTK_STATE_ACTIVE, &colorRed);

    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(gx_child_process::JackCapture::start_stop), NULL);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), FALSE);
    gtk_widget_add_accelerator(button, "activate", fAccelGroup->gobj(), GDK_r,
                               GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_show(lab);
}
#endif

void GxMainInterface::addMToggleButton(const char* label, bool* zone) {
    GdkColor colorRed;
    GdkColor colorOwn;
    GdkColor colorwn;
    gdk_color_parse("#58b45e", &colorRed);
    gdk_color_parse("#000000", &colorwn);
    gdk_color_parse("#7f7f7f", &colorOwn);
    *zone = 0;
    GtkWidget*     button = gtk_toggle_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);
    gtk_widget_set_size_request(GTK_WIDGET(button), 70, 20);
    GtkWidget * box = gtk_hbox_new(homogene, 4);
    GtkWidget * box1 = gtk_vbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box), 0);
    gtk_container_set_border_width(GTK_CONTAINER(box1), 0);
    gtk_container_add(GTK_CONTAINER(box), box1);
    GtkWidget * box2 = gtk_vbox_new(homogene, 4);
    gtk_container_set_border_width(GTK_CONTAINER(box2), 0);
    gtk_widget_set_size_request(GTK_WIDGET(box2), 6, 20);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_container_add(GTK_CONTAINER(box), box2);
    gtk_widget_set_size_request(GTK_WIDGET(box1), 6, 20);
    gtk_widget_show(button);
    gtk_widget_show(box1);
    gtk_widget_show(box2);
    gtk_widget_show(lab);
    gtk_widget_show(box);
    gtk_container_add(GTK_CONTAINER(fBox[fTop]), box);
    uiToggleButton* c = new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));
    gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg(button, GTK_STATE_ACTIVE, &colorRed);
    gtk_widget_set_name(lab, "rack_label");
    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(uiToggleButton::toggled), (gpointer) c);
    connect_midi_controller(button, zone);
}

void gx_start_stop_jconv(GtkWidget *widget, gpointer data) {
    GxMainInterface::get_instance().engine.set_rack_changed();
}

void GxMainInterface::addJToggleButton(const char* label, bool* zone) {
    GdkColor colorRed;
    GdkColor colorOwn;
    gdk_color_parse("#58b45e", &colorRed);
    gdk_color_parse("#7f7f7f", &colorOwn);

    *zone = 0;

    GtkWidget*     button = gtk_toggle_button_new();
    GtkWidget*     lab = gtk_label_new(label);
    gtk_widget_set_name(lab, "beffekt_label");
    GtkStyle *style = gtk_widget_get_style(lab);

    pango_font_description_set_size(style->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);
    gtk_container_add(GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_show(lab);

    uiToggleButton* c =
        new uiToggleButton(this, zone, GTK_TOGGLE_BUTTON(button));

    gtk_widget_modify_bg(button, GTK_STATE_NORMAL, &colorOwn);
    gtk_widget_modify_bg(button, GTK_STATE_ACTIVE, &colorRed);

    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(uiToggleButton::toggled), (gpointer) c);

    g_signal_connect(GTK_OBJECT(button), "toggled",
                     G_CALLBACK(gx_start_stop_jconv), (gpointer)c);
    connect_midi_controller(button, zone);
}

// ---------------------------    Check Button ---------------------------

MenuCheckItemUiBool::MenuCheckItemUiBool(gx_ui::GxUI* ui, bool* zone)
    : Gtk::CheckMenuItem("", true),
      gx_ui::GxUiItemBool(ui, zone) {
    signal_toggled().connect(
        sigc::mem_fun(*this, &MenuCheckItemUiBool::on_my_activate));
}

void MenuCheckItemUiBool::reflectZone() {
    bool v = *fZone;
    fCache = v;
    set_active(v);
}

void MenuCheckItemUiBool::on_my_activate() {
    modifyZone(get_active());
}

struct uiCheckButton : public gx_ui::GxUiItemFloat {
    GtkToggleButton* fButton;
    uiCheckButton(gx_ui::GxUI* ui, float* zone, GtkToggleButton* b)
                 : gx_ui::GxUiItemFloat(ui, zone), fButton(b) {}
    static void toggled(GtkWidget *widget, gpointer data) {
            float    v = (GTK_TOGGLE_BUTTON(widget)->active) ? 1.0 : 0.0;
            ((gx_ui::GxUiItemFloat*)data)->modifyZone(v);
        }

    virtual void reflectZone() {
            float     v = *fZone;
            fCache = v;
            gtk_toggle_button_set_active(fButton, v > 0.0);
        }
};

void GxMainInterface::addCheckButton(const char* label, float* zone) {
    GdkColor   colorRed;
    GdkColor   colorOwn;
    GdkColor   colorba;
    gdk_color_parse("#000000", &colorRed);
    gdk_color_parse("#4c5159", &colorOwn);
    gdk_color_parse("#c4c0c0", &colorba);
    GtkWidget*     lab = gtk_label_new(label);
    GtkWidget*     button = gtk_check_button_new();
    gtk_container_add(GTK_CONTAINER(button), lab);
    addWidget(label, button);
    gtk_widget_modify_bg(button, GTK_STATE_PRELIGHT, &colorOwn);
    gtk_widget_modify_fg(button, GTK_STATE_PRELIGHT, &colorRed);
    gtk_widget_modify_text(button, GTK_STATE_NORMAL, &colorRed);
    gtk_widget_modify_base(button, GTK_STATE_NORMAL, &colorba);
    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(lab, style->font_desc);
    uiCheckButton* c = new uiCheckButton(this, zone, GTK_TOGGLE_BUTTON(button));
    g_signal_connect(GTK_OBJECT(button), "toggled",
                      G_CALLBACK(uiCheckButton::toggled), (gpointer) c);
    connect_midi_controller(button, zone);
    gtk_widget_show(lab);
}

// ---------------------------    Adjustmenty based widgets ---------------------------

struct uiValueDisplay : public gx_ui::GxUiItemFloat {
    GtkLabel* fLabel;
    int    fPrecision;

    uiValueDisplay(gx_ui::GxUI* ui, float* zone, GtkLabel* label, int precision)
        : gx_ui::GxUiItemFloat(ui, zone), fLabel(label), fPrecision(precision) {}

    virtual void reflectZone() {
            float v = *fZone;
            fCache = v;
            char s[64];
            if (fPrecision <= 0) {
                snprintf(s, sizeof(s), "%d", static_cast<int>(v));
            } else if (fPrecision > 3) {
                snprintf(s, sizeof(s), "%f", v);
            } else if (fPrecision == 1) {
                const char* format[] = {"%.1f", "%.2f", "%.3f"};
                snprintf(s, sizeof(s), format[1-1], v);
            } else if (fPrecision == 2) {
                const char* format[] = {"%.1f", "%.2f", "%.3f"};
                snprintf(s, sizeof(s), format[2-1], v);
            } else {
                const char* format[] = {"%.1f", "%.2f", "%.3f"};
                snprintf(s, sizeof(s), format[3-1], v);
            }
            gtk_label_set_text(fLabel, s);
        }
};

void GxMainInterface::addCheckButton(string id, const char* label) {
    if (!parameter_map.hasId(id)) {
        return;
    }
    const FloatParameter &p = parameter_map[id].getFloat();
    if (!label) {
        label = p.name().c_str();
    }
    addCheckButton(label, &p.value);
}

void GxMainInterface::addNumEntry(string id, const char* label) {
    if (!parameter_map.hasId(id)) {
        return;
    }
    const FloatParameter &p = parameter_map[id].getFloat();
    if (!label) {
        label = p.name().c_str();
    }
    addNumEntry(label, &p.value, p.std_value, p.lower, p.upper, p.step);
}

void GxMainInterface::addMToggleButton(string id, const char* label) {
    if (!parameter_map.hasId(id)) {
        return;
    }
    const BoolParameter &p = parameter_map[id].getBool();
    if (!label) {
        label = p.name().c_str();
    }
    addMToggleButton(label, &p.value);
}

// -------------------------- gtk widgets -----------------------------------

void GxMainInterface::addNumEntry(const char* label, float* zone, float init, float min,
                                  float max, float step) {
    *zone = init;
    GtkObject* adj = gtk_adjustment_new(init, min, max, step, 10*step, 0);
    uiAdjustment* c = new uiAdjustment(this, zone, GTK_ADJUSTMENT(adj));
    g_signal_connect(GTK_OBJECT(adj), "value-changed",
                      G_CALLBACK(uiAdjustment::changed), (gpointer) c);
    GtkWidget* spinner = gtk_spin_button_new(GTK_ADJUSTMENT(adj), step, precision(step));
    connect_midi_controller(spinner, zone);
    GtkWidget * box = gtk_hbox_new(homogene, 0);
    GtkWidget*     lab = gtk_label_new(label);
    gtk_container_add(GTK_CONTAINER(box), lab);
    gtk_widget_set_name(lab, "rack_label");
    addWidget(label, box);
    addWidget(label, spinner);
}

// -------- collect patch info for stage display
struct uiPatchDisplay : public gx_ui::GxUiItemFloat {
    GtkWidget* fdialog;

    static void delete_self(GtkWindow*, uiPatchDisplay *self) {
	delete self;
    }

    uiPatchDisplay(gx_ui::GxUI* ui, float* zone, GtkWidget* dialog)
        : gx_ui::GxUiItemFloat(ui, zone), fdialog(dialog) {
	g_signal_connect(GTK_OBJECT(dialog), "destroy",
			 G_CALLBACK(delete_self), this);
    }

    virtual void reflectZone() {
            GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(fdialog));
            GtkWidget *parent = reinterpret_cast<GtkWidget *>( g_list_nth_data(child_list, 0));
            if (GDK_WINDOW(parent->window)) {
                if (fCache != *fZone) {
                    char s[64];
                    gdk_window_invalidate_rect(GDK_WINDOW(parent->window), NULL, false);
                    child_list =  gtk_container_get_children(GTK_CONTAINER(parent));
                    parent = reinterpret_cast<GtkWidget *>( g_list_nth_data(child_list, 1));
                    GtkWidget *pchild = reinterpret_cast<GtkWidget *>
                                      ( g_list_nth_data(child_list, 2));
		    gx_engine::GxJConvSettings& jcset = GxMainInterface::get_instance().engine.convolver.jcset;

                    if (*gx_engine::GxJConvSettings::checkbutton7 == 1) {
                        snprintf(s, sizeof(s), _("convolve %s"), jcset.getIRFile().c_str());
                        gtk_label_set_text(GTK_LABEL(pchild), s);
                    } else {
                        snprintf(s, sizeof(s), _("convolver off"));
                        gtk_label_set_text(GTK_LABEL(pchild), s);
                    }

                    if (gx_preset::GxSettings::get_instance().setting_is_preset()) {
                        snprintf(s, sizeof(s), " %i%s%s ", static_cast<int>(guivar.show_patch_info),
                                 ". ", gx_preset::GxSettings::get_instance().get_current_name().c_str());
                        gtk_label_set_text(GTK_LABEL(parent), s);
                    } else {
                        guivar.show_patch_info = 0;
                        snprintf(s, sizeof(s), _(" %i%sMain Setting "),
                                 static_cast<int>(guivar.show_patch_info), ". ");
                        gtk_label_set_text(GTK_LABEL(parent), s);
                    }
                    fCache = *fZone;
                }
            }
            g_list_free(child_list);
        }
};

// ----- hide the PatchInfo widget
gboolean gx_delete_pi(GtkWidget *widget, gpointer   data ) {
    gtk_widget_hide(gw.patch_info);
    return TRUE;
}

void GxMainInterface::openPatchInfoBox(float* zone) {
    gw.patch_info = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_decorated(GTK_WINDOW(gw.patch_info), TRUE);
    gtk_window_set_icon(GTK_WINDOW(gw.patch_info), GDK_PIXBUF(gw.ib));
    gtk_window_set_resizable(GTK_WINDOW(gw.patch_info), FALSE);
    gtk_window_set_gravity(GTK_WINDOW(gw.patch_info), GDK_GRAVITY_SOUTH);
    gtk_window_set_transient_for(GTK_WINDOW(gw.patch_info), fWindow.gobj());
    gtk_window_set_position(GTK_WINDOW(gw.patch_info), GTK_WIN_POS_MOUSE);
    gtk_window_set_keep_below(GTK_WINDOW(gw.patch_info), FALSE);
    gtk_window_set_title(GTK_WINDOW(gw.patch_info), "Patch Info");
    gtk_window_set_type_hint(GTK_WINDOW(gw.patch_info), GDK_WINDOW_TYPE_HINT_UTILITY);
    gtk_window_set_destroy_with_parent(GTK_WINDOW(gw.patch_info), TRUE);
    GtkWidget * box = gtk_vbox_new(homogene, 8);
    const char *labe = "";
    GtkWidget*     la = gtk_label_new(labe);
    GtkWidget*     lab = gtk_label_new(labe);
    GtkWidget*     label = gtk_label_new(labe);
    new uiPatchDisplay(this, zone, GTK_WIDGET(gw.patch_info));
    g_signal_connect_swapped(G_OBJECT(gw.patch_info), "delete_event",
                             G_CALLBACK(gx_delete_pi), NULL);
    g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::info_box_expose), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(box), 8);

    GtkStyle *style = gtk_widget_get_style(lab);
    pango_font_description_set_size(style->font_desc, 30*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(lab, style->font_desc);

    gtk_container_add(GTK_CONTAINER(box), la);
    gtk_container_add(GTK_CONTAINER(box), lab);
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(gw.patch_info), box);

    gtk_widget_hide(gw.patch_info);
}

// ------------------------------ Num Display -----------------------------------

uiTuner::uiTuner(gx_engine::TunerAdapter& a)
    : Gtk::Alignment(0.5, 0.5, 0, 0),
      fTuner(),
      adapt(a) {
    add(fTuner);
    fTuner.show();
    adapt.signal_freq_changed().connect(
	sigc::mem_fun(*this, &uiTuner::freq_changed));
}

void uiTuner::freq_changed() {
    fTuner.set_freq(adapt.get_freq());
}

void GxMainInterface::addNumDisplay() {
    GxToolBox *box =  new GxToolBox(*this,
        pb_gxrack_expose, _("tuner"), GTK_WIDGET(fShowTuner.gobj()));

    box->rbox.add(fTuner);
    // box->window.set_size_request(200,140);
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), GTK_WIDGET(box->window.gobj()), expand, fill, 0);

    gw.tuner_widget = GTK_WIDGET(box->window.gobj());

    GList*   child_list =  gtk_container_get_children(GTK_CONTAINER(gw.rack_tool_bar));
    GtkWidget *box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    child_list =  gtk_container_get_children(GTK_CONTAINER(box1));
    box1 = reinterpret_cast<GtkWidget *>(g_list_nth_data(child_list, 0));
    g_list_free(child_list);

    GxTBox * tbox1 =  new GxTBox(*this);
    tbox1->m_tcb.set_parameter(fShowTuner.get_parameter());
    tbox1->m_tcb.m_label.set_text(_("tuner"));
    tbox1->m_tcb.set_tooltip_text(_("Show tuner"));
    gtk_container_add(GTK_CONTAINER(box1), GTK_WIDGET(tbox1->m_tcb.gobj()));
}

/* status icons in the main menu bar*/
struct uiStatusDisplay : public gx_ui::GxUiItemBool {
    GtkLabel* fLabel;

    uiStatusDisplay(gx_ui::GxUI* ui, bool* zone, GtkLabel* label)
        : gx_ui::GxUiItemBool(ui, zone), fLabel(label) {}

    virtual void reflectZone() {
	bool v = *fZone;
	fCache = v;
	if (GxMainInterface::get_instance().engine.midiaudiobuffer.plugin.on_off) {
	    if (GxMainInterface::get_instance().jack.get_jcpu_load() < 65.0) {
		if (v) {
		    gtk_status_icon_set_from_pixbuf(GTK_STATUS_ICON(gw.status_icon),
						    GDK_PIXBUF(gw.ibm));
		} else {
		    gtk_status_icon_set_from_pixbuf(GTK_STATUS_ICON(gw.status_icon),
						    GDK_PIXBUF(gw.ib));
		}
	    } else {
		gtk_status_icon_set_from_pixbuf(GTK_STATUS_ICON(gw.status_icon),
						GDK_PIXBUF(gw.ibr));
	    }
	} else {
	    gtk_status_icon_set_from_pixbuf(GTK_STATUS_ICON(gw.status_icon),
					    GDK_PIXBUF(gw.ib));
	}
    }
};

void GxMainInterface::addStatusDisplay(const char* label, bool* zone ) {
    GtkWidget* lw = gtk_label_new("");
    new uiStatusDisplay(this, zone, GTK_LABEL(lw));
    openFrameBox(label);
    addWidget(label, lw);
    closeBox();
    gtk_widget_hide(lw);
}

/* oscilloscope handling*/
bool GxMainInterface::on_refresh_oscilloscope() {
    static struct  {
        int load, frames;
        jack_nframes_t bsize;
        bool rt;
    } oc;
    int load = static_cast<int>(round(jack.get_jcpu_load()));
    if (!oc.bsize || oc.load != load) {
        oc.load = load;
        fWaveView.set_text(
            (boost::format(_("dsp load  %1% %%")) % oc.load).str().c_str(),
            Gtk::CORNER_TOP_LEFT);
    }
    int frames = jack.get_time_is()/100000;
    if (!oc.bsize || oc.frames != frames) {
        oc.frames = frames;
        fWaveView.set_text(
            (boost::format(_("ht frames %1%")) % oc.frames).str().c_str(),
            Gtk::CORNER_BOTTOM_LEFT);
    }
    bool is_rt = jack.get_is_rt();
    if (!oc.bsize || oc.rt != is_rt) {
        oc.rt = is_rt;
        fWaveView.set_text(
            oc.rt ? _("RT mode  yes ") : _("RT mode  <span color=\"#cc1a1a\">NO</span>"),
            Gtk::CORNER_BOTTOM_RIGHT);
    }
    if (!oc.bsize || oc.bsize != jack.get_jack_bs()) {
        oc.bsize = jack.get_jack_bs();
        fWaveView.set_text(
            (boost::format(_("latency    %1%")) % oc.bsize).str().c_str(),
            Gtk::CORNER_TOP_RIGHT);
    }
    fWaveView.queue_draw();
    return engine.oscilloscope.plugin.box_visible;
}

void GxMainInterface::addLiveWaveDisplay(const char* label) {
    GtkWidget * box      = gtk_hbox_new(false, 4);
    GtkWidget * box1      = gtk_vbox_new(false, 0);
    GtkWidget * box2      = gtk_vbox_new(false, 0);
    GtkWidget * e_box =  gtk_event_box_new();
    // gtk_container_set_border_width (GTK_CONTAINER(e_box),2);
    g_signal_connect(box, "expose-event", G_CALLBACK(gx_cairo::conv_widget_expose), NULL);
    gtk_widget_set_size_request(box, 303, 82);
    gtk_widget_set_size_request(e_box, 284, 54);
    gtk_container_set_border_width(GTK_CONTAINER(box), 12);
    gtk_container_add(GTK_CONTAINER(e_box), GTK_WIDGET(fWaveView.gobj()));
    // gtk_container_add(GTK_CONTAINER(box),e_box );
    gtk_box_pack_start(GTK_BOX(box), box1, true, true, 0);
    gtk_box_pack_start(GTK_BOX(box), e_box, false, false, 0);
    gtk_box_pack_start(GTK_BOX(box), box2, true, true, 0);
    addWidget(label, box);
    fWaveView.hide(); // was show()'n by addWidget
    fWaveView.property_text_pos_left() = 1.5;
    fWaveView.property_text_pos_right() = 77;
    fWaveView.set_multiplicator(150., 250.);
    gtk_widget_show(box);
    gtk_widget_hide(e_box);
}

/* set knobs in linear or radial mode*/
void GxMainInterface::set_mouse_mode() {
    if (fSetMouse.get_active()) {
        Gxw::Knob::set_jump_to_mouse(false);
    } else {
        Gxw::Knob::set_jump_to_mouse(true);
    }
}

//----------------------------- main menu ----------------------------
void GxMainInterface::addMainMenu() {
    /*-- Declare the GTK Widgets used in the menu --*/
    GtkWidget* menucont;  // menu container
    GtkWidget* menupix;  // menu container
    GtkWidget* hbox;      // top menu bar box container

    /*------------------ TOP Menu BAR ------------------*/
    hbox = gtk_hbox_new(FALSE, 0);

    /*-- Create the menu bar --*/
    menucont = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(hbox), menucont, TRUE, TRUE, 0);

    /*-- Create the pixmap menu bar --*/
    menupix = gtk_menu_bar_new();
    gtk_box_pack_end(GTK_BOX(hbox), menupix, TRUE, TRUE, 0);

    /*-- set packdirection for pixmaps from right to left --*/
    gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(menupix), GTK_PACK_DIRECTION_RTL);

    /*-- Engine on/off and status --*/
    // set up ON image: shown by default
    string img_path = options.get_pixmap_filepath("gx_on.png");

    gw.gx_engine_on_image =  gtk_image_menu_item_new_with_label("");
    GtkWidget* engineon = gtk_image_new_from_file(img_path.c_str());
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gw.gx_engine_on_image), engineon);
    gtk_menu_bar_append(GTK_MENU_BAR(menupix), gw.gx_engine_on_image);
    GtkTooltips* comandlin = gtk_tooltips_new();

    gtk_tooltips_set_tip(GTK_TOOLTIPS(comandlin),
                         gw.gx_engine_on_image, _("engine is on"), "engine state.");
    gtk_widget_show(gw.gx_engine_on_image);

    // set up OFF image: hidden by default
    img_path = options.get_pixmap_filepath("gx_off.png");

    gw.gx_engine_off_image =  gtk_image_menu_item_new_with_label("");
    GtkWidget* engineoff = gtk_image_new_from_file(img_path.c_str());
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gw.gx_engine_off_image), engineoff);
    gtk_menu_bar_append(GTK_MENU_BAR(menupix), gw.gx_engine_off_image);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(comandlin),
                         gw.gx_engine_off_image, _("engine is off"), "engine state.");
    gtk_widget_hide(gw.gx_engine_off_image);

    // set up BYPASS image: hidden by default
    img_path = options.get_pixmap_filepath("gx_bypass.png");

    gw.gx_engine_bypass_image  =  gtk_image_menu_item_new_with_label("");
    GtkWidget* engineby = gtk_image_new_from_file(img_path.c_str());
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gw.gx_engine_bypass_image), engineby);
    gtk_menu_bar_append(GTK_MENU_BAR(menupix), gw.gx_engine_bypass_image);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(comandlin),
                         gw.gx_engine_bypass_image, _("engine is in bypass mode"), "engine state.");
    gtk_widget_hide(gw.gx_engine_bypass_image);


    /*-- Jack server status image --*/
    // jackd ON image
    img_path = options.get_pixmap_filepath("jackd_on.png");

    gw.gx_jackd_on_image =  gtk_image_menu_item_new_with_label("");
    GtkWidget*   jackstateon = gtk_image_new_from_file(img_path.c_str());
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gw.gx_jackd_on_image), jackstateon);
    gtk_menu_bar_append(GTK_MENU_BAR(menupix), gw.gx_jackd_on_image);

    GtkTooltips* comandline = gtk_tooltips_new();

    gtk_tooltips_set_tip(GTK_TOOLTIPS(comandline),
                         gw.gx_jackd_on_image, _("jack server is connected"), "jack server state.");

    gtk_widget_show(gw.gx_jackd_on_image);

    // jackd OFF image: hidden by default
    img_path = options.get_pixmap_filepath("jackd_off.png");

    gw.gx_jackd_off_image =  gtk_image_menu_item_new_with_label("");
    GtkWidget*   jackstateoff = gtk_image_new_from_file(img_path.c_str());
    gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(gw.gx_jackd_off_image), jackstateoff);
    gtk_menu_bar_append(GTK_MENU_BAR(menupix), gw.gx_jackd_off_image);
    gtk_tooltips_set_tip(GTK_TOOLTIPS(comandline),
                         gw.gx_jackd_off_image, _("jack server is unconnected"),
                         "jack server state.");
    gtk_widget_hide(gw.gx_jackd_off_image);


    /* ----------------------------------------------------------- */
    fMenuList["Top"] = menucont;

    addEngineMenu();
    addPresetMenu();
    addPluginMenu();
    addAmpMenu();
    addOptionMenu();
    addAboutMenu();

    /*---------------- add menu to main window box----------------*/
    gtk_box_pack_start(GTK_BOX(fBox[fTop]), hbox , FALSE, FALSE, 0);
    gtk_widget_show(menucont);
    gtk_widget_show(menupix);
    gtk_widget_show(hbox);
}



//----------------------------- engine menu ----------------------------
void GxMainInterface::addEngineMenu() {
    GtkWidget* menulabel;   // menu label
    // GtkWidget* menucont;    // menu container use gw.menuh for systray menu here
    GtkWidget* menuitem;    // menu item
    //GSList   * group = NULL;

    /*---------------- Create Engine menu items ------------------*/
    gw.menuh = fMenuList["Top"];

    menulabel = gtk_menu_item_new_with_mnemonic(_("_Engine"));
    gtk_menu_bar_append(GTK_MENU_BAR(gw.menuh), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create Engine submenu  --*/
    gw.menuh = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), gw.menuh);
    gtk_widget_show(gw.menuh);
    fMenuList["Engine"] = gw.menuh;

    /*-- Create Engine start / stop item  --*/
    //group = NULL;

    menuitem = gtk_check_menu_item_new_with_mnemonic(_("Engine _Start / _Stop"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_space, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);

    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), menuitem);
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), TRUE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_engine_switch), (gpointer)0);
    gw.gx_engine_item = menuitem; // save into global var
    gtk_widget_show(menuitem);

    /*-- Create Engine bypass item  --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("Engine _Bypass"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_b, GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);

    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), menuitem);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_engine_switch), (gpointer)1);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    GtkWidget* sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), sep);
    gtk_widget_show(sep);

    /*---------------- Create Jack Server menu --------------------*/
    addJackServerMenu();

    /*---------------- End Jack server menu declarations ----------------*/

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), sep);
    gtk_widget_show(sep);

    /*-- create Midi Controller Table menu item --*/
    menuitem = gtk_check_menu_item_new_with_mnemonic(_("M_idi Controller"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_i, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(
        GTK_OBJECT(menuitem), "activate",
        G_CALLBACK(gx_main_midi::MidiControllerTable::toggle), menuitem);
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), sep);
    gtk_widget_show(sep);

    /*-- Create Exit menu item under Engine submenu --*/
    Gtk::MenuItem* item = new Gtk::MenuItem(_("_Quit"), true); //FIXME
    item->add_accelerator("activate", fAccelGroup, GDK_q, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    item->signal_activate().connect(
	sigc::mem_fun(*this, &GxMainInterface::save_window_position));
    item->signal_activate().connect(sigc::ptr_fun(Gtk::Main::quit));
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), GTK_WIDGET(item->gobj()));
    item->show();

    /*---------------- End Engine menu declarations ----------------*/
}

//----------------------------- preset menu ----------------------------
void GxMainInterface::addPresetMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item

    menucont = fMenuList["Top"];

    /*---------------- Create Presets menu items --------------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Presets"));
    gtk_menu_bar_append(GTK_MENU_BAR(menucont), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create Presets submenus --*/
    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);
    fMenuList["Presets"] = menucont;
    
    const char* preset_accel_path[] = {
        "<gx_head>/Load",
        "<gx_head>/Save",
        "<gx_head>/Rename",
        "<gx_head>/Delete"
    };

    const char* preset_menu_name[] = {
        N_("_Load Preset..."),
        N_("_Save Preset..."),
        N_("_Rename Preset..."),
        N_("_Delete Preset...")
    };

    /* special treatment of preset lists, from gx_preset namespace */
    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++) {
        GtkWidget* menuItem =
            gtk_menu_item_new_with_mnemonic(gettext(preset_menu_name[i]));
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuItem);

        GtkWidget* menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);

        gtk_menu_set_accel_path(GTK_MENU(menu), preset_accel_path[i]);

        gx_preset::gxpreset.presmenu[i] = menu;
        gx_preset::gxpreset.presMenu[i] = menuItem;
    }

    GtkWidget* menuItem =
            gtk_menu_item_new_with_mnemonic(_("Factory Settings"));
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuItem);

        GtkWidget* menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);

        gx_preset::gxpreset.fpresmenu = menu;

    gtk_widget_show(menuItem);

    menuitem = gtk_menu_item_new_with_mnemonic("funkmuscle");
    menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.fpresmenu), menuitem, 0);
    gx_preset::gxpreset.ffpresmenu[0] = menu;

    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_mnemonic("zettberlin");
    menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.fpresmenu), menuitem, 0);
    gx_preset::gxpreset.ffpresmenu[1] = menu;

    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_mnemonic("autoandimat");
    menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.fpresmenu), menuitem, 0);
    gx_preset::gxpreset.ffpresmenu[3] = menu;

    gtk_widget_show(menuitem);
    
    menuitem = gtk_menu_item_new_with_mnemonic("StudioDave");
    menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.fpresmenu), menuitem, 0);
    gx_preset::gxpreset.ffpresmenu[2] = menu;

    gtk_widget_show(menuitem);
    
    menuitem = gtk_menu_item_new_with_mnemonic("JP");
    menu = gtk_menu_new();
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.fpresmenu), menuitem, 0);
    gx_preset::gxpreset.ffpresmenu[4] = menu;

    gtk_widget_show(menuitem);

    /*-- add New Preset saving under Save Presets menu */
    menuitem = gtk_menu_item_new_with_mnemonic(_("New _Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_save_newpreset_dialog), NULL);
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_p, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.presmenu[SAVE_PRESET_LIST]), menuitem, 0);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    GtkWidget* sep = gtk_separator_menu_item_new();
    gtk_menu_shell_insert(GTK_MENU_SHELL(gx_preset::gxpreset.presmenu[SAVE_PRESET_LIST]), sep, 1);
    gtk_widget_show(sep);

    for (int i = 0; i < GX_NUM_OF_PRESET_LISTS; i++)
        gtk_widget_show(gx_preset::gxpreset.presMenu[i]);

    /* ------------------- */

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create patch info menu item under Options submenu --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("P_atch Info"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_a, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_patch), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create load presetfile menu --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("Load Preset-_file"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_f, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_load_preset_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- Create save as presetfile menu--*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("E_xport Preset-file"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_x, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_save_preset_file), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create  Main setting submenu --*/
    Gtk::MenuItem* item = new Gtk::MenuItem(_("Recall Main _Setting"), true); //FIXME
    item->add_accelerator("activate", fAccelGroup, GDK_s, (Gdk::ModifierType)0, Gtk::ACCEL_VISIBLE);
    item->signal_activate().connect(
	sigc::mem_fun(gx_preset::gxpreset, &gx_preset::GxPreset::gx_recall_settings_file));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(item->gobj()));
    item->show();

    menuitem = gtk_menu_item_new_with_mnemonic(_("_Save As Main _Setting"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_save_main_setting), NULL);
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_s, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create sub menu More Preset Action --*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("More Preset Options..."));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menulabel);
    gtk_widget_show(menulabel);

    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);
    fMenuList["ExtraPresets"] = menucont;

    /*--------------- Extra preset menu */
    addExtraPresetMenu();
    gx_settings.signal_presetfile_changed().connect(
	sigc::mem_fun(gx_preset::gxpreset,
		      &gx_preset::GxPreset::gx_refresh_preset_menus));
}

//------------------------ extra preset menu ----------------------------
void GxMainInterface::addExtraPresetMenu() {
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item

    menucont = fMenuList["ExtraPresets"];

    /*---------------- Create Presets menu items --------------------*/

    /* forward preset */
    menuitem = gtk_menu_item_new_with_mnemonic(_("Next _Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_next_preset), NULL);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_Page_Down,
                               GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /* rewind preset */
    menuitem = gtk_menu_item_new_with_mnemonic(_("Previous _Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_previous_preset), NULL);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_Page_Up,
                               GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    GtkWidget* sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create  menu item Delete Active preset --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("_Save Active Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_save_oldpreset), (gpointer)1);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_s,
                               GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_mnemonic(_("_Rename Active Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_rename_active_preset_dialog), NULL);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_r,
                               GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    menuitem = gtk_menu_item_new_with_mnemonic(_("_Delete Active Preset"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_delete_active_preset_dialog), NULL);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_Delete,
                               GDK_NO_MOD_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create  menu item Delete All presets --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("_Delete All Presets"));
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_preset::gxpreset.gx_delete_all_presets_dialog), NULL);
    gtk_widget_add_accelerator(menuitem, "activate",
                               fAccelGroup->gobj(), GDK_d,
                               GdkModifierType(GDK_CONTROL_MASK|GDK_SHIFT_MASK), GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);
}

/****************************************************************
 ** KeyFinder
 ** finds next unused Key in a GtkAccelGroup
 */

class KeyFinder {
private:
    typedef list<GtkAccelKey> accel_list;
    unsigned int next_key;
    accel_list l;
    static gboolean add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data);
public:
    KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group);
    ~KeyFinder();
    int operator()();
};

KeyFinder::KeyFinder(Glib::RefPtr<Gtk::AccelGroup> group) {
    next_key = GDK_a;
    gtk_accel_group_find(group->gobj(), add_keys_to_list, static_cast<gpointer>(&l));
}

KeyFinder::~KeyFinder() {
}

gboolean KeyFinder::add_keys_to_list(GtkAccelKey *key, GClosure *cl, gpointer data) {
    accel_list* l = (accel_list*)data;
    if (key->accel_mods == GDK_SHIFT_MASK) {
	l->push_back(*key);
    }
    return false;
}

int KeyFinder::operator()() {
    while (next_key <= GDK_z) {
	bool found = false;
	for (accel_list::iterator i = l.begin(); i != l.end(); ++i) {
	    if (next_key == i->accel_key) {
		found = true;
		break;
	    }
	}
	if (!found) {
	    return next_key++;
	}
	next_key++;
    }
    return -1;
}


/****************************************************************
 ** GxUiRadioMenu
 ** adds the values of an UEnumParameter as Gtk::RadioMenuItem's
 ** to a Gtk::MenuShell
 */

class GxUiRadioMenu: public gx_ui::GxUiItemInt {
private:
    vector<Gtk::RadioMenuItem*> items;
    Gtk::RadioButtonGroup group;
    UIntParameter& param;
    virtual void reflectZone();
    void on_activate(int i);
public:
    static GxUiRadioMenu* create(
	gx_ui::GxUI* ui, Glib::RefPtr<Gtk::AccelGroup>& ag,
	const char *id, Gtk::MenuShell& menucont);
    GxUiRadioMenu(gx_ui::GxUI* ui, Glib::RefPtr<Gtk::AccelGroup>& ag,
		  UIntParameter& param, Gtk::MenuShell& menucont);
    virtual ~GxUiRadioMenu();
};

GxUiRadioMenu* GxUiRadioMenu::create(
    gx_ui::GxUI* ui, Glib::RefPtr<Gtk::AccelGroup>& ag,
    const char *id, Gtk::MenuShell& menucont) {
    return new GxUiRadioMenu(ui, ag, parameter_map[id].getUInt(),menucont);
}

class TubeKeys {
private:
    static unsigned int keysep[];
    unsigned int ks;
public:
    TubeKeys(): ks(0) {};
    int operator()();
};

unsigned int TubeKeys::keysep[] = {
    GDK_v, GDK_u, GDK_q, GDK_e, 0,
    GDK_w, 0,
    GDK_n, GDK_d, GDK_q, GDK_t, 0,
    GDK_z, GDK_y, GDK_k, GDK_o, 0,
    GDK_h, GDK_j, GDK_l, GDK_g
};

inline int TubeKeys::operator()() {
    if (ks < sizeof(keysep)/sizeof(keysep[0])) {
	return keysep[ks++];
    }
    return -1;
}

GxUiRadioMenu::GxUiRadioMenu(gx_ui::GxUI* ui, Glib::RefPtr<Gtk::AccelGroup>& ag,
			     UIntParameter& param_, Gtk::MenuShell& menucont):
    gx_ui::GxUiItemInt(ui, reinterpret_cast<int*>(&param_.value)), //FIXME
    param(param_)
{
    int i, c;
    const value_pair *p;
    TubeKeys next_key;
    //KeyFinder next_key(ag); // uncomment to find out which keys are free...
    items.reserve(param.upper-param.lower+1);
    for (p = param.getValueNames(), i = 0; p->value_id; p++, i++) {
	Gtk::RadioMenuItem *r = new Gtk::RadioMenuItem(group, param.value_label(*p));
	c = next_key();
	if (c == 0) {
	    Gtk::SeparatorMenuItem* sep = new Gtk::SeparatorMenuItem();
	    menucont.append(*sep);
	    sep->show();
	    c = next_key();
	}
	items[i] = r;
	if (c > 0) {
	    r->add_accelerator("activate", ag, c, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
	}
	r->signal_activate().connect(
	    sigc::bind<int>(sigc::mem_fun(*this, &GxUiRadioMenu::on_activate), i));
	menucont.append(*r);
	r->show();
    }
}

GxUiRadioMenu::~GxUiRadioMenu() {
    for (vector<Gtk::RadioMenuItem*>::iterator i = items.begin(); i != items.end(); ++i) {
	delete *i;
    }
}

void GxUiRadioMenu::reflectZone() {
    int v = *fZone;
    fCache = v;
    items[v]->set_active(true);
}

void GxUiRadioMenu::on_activate(int i) {
    param.set(i);
}

//----------------------------- preset menu ----------------------------
void GxMainInterface::addAmpMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    menucont = fMenuList["Top"];

    /*---------------- Create Options menu items ------------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Tube "));
    gtk_menu_bar_append(GTK_MENU_BAR(menucont), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create Options submenu  --*/
    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);

    GxUiRadioMenu::create(this, this->fAccelGroup, "tube.select", *Glib::wrap(GTK_MENU_SHELL(menucont)));
}

//----------------------------- preset menu ----------------------------
void GxMainInterface::addPluginMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menucontin;  // menu container
    GtkWidget* sep;  // menu separator

    menucont = fMenuList["Top"];

    /*---------------- Create Options menu items ------------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("P_lugins"));
    gtk_menu_bar_append(GTK_MENU_BAR(menucont), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create Options submenu  --*/
    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);
    fMenuList["PluginMenu"] = menucont;

    /*-- Create toolbar check menu item under Options submenu --*/
    fShowToolBar.set_label(_("Show Plugin _Bar"));
    fShowToolBar.add_accelerator("activate", fAccelGroup,
                               GDK_b, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
    fShowToolBar.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_toolbar_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowToolBar.gobj()));
    fShowToolBar.show();
    fShowToolBar.set_parameter(new SwitchParameter("system.show_toolbar"));

    /*-- Create mono rack check menu item under Options submenu --*/
    fShowRRack.set_label(_("Show _Rack"));
    fShowRRack.add_accelerator("activate", fAccelGroup,
                               GDK_r, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
    fShowRRack.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_rrack_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowRRack.gobj()));
    fShowRRack.show();
    fShowRRack.set_parameter(new SwitchParameter("system.show_rrack"));

    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);

    /*-- Create mono rack check menu item under Options submenu --*/
    fShowRack.set_label(_("Show Mono _Rack"));
    fShowRack.add_accelerator("activate", fAccelGroup,
                               GDK_m, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
    fShowRack.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_rack_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowRack.gobj()));
    fShowRack.show();
    fShowRack.set_parameter(new SwitchParameter("system.show_rack"));
    /*-- Create mono plugin menu soket item under Options submenu --*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Mono Plugins"));

    gtk_menu_append(GTK_MENU(menucont), menulabel);
    gtk_widget_show(menulabel);

    menucontin = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucontin);
    gtk_widget_show(menucontin);

    fMenuList["PluginsMono"] = menucontin;
    gw.menu_mono_rack = fMenuList["PluginMenu"];
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);
    /*-- create midi out menu  --*/
    fShowMidiOut.set_label(_("MIDI out"));
    fShowMidiOut.add_accelerator("activate", fAccelGroup,
                               GDK_a, Gdk::LOCK_MASK, Gtk::ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(fShowMidiOut.gobj()), "activate",
                      G_CALLBACK(gx_midi_out), NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menucontin), GTK_WIDGET(fShowMidiOut.gobj()));
    fShowMidiOut.show();
    fShowMidiOut.set_parameter(new SwitchParameter("ui.midi_out"));

    /*-- add a separator line --*/
    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), sep);
    gtk_widget_show(sep);

    /*-- Create stereo rack check menu item under Options submenu --*/
    fShowSRack.set_label(_("Show _Stereo Rack"));
    fShowSRack.add_accelerator("activate", fAccelGroup,
                               GDK_s, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
    fShowSRack.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_srack_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowSRack.gobj()));
    fShowSRack.show();
    fShowSRack.set_parameter(new SwitchParameter("system.show_Srack"));

    /*-- Create stereo plugin menu soket item under Options submenu --*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Stereo Plugins"));

    gtk_menu_append(GTK_MENU(menucont), menulabel);
    gtk_widget_show(menulabel);

    menucontin = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucontin);
    gtk_widget_show(menucontin);

    fMenuList["PluginsStereo"] = menucontin;
    gw.menu_stereo_rack = fMenuList["PluginsStereo"];

    sep = gtk_separator_menu_item_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), sep);
    gtk_widget_show(sep);
}
//----------------------------- option menu ----------------------------

static void set_tooltips(bool v) {
    gtk_settings_set_long_property(
        gtk_settings_get_default(), "gtk-enable-tooltips", v,
        "gx_head menu-option");
}

void reset_all_parameters(GtkWidget*, gpointer) {
    for (ParamMap::iterator i = parameter_map.begin(); i != parameter_map.end(); ++i) {
        i->second->set_std_value();
    }
}

void GxMainInterface::addOptionMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item

    menucont = fMenuList["Top"];

    /*---------------- Create Options menu items ------------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Options"));
    gtk_menu_bar_append(GTK_MENU_BAR(menucont), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create Options submenu  --*/
    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);
    fMenuList["Options"] = menucont;

    /*-- Create Open check menu item under Options submenu --*/
    menuitem = gtk_check_menu_item_new_with_mnemonic(_("_Meterbridge"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_m, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_child_process::Meterbridge::start_stop), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- Create tuner check menu item under Options submenu --*/
    fShowTuner.set_label(_("_Tuner"));
    fShowTuner.add_accelerator("activate", fAccelGroup,
                               GDK_t, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowTuner.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_tuner_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowTuner.gobj()));
    fShowTuner.show();
    fShowTuner.set_parameter(new SwitchParameter("system.show_tuner"));

    /*-- Create skin menu under Options submenu--*/
    addGuiSkinMenu();

    fSetMouse.set_label(_("Set _Knobs Linear"));
    fSetMouse.add_accelerator("activate", fAccelGroup,
                               GDK_k, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fSetMouse.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::set_mouse_mode));
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fSetMouse.gobj()));
    fSetMouse.show();
    fSetMouse.set_parameter(new SwitchParameter("system.set_mouse"));

    /*-- Create logbox check menu item under Options submenu --*/
    fShowLogger.set_label(_("Show _Logging Box"));
    fShowLogger.add_accelerator("activate", fAccelGroup,
                               GDK_l, Gdk::CONTROL_MASK, Gtk::ACCEL_VISIBLE);
    fShowLogger.signal_activate().connect(
        sigc::mem_fun(*this, &GxMainInterface::on_log_activate));
    gtk_menu_shell_append(GTK_MENU_SHELL(fMenuList["Options"]), GTK_WIDGET(fShowLogger.gobj()));
    fShowLogger.show();
    fShowLogger.set_parameter(new SwitchParameter("system.show_logger"));

    /*-- Create menu item to control tooltip display --*/
    fShowTooltips.set_label(_("Show _Tooltips"));
    fShowTooltips.show();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fShowTooltips.gobj()));
    SwitchParameter *p = new SwitchParameter("system.show_tooltips");
    fShowTooltips.set_parameter(p);
    fShowTooltips.set_active(true);
    p->signal_changed().connect(ptr_fun(set_tooltips));

    /*-- create option for saving midi controller settings in presets --*/
    fMidiInPreset.set_label(_("Include MIDI in _presets"));
    fMidiInPreset.show();
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), GTK_WIDGET(fMidiInPreset.gobj()));
    fMidiInPreset.set_parameter(new SwitchParameter("system.midi_in_preset"));

    /*-- create option for resetting gx_head settings --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("Reset _All Parameters"));
    gtk_widget_show(menuitem);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                     G_CALLBACK(reset_all_parameters), NULL);
}


//----------------------------- skin menu ----------------------------
void GxMainInterface::addGuiSkinMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item
    GSList   * group = NULL;

    menucont = fMenuList["Options"];

    /*---------------- Create skin menu items ------------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Skin..."));
    gtk_menu_append(GTK_MENU(menucont), menulabel);
    gtk_widget_show(menulabel);

    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);
    gtk_widget_show(menucont);
    fMenuList["Skin"] = menucont;

    /* Create black skin item under skin submenu --*/
    int idx = 0;
    for (vector<string>::iterator i = options.skin.skin_list.begin();
	 i != options.skin.skin_list.end();
	 ++i) {
	menuitem =
            gtk_radio_menu_item_new_with_label(group, i->c_str());
        group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(menuitem));
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), FALSE);
        g_signal_connect(GTK_OBJECT(menuitem), "activate",
			 G_CALLBACK(gx_change_skin), GINT_TO_POINTER(idx++));
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        gtk_widget_show(menuitem);
    }

    menucont = fMenuList["Options"];

    menuitem = gtk_menu_item_new();
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_s, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_cycle_through_skin), NULL);
    gtk_menu_append(GTK_MENU(menucont), menuitem);
    gtk_widget_show(menuitem);

    /*-- End skin menu declarations --*/
}

// ----------------------------- about menu ----------------------------


void GxMainInterface::addAboutMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item

    menucont = fMenuList["Top"];

    /*---------------- Start About menu declarations ----------------*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_About"));
    gtk_menu_bar_append(GTK_MENU_BAR(menucont), menulabel);
    gtk_widget_show(menulabel);

    /*-- Create About submenu --*/
    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);

    /*-- Create About menu item under About submenu --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("_About"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_a, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                     G_CALLBACK(gx_show_about), NULL);
    gtk_widget_show(menuitem);

    /*-- Create Help menu item under About submenu --*/
    menuitem = gtk_menu_item_new_with_mnemonic(_("_Help"));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_h, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
    //    g_signal_connect(GTK_OBJECT (menuitem), "activate", G_CALLBACK (gx_show_about), NULL);
    gtk_widget_show(menuitem);
    /*---------------- End About menu declarations ----------------*/
}

void GxMainInterface::gx_jack_connection(GtkCheckMenuItem* p, gpointer arg) {
    static_cast<GxMainInterface*>(arg)->connect_jack(
	gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(p)));
}

// ----- change the jack buffersize on the fly is still experimental, give a warning
enum GxJackLatencyChange {
    kChangeLatency = 1,
    kKeepLatency   = 2
};

gint gx_wait_latency_warn() {
    GtkWidget* warn_dialog = gtk_dialog_new();
    gtk_window_set_destroy_with_parent(GTK_WINDOW(warn_dialog), TRUE);

    GtkWidget* box     = gtk_vbox_new(0, 4);
    GtkWidget* labelt  = gtk_label_new(_("\nWARNING\n"));
    GtkWidget* labelt1 = gtk_label_new(_("CHANGING THE JACK_BUFFER_SIZE ON THE FLY \n"
                                       "MAY CAUSE UNPREDICTABLE EFFECTS \n"
                                       "TO OTHER RUNNING JACK APPLICATIONS. \n"
                                       "DO YOU WANT TO PROCEED ?"));
    GdkColor colorGreen;
    gdk_color_parse("#969292", &colorGreen);
    gtk_widget_modify_fg(labelt1, GTK_STATE_NORMAL, &colorGreen);

    GtkStyle *style1 = gtk_widget_get_style(labelt1);
    pango_font_description_set_size(style1->font_desc, 10*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt1, style1->font_desc);

    gdk_color_parse("#ffffff", &colorGreen);
    gtk_widget_modify_fg(labelt, GTK_STATE_NORMAL, &colorGreen);
    style1 = gtk_widget_get_style(labelt);
    pango_font_description_set_size(style1->font_desc, 14*PANGO_SCALE);
    pango_font_description_set_weight(style1->font_desc, PANGO_WEIGHT_BOLD);
    gtk_widget_modify_font(labelt, style1->font_desc);

    GtkWidget* button1 =
        gtk_dialog_add_button(GTK_DIALOG(warn_dialog),
                              _("Yes"), kChangeLatency);

    GtkWidget* button2 =
        gtk_dialog_add_button(GTK_DIALOG(warn_dialog),
                              _("No"),  kKeepLatency);


    GtkWidget* box1    = gtk_hbox_new(0, 4);
    GtkWidget* box2    = gtk_hbox_new(0, 4);

    GtkWidget* disable_warn = gtk_check_button_new();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(disable_warn), FALSE);
    g_signal_connect(disable_warn, "clicked",
                     G_CALLBACK(gx_user_disable_latency_warn), NULL);

    GtkWidget * labelt2 =
        gtk_label_new(_("Don't bother me again with such a question, "
                       "I know what I am doing"));

    gtk_container_add(GTK_CONTAINER(box),  labelt);
    gtk_container_add(GTK_CONTAINER(box),  labelt1);
    gtk_container_add(GTK_CONTAINER(box),  box2);
    gtk_container_add(GTK_CONTAINER(box),  box1);
    gtk_container_add(GTK_CONTAINER(box1), disable_warn);
    gtk_container_add(GTK_CONTAINER(box1), labelt2);
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(warn_dialog)->vbox), box);

    gtk_widget_modify_fg(labelt2, GTK_STATE_NORMAL, &colorGreen);

    GtkStyle *style = gtk_widget_get_style(labelt2);
    pango_font_description_set_size(style->font_desc, 8*PANGO_SCALE);
    pango_font_description_set_weight(style->font_desc, PANGO_WEIGHT_NORMAL);
    gtk_widget_modify_font(labelt2, style->font_desc);

    g_signal_connect_swapped(button1, "clicked",
                             G_CALLBACK(gtk_widget_destroy), warn_dialog);
    g_signal_connect_swapped(button2, "clicked",
                             G_CALLBACK(gtk_widget_destroy), warn_dialog);

    gtk_widget_show_all(box);

    return gtk_dialog_run(GTK_DIALOG(warn_dialog));
}

// check user's decision to turn off latency change warning
void gx_user_disable_latency_warn(GtkWidget* wd, gpointer arg) {
    GtkToggleButton* button = GTK_TOGGLE_BUTTON(wd);
    gx_engine::audio.fwarn = gtk_toggle_button_get_active(button);
}


// refresh latency check menu
void GxMainInterface::refresh_latency_menu() {
    GtkWidget* wd = getJackLatencyItem(jack.get_jack_bs());
    if (wd) {
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);
    }
}

bool GxMainInterface::connect_jack(bool v) {
    if (jack.gx_jack_connection(v)) {
	return true;
    }
    if (!v) {
	gx_system::gx_print_error(_("main"), _("can't disconnect jack"));
	return false;
    }
    if (!gx_gui::gx_start_jack_dialog()) {
	gx_system::gx_print_error(_("main"),
				  string(_("Ignoring jackd ...")));
	return false;
    }
    for (int i = 0; i < 5; i++) {
	usleep(500000);
	if (gx_system::gx_system_call("pgrep", "jackd", true) == SYSTEM_OK) {
	    break;
	}
    }
    gx_system::gx_print_warning(_("Jack Init"),
				_("jackd OK, trying to be a gxjack.client"));
    for (int i = 0; i < 10; i++) {
	if (jack.gx_jack_connection(true)) {
	    sleep(4);
	    return true;
	}
	usleep(500000);
    }
    gx_system::gx_print_error(
	_("main"),
	string(_("I really tried to get jack up and running, sorry ... ")));
    return false;
}

// ----jack latency change
void gx_set_jack_buffer_size(GtkCheckMenuItem* menuitem, gpointer arg) {
    GxMainInterface& self = GxMainInterface::get_instance();
    // requested latency
    jack_nframes_t buf_size = (jack_nframes_t)GPOINTER_TO_INT(arg);

    // are we a proper jack gxjack.client ?
    if (!self.jack.client) {
        gx_system::gx_print_error(
            _("Jack Buffer Size setting"),
            _("we are not a jack gxjack.client, server may be down")
            );

        return;
    }

    // ----- if check button triggered menually

    // let's avoid triggering the jack server on "inactive"
    if (gtk_check_menu_item_get_active(menuitem) == false) {
        return;
    }
    // if the actual buffer size is the same, no need further action
    if (buf_size == jack_get_buffer_size(self.jack.client)) {
        return;
    }

    // first time useage warning
    GxJackLatencyChange change_latency = kChangeLatency;

    // if user still wants to be given a choice, let's trigger dialog
    if (!gx_engine::audio.fwarn)
        change_latency = (GxJackLatencyChange)gx_gui::gx_wait_latency_warn();

    // let's see
    if (change_latency == kChangeLatency) {
        // let's resize the buffer
        if (jack_set_buffer_size(self.jack.client, buf_size) != 0)
            gx_system::gx_print_warning(_("Setting Jack Buffer Size"),
                             _("Could not change latency"));
    } else { // restore latency status
        // refresh latency check menu
        gx_gui::GxMainInterface& gui = gx_gui::GxMainInterface::get_instance();
        GtkWidget* wd = gui.getJackLatencyItem(self.jack.get_jack_bs());
        if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);
    }
    gx_system::gx_print_info(
	_("Jack Buffer Size"),
	boost::format(_("latency is %1%")) % jack_get_buffer_size(self.jack.client));
}


/*---------------- Jack Server Menu ----------------*/
void GxMainInterface::addJackServerMenu() {
    GtkWidget* menulabel; // menu label
    GtkWidget* menucont;  // menu container
    GtkWidget* menuitem;  // menu item
    GSList   * group = NULL;

    menucont = fMenuList["Engine"];

    /*-- Create Jack Connection toggle button --*/
    menuitem = gtk_check_menu_item_new_with_mnemonic(_("Jack Server _Connection "));
    gtk_widget_add_accelerator(menuitem, "activate", fAccelGroup->gobj(),
                               GDK_c, GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE);
    g_signal_connect(GTK_OBJECT(menuitem), "activate",
                      G_CALLBACK(gx_jack_connection), this);
    gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);

    gtk_widget_show(menuitem);
    fJackConnectItem = menuitem;

    /*-- create Jack Ports menu item --*/
    portmap_item.add_accelerator(
	"activate", fAccelGroup, GDK_p, Gdk::SHIFT_MASK, Gtk::ACCEL_VISIBLE);
    portmap_item.signal_activate().connect(
	sigc::mem_fun(*this, &GxMainInterface::on_portmap_activate));
    portmap_item.show();
    gtk_menu_shell_append(GTK_MENU_SHELL(gw.menuh), GTK_WIDGET(portmap_item.gobj()));

    /*-- Create  Latency submenu under Jack Server submenu --*/
    menulabel = gtk_menu_item_new_with_mnemonic(_("_Latency"));
    gtk_menu_append(GTK_MENU(menucont), menulabel);
    gtk_widget_show(menulabel);

    menucont = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menulabel), menucont);

    /*-- Create  menu item under Latency submenu --*/
    gchar buf_size[8];
    const int min_pow = 5;  // 2**5  = 32
    const int max_pow = 13; // 2**13 = 8192
    group = NULL;
        int jack_buffer_size = static_cast<int>(16);
        (void)snprintf(buf_size, sizeof(buf_size), "%d", jack_buffer_size);
        menuitem = gtk_radio_menu_item_new_with_label(group, buf_size);
        group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(menuitem));
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), FALSE);

        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                          G_CALLBACK(gx_set_jack_buffer_size),
                          GINT_TO_POINTER(jack_buffer_size));

        // display actual buffer size as default
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        gtk_widget_show(menuitem);

    for (int i = min_pow; i <= max_pow; i++) {
        int jack_buffer_size = static_cast<int>(pow(2., i));
        (void)snprintf(buf_size, sizeof(buf_size), "%d", jack_buffer_size);
        menuitem = gtk_radio_menu_item_new_with_label(group, buf_size);
        group = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(menuitem));
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(menuitem), FALSE);

        g_signal_connect(GTK_OBJECT(menuitem), "activate",
                          G_CALLBACK(gx_set_jack_buffer_size),
                          GINT_TO_POINTER(jack_buffer_size));

        // display actual buffer size as default
        gtk_menu_shell_append(GTK_MENU_SHELL(menucont), menuitem);
        gtk_widget_show(menuitem);

        fJackLatencyItem[i-min_pow] = menuitem;
    }
}

void GxMainInterface::on_portmap_response(int) {
    portmap_item.set_active(false);
}

void GxMainInterface::on_portmap_activate() {
    if (portmap_item.get_active()) {
	if (portmap_window) {
	    return;
	}
	portmap_window = gx_portmap::PortMapWindow::create(jack, *this, fAccelGroup);
	portmap_window->signal_response().connect(
	    sigc::mem_fun(*this, &GxMainInterface::on_portmap_response));
    } else {
	if (!portmap_window) {
	    return;
	}
	delete portmap_window;
	portmap_window = 0;
    }
}

void GxMainInterface::set_waveview_buffer(unsigned int size) {
    fWaveView.set_frame(engine.oscilloscope.get_buffer(), size);
}

// ---- show main GUI
void GxMainInterface::show() {
    assert(fTop == 0);
    fInitialized = true;

    if (jack.client) {
        // refresh some GUI stuff
        gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(fJackConnectItem), TRUE);

        GtkWidget* wd = getJackLatencyItem(jack.get_jack_bs());
        if (wd) gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(wd), TRUE);
    } else {
        gtk_widget_hide(gx_gui::gw.gx_jackd_on_image);
        gtk_widget_show(gx_gui::gw.gx_jackd_off_image);
    }
    
    gint mainxorg = gx_set_mx_oriantation();
    gint mainyorg = gx_set_my_oriantation();
    fWindow.move(mainxorg, mainyorg);
    gtk_widget_show(fBox[0]);
    // ----- set the last used skin when no cmd is given
    if (gx_engine::audio.fskin) {
	gx_update_skin_menu_item(gx_engine::audio.fskin);
    } else {
	gx_update_skin(gx_engine::audio.fskin, "");
    }
    fWindow.show();
}

void GxMainInterface::on_oscilloscope_post_pre(int post_pre) {
    if (post_pre) {
        fWaveView.set_multiplicator(150.,250.);
    } else {
        fWaveView.set_multiplicator(20.,60.);
    }
}

int GxMainInterface::on_oscilloscope_activate(bool start) {
    if (!start) {
	engine.oscilloscope.clear_buffer();
	fWaveView.queue_draw();
    }
    return 0;
}

// ---- show main GUI thread and more
void GxMainInterface::run() {
    if (!jack.is_jack_exit()) {
	engine.clear_stateflag(gx_engine::ModuleSequencer::SF_INITIALIZING);
    }
    /* timeout in milliseconds */
    guivar.g_threads[0] = g_timeout_add(40, gx_threads::gx_update_all_gui, 0);
    // Note: meter display timeout is a global var in gx_gui namespace
    guivar.g_threads[1] = g_timeout_add(guivar.meter_display_timeout, gx_threads::gx_refresh_meter_level, 0);
    // watch tread for cabinet switch
    guivar.g_threads[3] = g_timeout_add(200, gx_threads::gx_check_cab_state, 0);

#ifndef IS_MACOSX
    // -------------- start helper thread for midi control ------------
    int semaphor = sem_init(&guivar.program_change_sem, 0, 0);
    if (semaphor != 0) {
        gx_system::gx_print_error(_("system startup"),
                   string(_("create semaphor failed (midi): preset switch disabled")));
    } else {
	GError* err = NULL;
        if (g_thread_create(gx_threads::gx_program_change_helper_thread,
                            NULL, FALSE, &err)  == NULL) {
            gx_system::gx_print_fatal(_("system startup"),
                       string(_("Thread create failed (midi): ")) + err->message);
            g_error_free(err);
            return;
        }
    }
#endif
    gtk_main();
}

} /* end of gx_gui namespace */
