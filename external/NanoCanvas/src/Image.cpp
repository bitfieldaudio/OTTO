#include "NanoCanvas.h"
#include "nanovg.h"

namespace NanoCanvas
{
    Image::Image(Canvas& canvas,const string& filePath, int imageFlags)
    {
        m_canvas = &canvas;
        auto vg = canvas.nvgContext();
        if(vg && filePath.length() )
            imageID = nvgCreateImage(vg,filePath.c_str(),imageFlags);
    }
    Image::Image(Canvas& canvas,const Memery& memory, int imageFlags)
    {
        m_canvas = &canvas;
        auto vg = canvas.nvgContext();
        if(vg && memory.valid() )
        {
            imageID = nvgCreateImageMem(vg,imageFlags,
                                            (unsigned char*)(memory.data),
                                            memory.size);
        }
    }
    
    Image::Image(Canvas& canvas,int w,int h,const Memery& memory,int imageFlags)
    {
        m_canvas = &canvas;
        auto vg = canvas.nvgContext();
        if(vg && memory.valid() )
        {
            imageID = nvgCreateImageRGBA(vg,w,h,imageFlags,
                                            (unsigned char*)(memory.data));
        }
    }
    
    Image::~Image()
    {
        if(m_canvas)
        {
            auto vg = m_canvas->nvgContext();
            if(vg)
                nvgDeleteImage(vg,imageID);
        }
    }
    
    void Image::update(const Memery& memory)
    {
        if(m_canvas)
        {
            auto vg = m_canvas->nvgContext();
            if(vg)
                nvgUpdateImage(vg,imageID,(const unsigned char*)(memory.data));
        }
    }
    
    void Image::size(int& width,int& height)
    {
        if(m_canvas)
        {
            auto vg = m_canvas->nvgContext();
            if(vg)
                nvgImageSize(vg,imageID,&width,&height);
        }
    }
}


