import("music.lib");
import("guitarix.lib");

resonator = (+ <: (delay(4096, d-1) + delay(4096, d))/2.0)~*(1.0-a)
with {
d = vslider("vibrato", 0.5, 0, 1, 0.01);
a = vslider("trigger", 0.12, 0, 1, 0.01);
};

fuzzy = vslider("fuzzy", 0.5, 0, 1, 0.01);
tube1 = nonlin1 : resonator * fuzzy * 0.5 : g_clip(0.7);

process = add_dc <: _ + tube1 : sym_clip(0.7);
