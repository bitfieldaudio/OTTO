#ifndef ColorConverter_H_
#define ColorConverter_H_

#include <algorithm>
namespace ColorConverter
{
    using byte = unsigned char;
    
    static double clamp(double x, double a, double b)
    {
        return x < a ? a : (x > b ? b : x);
    }
    
    static double threeway_max(double a, double b, double c)
    {
        return std::max(a, std::max(b, c));
    }
    
    static double threeway_min(double a, double b, double c)
    {
        return std::min(a, std::min(b, c));
    }
    
    static double hue2rgb(double h, double m1, double m2)
    {
        if (h < 0.0) h += 1.0;
        if (h > 1.0) h -= 1.0;
        if (h < 1.0/6.0)
            return m1 + (m2 - m1) * h * 6.0;
        else if (h < 3.0/6.0)
            return m2;
        else if (h < 4.0/6.0)
            return m1 + (m2 - m1) * (2.0f/3.0f - h) * 6.0f;
        
        return m1;
    }

    /**
     * Converts an HSL color value to RGB. Conversion formula
     * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
     * Assumes h, s, and l are contained in the set [0, 1] and
     * returns r, g, and b in the set [0, 255].
     *
     * @param   double  h       The hue
     * @param   double  s       The saturation
     * @param   double  l       The lightness
     * @return  byte    rgb[]   The RGB representation
     */
    static void hslToRgb(double h, double s, double l, byte rgb[])
    {
        double m1, m2;
        double useless;
        h = std::modf(h,&useless);
        if (h < 0.0) h += 1.0;
        s = clamp(s,0.0,1.0);
        l = clamp(l,0.0,1.0);
        m2 = l <= 0.5f ? (l * (1 + s)) : (l + s - l * s);
        m1 = 2 * l - m2;
        
        double r = clamp(hue2rgb(h + 1.0/3.0, m1, m2), 0.0, 1.0);
        double g = clamp(hue2rgb(h, m1, m2), 0.0, 1.0);
        double b = clamp(hue2rgb(h - 1.0/3.0, m1, m2), 0.0, 1.0);
        
        rgb[0] = byte(r*255);
        rgb[1] = byte(g*255);
        rgb[2] = byte(b*255);
    }
    
    /**
     * Converts an RGB color value to HSL. Conversion formula
     * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
     * Assumes r, g, and b are contained in the set [0, 255] and
     * returns h, s, and l in the set [0, 1].
     *
     * @param   byte    r       The red color value
     * @param   byte    g       The green color value
     * @param   byte    b       The blue color value
     * @param   double  hsl[]   The HSL representation
     */
     static void rgbToHsl(byte r, byte g, byte b, double hsl[])
     {
         // TODO:
     }
     

    /**
     * Converts an RGB color value to HSV. Conversion formula
     * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
     * Assumes r, g, and b are contained in the set [0, 255] and
     * returns h, s, and v in the set [0, 1].
     *
     * @param   byte  r       The red color value
     * @param   byte  g       The green color value
     * @param   byte  b       The blue color value
     * @return  double hsv[]  The HSV representation
     */
    static void rgbToHsv(byte r, byte g, byte b, double hsv[])
    {
        // TODO:
    }
    
   /**
     * Converts an HSV color value to RGB. Conversion formula
     * adapted from http://en.wikipedia.org/wiki/HSV_color_space.
     * Assumes h, s, and v are contained in the set [0, 1] and
     * returns r, g, and b in the set [0, 255].
     *
     * @param   double  h       The hue
     * @param   double  s       The saturation
     * @param   double  v       The value
     * @return  byte    rgb[]   The RGB representation
     */
    static void hsvToRgb(double h, double s, double v, byte rgb[])
    {
        // TODO:
    }
};

#endif //ColorConverter_H_
