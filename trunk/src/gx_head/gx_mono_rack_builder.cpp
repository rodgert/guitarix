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
*    This file is a part ofthe gx_head interface builder
*    and build the mono effect rack,
*    it's a part of the class GxMainInterface
*
* ----------------------------------------------------------------------------
*/

#include "guitarix.h"        // NOLINT

#include <glibmm/i18n.h>     // NOLINT

// -------- the gx_head user interface build instruktions

namespace gx_gui {

void GxMainInterface::gx_build_mono_rack() {
    /** This is the fixed box on top of the mono rack, it include fixed effect modules
     * witch can't move (make no sense to move them arround). Right now it is the noisegate,
     * and the noisesharper, witch are fixed at the beginning of the process callback, and the
     * mono level out and the clipper, witch are fixed at the end of the mono callback.
     **/
    openHorizontalTableBox("");
    gx_engine::PluginList& pl = engine.pluginlist;
    fMonoRackContainer = fBox[fTop];
    {
        openVerticalBox("");
        {
            openPaintBox("");
            {
                openVerticalBox(" noise gate      ");
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "noise_gate.on_off");
                        openpaintampBox("noise gate");
                        {
                            create_wheel("noise_gate.threshold");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("noise shaper       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "shaper.on_off");

                        openpaintampBox("shaper");
                        {
                            create_wheel("shaper.sharper");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("mono level out       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.on_off");

                        openpaintampBox("level");
                        {
                            create_spin_value("amp.out_amp");
                            create_wheel("amp.out_amp");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();

                openVerticalBox(_("clip       "));
                {
                    openHorizontalBox("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.clip.on_off");

                        openpaintampBox("level");
                        {
                            create_wheel("amp.fuzz");
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        /** The moveable mono effects. Main box of a mono effect modul is the HorizontalOrderBox
         * witch present the move buttons. Inside the HorizontalOrderBox we need a DialogBox witch
         * register the effect to a counter and insert a menu entry as well a button to the toolbar
         **/
        // low high pass filter
	GtkWidget* box;
        box = openHorizontalOrderBox(_("l/h/filter"), pl.pos_var("low_highpass"));
        {
            openVerticalBox(_("l/h/filter"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "low_highpass.on_off");
                        create_selector("low_highpass.pp");
                    }
                    closeBox();

                    openDialogBox("ui.low high pass", "low_highpass.on_off", "RackBox_expose", box);
                    {
                        openHorizontalBox("");
                        {

                            openHorizontalBox("");
                            {
                                create_small_rackknob("low_high_pass.lhp.high_freq", _("high-pass "));
                                create_small_rackknob("low_high_pass.lhp.low_freq", _(" low-pass "));
                                create_switch_no_caption(sw_switchit, "low_high_pass.lhp.on_off");
                            }
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openHorizontalBox("");
                            {
                                create_small_rackknob("low_high_pass.lhc.low_freq", _("low-cut "));
                                create_small_rackknob("low_high_pass.lhc.high_freq", _("high-cut "));
                                create_switch_no_caption(sw_switchit, "low_high_pass.lhc.on_off");
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // EQ
        box = openHorizontalOrderBox(_("EQ"), pl.pos_var("eqs"));
        {
            openVerticalBox(_("EQ"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "eqs.on_off");
                        create_selector("eqs.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Scaleable EQ", "eqs.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalTableBox("");
                            {
                                create_simple_spin_value("eqs.freq31_25");
                                create_simple_spin_value("eqs.freq62_5");
                                create_simple_spin_value("eqs.freq125");
                                create_simple_spin_value("eqs.freq250");
                                create_simple_spin_value("eqs.freq500");
                                create_simple_spin_value("eqs.freq1k");
                                create_simple_spin_value("eqs.freq2k");
                                create_simple_spin_value("eqs.freq4k");
                                create_simple_spin_value("eqs.freq8k");
                                create_simple_spin_value("eqs.freq16k");
                            }
                            closeBox();
                            openHorizontalTableBox("");
                            {
                                create_eq_rackslider_no_caption("eqs.fs31_25");
                                create_eq_rackslider_no_caption("eqs.fs62_5");
                                create_eq_rackslider_no_caption("eqs.fs125");
                                create_eq_rackslider_no_caption("eqs.fs250");
                                create_eq_rackslider_no_caption("eqs.fs500");
                                create_eq_rackslider_no_caption("eqs.fs1k");
                                create_eq_rackslider_no_caption("eqs.fs2k");
                                create_eq_rackslider_no_caption("eqs.fs4k");
                                create_eq_rackslider_no_caption("eqs.fs8k");
                                create_eq_rackslider_no_caption("eqs.fs16k");
                            }
                            closeBox();
                            openHorizontalTableBox("");
                            {
                                create_small_rackknob("eqs.Qs31_25", "Q");
                                create_small_rackknob("eqs.Qs62_5", "Q");
                                create_small_rackknob("eqs.Qs125", "Q");
                                create_small_rackknob("eqs.Qs250", "Q");
                                create_small_rackknob("eqs.Qs500", "Q");
                                create_small_rackknob("eqs.Qs1k", "Q");
                                create_small_rackknob("eqs.Qs2k", "Q");
                                create_small_rackknob("eqs.Qs4k", "Q");
                                create_small_rackknob("eqs.Qs8k", "Q");
                                create_small_rackknob("eqs.Qs16k", "Q");
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- crybaby
        box = openHorizontalOrderBox(_("crybaby"), pl.pos_var("crybaby"));
        {
            openVerticalBox(_("crybaby"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "crybaby.on_off");
                        create_selector("crybaby.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Crybaby", "crybaby.on_off", "RackBox_expose", box);
                    {
                        openHorizontalBox("");
                        {
                            openSpaceBox("");
                            closeBox();
                            create_selector("crybaby.autowah");
                            openSpaceBox("");
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("crybaby.wah", _("  wah   "));
                                create_small_rackknob("crybaby.level", _("  level  "));
                                create_small_rackknob("crybaby.wet_dry", _("  dry/wet  "));
                            }
                            closeBox();
                            openSpaceBox("");
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- distortion
        box = openHorizontalOrderBox(_("distortion"), pl.pos_var("gx_distortion"));
        {
            openVerticalBox(_("distortion"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "gx_distortion.on_off");
                        create_selector("gx_distortion.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Multi Band Distortion", "gx_distortion.on_off", "RackBox_expose", box);
                    {
                        openHorizontalBox("");
                        {
                            openVerticalBox("");
                            {
                                openVerticalBox("");
                                {
                                    openFlipLabelBox(_("  drive "));
                                    {
                                        openHorizontalBox("");
                                        {
                                            create_small_rackknobr("gx_distortion.drive", _("  drive "));
                                            create_small_rackknobr("gx_distortion.low_drive", _(" low "));
                                            create_small_rackknobr("gx_distortion.middle_l_drive", _(" middle l. "));
                                            create_small_rackknobr("gx_distortion.middle_h_drive", _(" middle h. "));
                                            create_small_rackknobr("gx_distortion.high_drive", _(" high "));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                    openFlipLabelBox(_("  gain  "));
                                    {
                                        openHorizontalBox("");
                                        {
                                            create_small_rackknob("gx_distortion.gain", _("  gain  "));
                                            create_small_rackknob("gx_distortion.low_gain", _(" low "));
                                            create_small_rackknob("gx_distortion.middle_l_gain", _(" middle l. "));
                                            create_small_rackknob("gx_distortion.middle_h_gain", _(" middle h. "));
                                            create_small_rackknob("gx_distortion.high_gain", _(" high "));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();

                                openHorizontalBox("");
                                {
                                    create_small_rackknob("gx_distortion.wet_dry", _("dry/wet"));
                                    create_small_rackknob("gx_distortion.level", _("  level  "));
                                    openVerticalBox(_("frequency split Hz"));
                                    {
                                        openpaintampBox("");
                                        {
                                            openHorizontalBox("");
                                            {
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_low_freq", _("split low freq"));
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_middle_freq", _("split m. freq"));
                                                openSpaceBox("");
                                                closeBox();
                                                create_wheel("gx_distortion.split_high_freq", _("split high freq"));
                                                openSpaceBox("");
                                                closeBox();
                                            }
                                            closeBox();
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();
                            }
                            closeBox();

                            openVerticalBox(_("resonator"));
                            {
                                create_small_rackknob("gx_distortion.trigger", _("trigger "));
                                create_small_rackknob("gx_distortion.vibrato", _(" vibrato "));
                                create_switch_no_caption(sw_switchit, "gx_distortion.resonator.on_off");
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- IR
        box = openHorizontalOrderBox(_("IR"), pl.pos_var("IR"));
        {
            openVerticalBox(_("IR"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "IR.on_off");
                        create_selector("IR.pp");
                    }
                    closeBox();

                    openDialogBox("ui.ImpulseResponse", "IR.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox1("");
                        {
                            openHorizontalBox("");
                            {
                                openSpaceBox("");
                                closeBox();
                                create_selector("IR.auto_freq");
                                openSpaceBox("");
                                closeBox();

                                openHorizontalTableBox("");
                                {
                                    create_small_rackknob("IR.freq", _(" freq "));
                                    create_small_rackknob("IR.peak", _(" peak "));
                                    create_small_rackknob("IR.bandwidth", _(" bandwidth "));
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- the compressor
        box = openHorizontalOrderBox(_("Compr."), pl.pos_var("compressor"));
        {
            openVerticalBox(_("Compr."));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "compressor.on_off");
                        create_selector("compressor.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Compressor", "compressor.on_off", "RackBox_expose", box);
                    {
                        openHorizontalTableBox("");
                        {
                            create_small_rackknob("compressor.knee", _("knee"));
                            create_small_rackknobr("compressor.ratio", _("ratio"));
                            create_small_rackknob("compressor.threshold", _("threshold"));


                            create_small_rackknob("compressor.attack", _("attack"));
                            create_small_rackknob("compressor.release", _("release"));
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // -----overdrive
        box = openHorizontalOrderBox(_("overdrive"), pl.pos_var("overdrive"));
        {
            openVerticalBox(_("overdrive"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "overdrive.on_off");
                        create_selector("overdrive.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Overdrive", "overdrive.on_off", "RackBox_expose", box);
                    {
                        openHorizontalTableBox("");
                        {
                            openSpaceBox("");
                            closeBox();
                            create_small_rackknobr("overdrive.drive", _("  drive "));
                            create_small_rackknob("overdrive.wet_dry", _("dry/wet"));
                            openSpaceBox("");
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- echo
        box = openHorizontalOrderBox(_("echo"), pl.pos_var("echo"));
        {
            openVerticalBox(_("echo"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "echo.on_off");
                        create_selector("echo.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Echo", "echo.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("echo.time", _("  time  "));

                                create_small_rackknob("echo.percent", _("    %    "));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // -----delay
        box = openHorizontalOrderBox(_("delay"), pl.pos_var("delay"));
        {
            openVerticalBox(_("delay"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "delay.on_off");
                        create_selector("delay.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Delay", "delay.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalTableBox("");
                            {
                                create_small_rackknobr("delay.delay", _(" delay "));

                                create_small_rackknob("delay.gain", _("  gain "));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
        // ----- freeverb
        box = openHorizontalOrderBox(_("freeverb"), pl.pos_var("freeverb"));
        {
            openVerticalBox(_("freeverb"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "freeverb.on_off");
                        create_selector("freeverb.pp");
                    }
                    closeBox();
                    openDialogBox("ui.Freeverb", "freeverb.on_off", "RackBox_expose", box);
                    {
                        openFrameBox("");
                        closeBox();
                        openFrameBox("");
                        closeBox();
                        openHorizontalTableBox("");
                        {
                            create_small_rackknobr("freeverb.RoomSize", _("RoomSize"));
                            create_small_rackknob("freeverb.damp", _("damp"));
                            create_small_rackknob("freeverb.wet_dry", _("dry/wet"));
                        }
                        closeBox();
                        openFrameBox("");
                        closeBox();
                        openFrameBox("");
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        // -----osc
        box = openHorizontalOrderBox(_("oscilloscope"), pl.pos_var("oscilloscope"));
        {
            openVerticalBox(_("osc"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "oscilloscope.on_off");
                        create_selector("oscilloscope.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Oscilloscope", "oscilloscope.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openFrameBox("");
                            closeBox();
                            openHorizontalBox("");
                            {
                                openFrameBox("");
                                closeBox();
                                addLiveWaveDisplay(" ");
                                openFrameBox("");
                                closeBox();
                            }
                            closeBox();
                            openFrameBox("");
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("biquad"), pl.pos_var("biquad"));
        {
            openVerticalBox(_("biquad"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "biquad.on_off");
                        create_selector("biquad.pp");
                    }
                    closeBox();

                    openDialogBox("ui.BiQuad Filter", "biquad.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("biquad.Freq", _("Freq"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("tremolo"), pl.pos_var("tremolo"));
        {
            openVerticalBox(_("tremolo"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "tremolo.on_off");
                        create_selector("tremolo.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Tremolo", "tremolo.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                openSpaceBox("");
                                closeBox();
                                create_selector("tremolo.SINE");
                                openSpaceBox("");
                                closeBox();
                                openSpaceBox("");
                                closeBox();
                                openHorizontalTableBox("");
                                {
                                    create_small_rackknobr("tremolo.freq", _("Freq"));
                                    openSpaceBox("");
                                    closeBox();
                                    create_small_rackknobr("tremolo.depth", _("Depth"));
                                    openSpaceBox("");
                                    closeBox();
                                    create_small_rackknob("tremolo.wet_dry", _("dry/wet"));
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("phaser"), pl.pos_var("phaser"));
        {
            openVerticalBox(_("phaser"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "phaser_mono.on_off");
                        create_selector("phaser_mono.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Phaser Mono", "phaser_mono.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("phaser_mono.level", _("level"));
                                create_small_rackknob("phaser_mono.Speed", _("speed"));
                                create_small_rackknob("phaser_mono.wet_dry", _("dry/wet"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("chorus"), pl.pos_var("chorus"));
        {
            openVerticalBox(_("chorus"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "chorus_mono.on_off");
                        create_selector("chorus_mono.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Chorus Mono", "chorus_mono.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("chorus_mono.level", _("level"));
                                create_small_rackknob("chorus_mono.freq", _("speed"));
                                create_small_rackknob("chorus_mono.wet_dry", _("dry/wet"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("flanger"), pl.pos_var("flanger_mono"));
        {
            openVerticalBox(_("flanger"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "flanger_mono.on_off");
                        create_selector("flanger_mono.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Flanger Mono", "flanger_mono.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("flanger_mono.level", _("level"));
                                create_small_rackknob("flanger_mono.freq", _("speed"));
                                create_small_rackknob("flanger_mono.wet_dry", _("dry/wet"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("feedback"), pl.pos_var("feedback"));
        {
            openVerticalBox(_("feedback"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "feedback.on_off");
                        create_selector("feedback.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Feedback", "feedback.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_small_rackknobr("feedback.feedback",  _("feedback"));
                                create_small_rackknob("feedback.wet_dry",  _("dry/wet"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("tonestack"), pl.pos_var("amp.tonestack"));
        {
            openVerticalBox(_("tonestack"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "amp.tonestack.on_off");
                        create_selector("amp.tonestack.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Tonestack", "amp.tonestack.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_selector("amp.tonestack.select");

                                create_small_rackknob("amp.tonestack.Bass", _("bass"));

                                create_small_rackknob("amp.tonestack.Middle", _("middle"));

                                create_small_rackknob("amp.tonestack.Treble", _("treble"));
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        box = openHorizontalOrderBox(_("cabinet"), pl.pos_var("cab"));
        {
            openVerticalBox(_("cabinet"));
            {
                openHorizontalBox("");
                {
                    openPaintBox1("");
                    {
                        create_switch_no_caption(sw_switchit, "cab.on_off");
                        create_selector("cab.pp");
                    }
                    closeBox();

                    openDialogBox("ui.Cabinet", "cab.on_off", "RackBox_expose", box);
                    {
                        openVerticalBox("");
                        {
                            openHorizontalBox("");
                            {
                                create_selector("cab.select");
                                create_small_rackknob("cab.bass", "bass");
                                create_small_rackknob("cab.treble", "treble");
                                create_small_rackknobr("cab.Level", "level");
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();

        openVerticalMidiBox(_("  MIDI out  "));
        {
            openHorizontalBox("");
            {
                openVerticalBox(_("  MIDI out  "));
                {
                    create_switch_no_caption(sw_switchit, "midi_out.on_off");
                    openFrameBox("");
                    closeBox();
                    openHorizontalBox("");
                    {
                        openFrameBox("");
                        closeBox();
                        openPaintBox2("gree_box");
                        {
                            create_switch_no_caption(sw_led, "midi_out.midistat");
                        }
                        closeBox();
                        openFrameBox("");
                        closeBox();
                    }
                    closeBox();
                    openFrameBox("");
                    closeBox();
                }
                closeBox();
                // ----- create the midi settings dialog
                openVerticalBox("");
                {
                    openTabBox("");
                    {
                        openVerticalBox(_("channel1"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_1.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_1.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_1.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_1.channel", _("channel"));
                                            addNumEntry("midi_out.channel_1.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_1.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_1.sensity", _("sensity"));
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        openHorizontalBox(" ");
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openFrameBox("");
                                            closeBox();
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat1");
                                            }
                                            closeBox();
                                            openFrameBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openHorizontalBox(" ");
                                        {
                                            addMToggleButton("midi_out.channel_1.auto_pitch", _("auto_pitch"));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();

                        openVerticalBox(_("channel2"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_2.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_2.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_2.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_2.channel", _("channel"));
                                            addNumEntry("midi_out.channel_2.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_2.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_2.sensity", _("sensity"));
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        create_switch_no_caption(sw_switchit, "midi_out.channel_2.on_off");
                                        openFrameBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openFrameBox("");
                                            closeBox();
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat2");
                                            }
                                            closeBox();
                                            openFrameBox("");
                                            closeBox();
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();

                                        openHorizontalBox(" ");
                                        {
                                            addMToggleButton("midi_out.channel_2.auto_pitch", _("auto_pitch"));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();

                        openVerticalBox(_("channel3"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {
                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("midi_out.channel_3.velocity", _("velocity"));
                                        openVerticalBox("");
                                        {
                                            openPaintBox2("dark_box");
                                            {
                                                create_small_rackknob("midi_out.channel_3.volume", _("volume"));
                                            }
                                            closeBox();
                                            addCheckButton("midi_out.channel_3.autogain", _("autogain"));
                                        }
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            addNumEntry("midi_out.channel_3.channel", _("channel"));
                                            addNumEntry("midi_out.channel_3.program", _("program"));
                                        }
                                        closeBox();
                                        create_small_rackknob("midi_out.channel_3.oktave", _("oktave"));
                                        create_small_rackknob("midi_out.channel_3.sensity", _("sensity"));
                                    }
                                    closeBox();
                                    openHorizontalBox("");
                                    {
                                        create_switch_no_caption(sw_switchit, "midi_out.channel_3.on_off");
                                        openFrameBox("");
                                        closeBox();
                                        openVerticalBox("");
                                        {
                                            openFrameBox("");
                                            closeBox();
                                            openPaintBox2("darker_box");
                                            {
                                                create_switch_no_caption(sw_led, "midi_out.midistat3");
                                            }
                                            closeBox();
                                            openFrameBox("");
                                            closeBox();
                                        }
                                        closeBox();

                                        openFrameBox("");
                                        closeBox();
                                        openHorizontalBox(" ");
                                        {
                                            addMToggleButton("midi_out.channel_3.auto_pitch", _("auto_pitch"));
                                        }
                                        closeBox();
                                    }
                                    closeBox();
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();

                        openVerticalBox(_("beat_detector"));
                        {
                            openpaintampBox("MIDI OUT");
                            {
                                openVerticalBox("");
                                {

                                    openHorizontalBox("");
                                    {
                                        create_small_rackknob("beat_detector.stepper", _("stepper"));
                                        create_small_rackknob("beat_detector.note_off", _("note_off"));
                                        create_small_rackknob("beat_detector.atack_gain", _("atack_gain"));
                                        create_small_rackknob("beat_detector.beat_gain", _("beat_gain"));
                                    }
                                    closeBox();
                                    addStatusDisplay("", engine.midiaudiobuffer.get_midistat_pointer());
                                    openHorizontalBox("");
                                    {
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat1");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat2");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                        openPaintBox2("darker_box");
                                        {
                                            create_switch_no_caption(sw_led, "midi_out.midistat3");
                                        }
                                        closeBox();
                                        openFrameBox("");
                                        closeBox();
                                    }
                                    closeBox();

                                    openVerticalBox(_("Midi gain"));
                                    {
                                        create_wheel("beat_detector.midi_gain");
                                    }
                                    closeBox();
                                }
                                closeBox();
                            }
                            closeBox();
                        }
                        closeBox();
                    }
                    closeBox();
                }
                closeBox();
            }
            closeBox();
        }
        closeBox();
    }
    closeBox();
}  // close mono rack
} // end namespace gx_gui

