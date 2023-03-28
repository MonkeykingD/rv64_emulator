#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

static int Width = 0;
static int Height = 0;
void __am_gpu_init() {
    Width = inw(VGACTL_ADDR+2);
    Height = inw(VGACTL_ADDR);
//  int i;
  //int w =io_read(AM_GPU_CONFIG).width ;  // TODO: get the correct width
 // int h =io_read(AM_GPU_CONFIG).height ;  // TODO: get the correct height
//  int w=inw(VGACTL_ADDR+2);
//  int h=inw(VGACTL_ADDR);
//  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
//  for (i = 0; i < w * h; i ++) fb[i] = i;
//  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = Width, .height = Height,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {

  int x = ctl->x, y = ctl->y, w = ctl->w, h = ctl->h;

  if (!ctl->sync && (w == 0 || h == 0)) return;
  uint32_t *pixels = ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  uint32_t screen_w = inw(VGACTL_ADDR+2);
  for(int ty=y;ty<y+h;ty++)
  {
    for(int tx=x;tx<x+w;tx++){
      fb[tx+ty*screen_w] =pixels[(tx-x)+(ty-y)*w];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }     
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
