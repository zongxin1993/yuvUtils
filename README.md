# yuvUtils

## Description

Yuv stream utils for stream player.  
  * Player I420 、NV12 and Y pixel format file.
  * Split I420 and NV12 pixel format file to Y U V.
  * Change the bright.
  * Change to the gray file.

## Environment

YuvUtils for Linux/Unix based on **SDL2**.   
Please install **SDL2**.

## Install

`mkdir build && cd build`  
`cmake .. && make`

## User Guide  
    yuvUtils usage: -i <input> -m <mode> -format <format> -w <width> -h <height> -b <bright> -f <fps>
        -help               help.
        -i      <str>       Input file stream.
        -format <str>       Input format [ NV12 | I420 | Y ].
        -w      <int>       Input stream width.
        -h      <int>       Input stream height.
        -m      <str>       Function mode [ player | split | bright | gray ].
        -bright <float>     Change Output file bright when 'bright' mode, parameter (0~1) brgiht is increase, 1 no change , (1~) is lower.
        -f      <int>       Player YUV file fps. Default 20.
   
    
   * Note  
   Support auto size function in the file name:  
      * Format:  
         * **{width}x{height}**
         * **SQCIF** , **sqcif**
         * **QCIF** , **qcif**
         * **CIF** , **cif**
         * **4CIF** , **4cif**
         
      * Like:
         * _'Cactus_ProRes_1280x720_50f.p010.yuv'_
         * _'akiyo_cif.yuv'_
   
   
   
   