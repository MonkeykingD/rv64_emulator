/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <common.h>
#include <device/map.h>
#include <SDL2/SDL.h>

enum {
  reg_freq,
  reg_channels,
  reg_samples,
  reg_sbuf_size,
  reg_init,
  reg_count,
  nr_reg
};

static uint8_t *sbuf = NULL;
static uint32_t *audio_base = NULL;
 static int pos = 0;
static void MyAudioCallback(void *userData,Uint8 * stream,int len){
//回调函数往缓冲区中写入音频数据
  int count=audio_base[reg_count];
  int nread = len;
  if (count < len) nread = count;
  /* if pos reaches sbuf_size then turns to start */
  if(len + pos <= CONFIG_SB_SIZE)
  {
    memcpy(stream, sbuf + pos, nread);
    pos += nread;
  }
  else
  {
    int first = CONFIG_SB_SIZE - pos;
    memcpy(stream, sbuf + pos, first);

    int second = nread - first;
    memcpy(stream + first, sbuf, second);
    pos = second;
  }  
  audio_base[reg_count] -= nread;
  if (len > nread) {
    memset(stream + nread, 0, len - nread);
  }
}
static void init_SDLAudio() {
  SDL_AudioSpec want = {};
  want.freq = audio_base[reg_freq];
  want.channels = audio_base[reg_channels];
  want.samples = audio_base[reg_samples];
  want.callback = MyAudioCallback; /* you wrote this function elsewhere. */
  want.format= AUDIO_S16SYS;
  want.userdata = NULL; 
  int ret = SDL_InitSubSystem(SDL_INIT_AUDIO);
  if (ret == 0) {
    SDL_OpenAudio(&want, NULL);
    SDL_PauseAudio(0);
  }
}
static void audio_io_handler(uint32_t offset, int len, bool is_write) {
   if (audio_base[reg_init]&& is_write){
     audio_base[reg_init]=false;
     init_SDLAudio();
   }
}

void init_audio() {
  uint32_t space_size = sizeof(uint32_t) * nr_reg;
  audio_base = (uint32_t *)new_space(space_size);
  audio_base[reg_sbuf_size]=CONFIG_SB_SIZE;
#ifdef CONFIG_HAS_PORT_IO
  add_pio_map ("audio", CONFIG_AUDIO_CTL_PORT, audio_base, space_size, audio_io_handler);
#else
  add_mmio_map("audio", CONFIG_AUDIO_CTL_MMIO, audio_base, space_size, audio_io_handler);
#endif

  sbuf = (uint8_t *)new_space(CONFIG_SB_SIZE);
  add_mmio_map("audio-sbuf", CONFIG_SB_ADDR, sbuf, CONFIG_SB_SIZE, NULL);
}
