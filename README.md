# yuvUtils

## Description

Yuv stream utils for stream player,adjust brightness,separate Y U V ...

## Environment

Player for Linux/Unix based on **SDL2**.   
Please install **SDL2**.

## Install

`mkdir build && cd build`  
`cmake .. && make`

## User Guide  
    yuvUtils usage: -i <input> -m <mode> -format <format> -w <width> -h <height> -o <output> -b <bright> -f <fps>
        -help               help.
        -i      <str>       Input file stream.
        -format <str>       Input format [ NV12 | I420 | Y ].
        -w      <int>       Input stream width.
        -h      <int>       Input stream height.
        -m      <str>       Function mode [ player | split | bright | gray ].
        -bright <float>     Output file bright, parameter (0~1) brgiht is increase, 1 no change , (1~) is lower.
        -f      <int>       Player YUV file fps. Default 20.
   
   
   
   
   
   