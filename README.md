# yuvUtils

## Description

Yuv stream utils for stream player,adjust brightness,separate Y U V ...

## Environment

Player for Linux/Unix based on SDL2.If you use the player function, please install SDL2.

## Install

`mkdir build && cd build`  
`cmake .. && make`

## Example  
   * YUV player example.   
   Supported formats: **_yuv420p_** **_yuv422p_** **_yuv444p_** **_y_** **_nv12_**  
   `yuvUtils -i <inputfile> -m player -format <format> -width <int> -height <int>`  
   * Separate YUV file.  
   Supported formats: **_yuv420p_** **_yuv422p_** **_yuv444p_**  
   `yuvUtils -i <inputfile> -m split -format <format> -width <int> -height <int>`  
   * Adjust brightness.  
   Supported formats: **_yuv420p_** **_yuv422p_** **_yuv444p_**  
   Parameter **_bright_** > 0 , when 0< **_bright_** < 1 outfile is brighten.  
   `yuvUtils -i <inputfile> -m bright -format <format> -width <int> -height <int> -bright <float>`  
   
   
   
   
   
   