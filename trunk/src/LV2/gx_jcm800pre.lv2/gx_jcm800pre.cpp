/*
 * Copyright (C) 2014 Guitarix project
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

////////////////////////////// LOCAL INCLUDES //////////////////////////


#include "gx_jcm800pre.h"        // define struct PortIndex
#include "gx_pluginlv2.h"   // define struct PluginLV2
#include "jcm800pre.cc"
#include "gx_common.h"      // faust support and denormal protection (SSE)
#include "tonestack_jcm800.cc"    // dsp class generated by faust -> dsp2cc
#include "gx_presence.cc"


////////////////////////////// PLUG-IN CLASS ///////////////////////////

namespace jcm800pre {

class Gx_jcm800pre_
{
private:
  // pointer to buffer
  float*                       output;
  float*                       input;
  uint32_t                     s_rate;
  int32_t                      prio;
  uint32_t                     bufsize;
  // pointer to dsp class
  PluginLV2*                   jcm800pre;
  PluginLV2*                   tonestack_jcm800;
  gx_resample::BufferResampler resamp1;
  GxPresence                   presence;
  LV2_URID_Map*                map;
  // private functions
  inline void run_dsp_(uint32_t n_samples);
  inline void connect_(uint32_t port,void* data);
  inline void init_dsp_(uint32_t rate, uint32_t bufsize_);
  inline void connect_all__ports(uint32_t port, void* data);
  inline void activate_f();
  inline void clean_up();
  inline void deactivate_f();

public:
  // LV2 Descriptor
  static const LV2_Descriptor descriptor;
  // static wrapper to private functions
  static void deactivate(LV2_Handle instance);
  static void cleanup(LV2_Handle instance);
  static void run(LV2_Handle instance, uint32_t n_samples);
  static void activate(LV2_Handle instance);
  static void connect_port(LV2_Handle instance, uint32_t port, void* data);
  static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                                double rate, const char* bundle_path,
                                const LV2_Feature* const* features);
  Gx_jcm800pre_();
  ~Gx_jcm800pre_();
};

// constructor
Gx_jcm800pre_::Gx_jcm800pre_() :
  output(NULL),
  input(NULL),
  s_rate(0),
  prio(0),
  bufsize(0),
  jcm800pre(jcm800pre::plugin()),
  tonestack_jcm800(tonestack_jcm800::plugin()),
  presence(GxPresence(resamp1)) {};
  
// destructor
Gx_jcm800pre_::~Gx_jcm800pre_()
{
  // just to be sure the plug have given free the allocated mem
  // it didn't hurd if the mem is already given free by clean_up()
  if (jcm800pre->activate_plugin !=0)
    jcm800pre->activate_plugin(false, jcm800pre);
  // delete DSP class
  jcm800pre->delete_instance(jcm800pre);
  tonestack_jcm800->delete_instance(tonestack_jcm800);
  presence.stop_process();
  presence.cleanup();
};

///////////////////////// PRIVATE CLASS  FUNCTIONS /////////////////////

void Gx_jcm800pre_::init_dsp_(uint32_t rate, uint32_t bufsize_)
{
  AVOIDDENORMALS(); // init the SSE denormal protection
  jcm800pre->set_samplerate(rate, jcm800pre); // init the DSP class
  tonestack_jcm800->set_samplerate(rate, tonestack_jcm800); // init the DSP class


#ifdef _POSIX_PRIORITY_SCHEDULING
  int priomax = sched_get_priority_max(SCHED_FIFO);
  if ((priomax/2) > 0) prio = priomax/2;
#endif
  bufsize = bufsize_;
  presence.set_samplerate(rate);
  presence.set_buffersize(bufsize);
  presence.configure(presence_ir_desc.ir_count, presence_ir_desc.ir_data, presence_ir_desc.ir_sr);
  while (!presence.checkstate());
  if(!presence.start(prio, SCHED_FIFO))
	printf("presence convolver disabled\n");
  
}

// connect the Ports used by the plug-in class
void Gx_jcm800pre_::connect_(uint32_t port,void* data)
{
  switch ((PortIndex)port)
    {
    case EFFECTS_OUTPUT:
      output = static_cast<float*>(data);
      break;
    case EFFECTS_INPUT:
      input = static_cast<float*>(data);
      break;
    default:
      break;
    }
}

void Gx_jcm800pre_::activate_f()
{
  // allocate the internal DSP mem
  if (jcm800pre->activate_plugin !=0)
    jcm800pre->activate_plugin(true, jcm800pre);
  if (tonestack_jcm800->activate_plugin !=0)
    tonestack_jcm800->activate_plugin(true, tonestack_jcm800);
}

void Gx_jcm800pre_::clean_up()
{
  // delete the internal DSP mem
  if (jcm800pre->activate_plugin !=0)
    jcm800pre->activate_plugin(false, jcm800pre);
  if (tonestack_jcm800->activate_plugin !=0)
    tonestack_jcm800->activate_plugin(false, tonestack_jcm800);
}

void Gx_jcm800pre_::deactivate_f()
{
  // delete the internal DSP mem
  if (jcm800pre->activate_plugin !=0)
    jcm800pre->activate_plugin(false, jcm800pre);
  if (tonestack_jcm800->activate_plugin !=0)
    tonestack_jcm800->activate_plugin(false, tonestack_jcm800);
}

void Gx_jcm800pre_::run_dsp_(uint32_t n_samples)
{
  if(n_samples == bufsize) {
    jcm800pre->mono_audio(static_cast<int>(n_samples), input, output, jcm800pre);
  } else {
    memcpy(output, input, n_samples * sizeof(float));
  }
  tonestack_jcm800->mono_audio(static_cast<int>(n_samples), output, output, tonestack_jcm800);
  // run presence convolver
  presence.run_static(n_samples, &presence, output);
}

void Gx_jcm800pre_::connect_all__ports(uint32_t port, void* data)
{
  // connect the Ports used by the plug-in class
  connect_(port,data); 
  // connect the Ports used by the DSP class
  jcm800pre->connect_ports(port,  data, jcm800pre);
  tonestack_jcm800->connect_ports(port,  data, tonestack_jcm800);
  presence.connect_ports(port,  data, &presence);
}

////////////////////// STATIC CLASS  FUNCTIONS  ////////////////////////

LV2_Handle 
Gx_jcm800pre_::instantiate(const LV2_Descriptor* descriptor,
                            double rate, const char* bundle_path,
                            const LV2_Feature* const* features)
{
  // init the plug-in class
  Gx_jcm800pre_ *self = new Gx_jcm800pre_();
  if (!self)
    {
      return NULL;
    }

  const LV2_Options_Option* options  = NULL;
  uint32_t bufsize = 0;
  //printf(" %s\n",descriptor->URI);

  for (int32_t i = 0; features[i]; ++i)
    {
      if (!strcmp(features[i]->URI, LV2_URID__map))
        {
          self->map = (LV2_URID_Map*)features[i]->data;
        }
      else if (!strcmp(features[i]->URI, LV2_OPTIONS__options))
        {
          options = (const LV2_Options_Option*)features[i]->data;
        }
    }
  if (!self->map)
    {
      fprintf(stderr, "Missing feature uri:map.\n");
    }
  else if (!options)
    {
      fprintf(stderr, "Missing feature options.\n");
    }
  else
    {
      LV2_URID bufsz_max = self->map->map(self->map->handle, LV2_BUF_SIZE__maxBlockLength);
      LV2_URID bufsz_    = self->map->map(self->map->handle,"http://lv2plug.in/ns/ext/buf-size#nominalBlockLength");
      LV2_URID atom_Int = self->map->map(self->map->handle, LV2_ATOM__Int);

      for (const LV2_Options_Option* o = options; o->key; ++o)
        {
          if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_ &&
              o->type == atom_Int)
            {
              bufsize = *(const int32_t*)o->value;
              break;
            }
          if (o->context == LV2_OPTIONS_INSTANCE &&
              o->key == bufsz_max &&
              o->type == atom_Int)
            {
              bufsize = *(const int32_t*)o->value;
            }
        }

      if (bufsize == 0)
        {
          fprintf(stderr, "No maximum buffer size given.\n");
          delete self;
          return NULL;
         }
      printf("using block size: %d\n", bufsize);
    }
    
  self->init_dsp_((uint32_t)rate, (uint32_t)bufsize);

  return (LV2_Handle)self;
}

void Gx_jcm800pre_::connect_port(LV2_Handle instance, 
                                   uint32_t port, void* data)
{
  // connect all ports
  static_cast<Gx_jcm800pre_*>(instance)->connect_all__ports(port, data);
}

void Gx_jcm800pre_::activate(LV2_Handle instance)
{
  // allocate needed mem
  static_cast<Gx_jcm800pre_*>(instance)->activate_f();
}

void Gx_jcm800pre_::run(LV2_Handle instance, uint32_t n_samples)
{
  // run dsp
  static_cast<Gx_jcm800pre_*>(instance)->run_dsp_(n_samples);
}

void Gx_jcm800pre_::deactivate(LV2_Handle instance)
{
  // free allocated mem
  static_cast<Gx_jcm800pre_*>(instance)->deactivate_f();
}

void Gx_jcm800pre_::cleanup(LV2_Handle instance)
{
  // well, clean up after us
  Gx_jcm800pre_* self = static_cast<Gx_jcm800pre_*>(instance);
  self->clean_up();
  delete self;
}

const LV2_Descriptor Gx_jcm800pre_::descriptor =
{
  GXPLUGIN_URI "#_jcm800pre_",
  Gx_jcm800pre_::instantiate,
  Gx_jcm800pre_::connect_port,
  Gx_jcm800pre_::activate,
  Gx_jcm800pre_::run,
  Gx_jcm800pre_::deactivate,
  Gx_jcm800pre_::cleanup,
  NULL
};


} // end namespace jcm800pre

////////////////////////// LV2 SYMBOL EXPORT ///////////////////////////

extern "C"
LV2_SYMBOL_EXPORT
const LV2_Descriptor*
lv2_descriptor(uint32_t index)
{
  switch (index)
    {
    case 0:
      return &jcm800pre::Gx_jcm800pre_::descriptor;
    default:
      return NULL;
    }
}

///////////////////////////// FIN //////////////////////////////////////
