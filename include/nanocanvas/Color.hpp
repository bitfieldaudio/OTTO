#ifndef __NanoCanvas_Color_H__
#define __NanoCanvas_Color_H__

namespace NanoCanvas
{
    #include "ColorConverter.h"
    
    using  Byte = unsigned char;

    struct Color
    {
        union
        {
            struct
            {
                /// Red value
                Byte r;
                /// Green value
                Byte g;
                /// Blue value
                Byte b;
                /// Alpha value
                Byte a;
            };
            Byte mem[4];
        };


        Color(){ r = g = b = a = 0; }

        /**
         * @brief Construct a color with an unsigned integer value
         * @param color The color code value
         */
        Color(const unsigned int color)
        {
            set(color);
        }

        /**
          * @brief Construct color with it's components value in the range [0,255]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
         */
        Color(Byte _r, Byte _g, Byte _b, Byte _a = 255)
        {
            set(_r,_g,_b,_a);
        }
        
        /**
          * @brief Construct color with it's components value in the range [0,255]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
         */
        Color(int _r, int _g, int _b, int _a = 255)
        {
            set(_r,_g,_b,_a);
        }

        /**
          * @brief Construct color with it's components value in the range [0,255]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
         */
        Color(unsigned _r, unsigned _g, unsigned _b, unsigned _a = 255)
        {
            set(_r,_g,_b,_a);
        }

         /**
          * @brief Construct color with it's components value in the range [0,1]
          * @param _r The red component value
          * @param _g The green component value
          * @param _b The blue component value
          * @param _a The alpha component value
          */
        Color(float _r, float _g, float _b, float _a = 1.0f)
        {
            set(_r,_g,_b,_a);
        }

        /// Convert the color to unsigned int as the color code
        inline operator unsigned int() const { return code(); }

        inline Byte& operator[](int index){ return mem[index]; }
        inline const Byte operator[](int index) const { return mem[index]; }

        inline bool operator==(const Color& color){  return code() == color.code(); }
        inline bool operator<(const Color& color){ return code() < color.code(); }

        inline Color& operator = (const unsigned int color){ return set(color); }

        Color& operator += (const Color& color)
        {
            r = clamp<Byte>( r + color.r, 0, UCHAR_MAX);
            g = clamp<Byte>( g + color.g, 0, UCHAR_MAX);
            b = clamp<Byte>( b + color.b, 0, UCHAR_MAX);
            a = clamp<Byte>( a + color.a, 0, UCHAR_MAX);
            return *this;
        }

        Color& operator -= (const Color& color)
        {
            using std::max;
            r = clamp<Byte>( r - color.r, 0, UCHAR_MAX);
            g = clamp<Byte>( g - color.g, 0, UCHAR_MAX);
            b = clamp<Byte>( b - color.b, 0, UCHAR_MAX);
            a = clamp<Byte>( a - color.a, 0, UCHAR_MAX);
            return *this;
        }

        Color& operator *= (const Color& color)
        {
            r = clamp<Byte>( r + (color.r * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            g = clamp<Byte>( g + (color.g * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            b = clamp<Byte>( b + (color.b * color.a/UCHAR_MAX), 0, UCHAR_MAX);
            return *this;
        }

        Color operator + (const Color& color)
        {
            Color ret(*this);
            ret += color;
            return ret;
        }

        Color operator - (const Color& color)
        {
            Color ret(*this);
            ret -= color;
            return ret;
        }

        Color operator * (const Color& color)
        {
            Color ret(*this);
            ret *= color;
            return ret;
        }

        inline Color& set(unsigned int color)
        {
            r = (Byte)( color >> 24U );
            g = (Byte)((color >> 16U) & 0x00ffU);
            b = (Byte)((color >> 8U) & 0x0000ffU);
            a = (Byte)( color % 0x100U );
            return *this;
        }

        inline Color& set(float _r, float _g , float _b,float _a)
        {
            r =  clamp<Byte>( (Byte)(_r * UCHAR_MAX), 0, UCHAR_MAX);
            g =  clamp<Byte>( (Byte)(_g * UCHAR_MAX), 0, UCHAR_MAX);
            b =  clamp<Byte>( (Byte)(_b * UCHAR_MAX), 0, UCHAR_MAX);
            a =  clamp<Byte>( (Byte)(_a * UCHAR_MAX), 0, UCHAR_MAX);
            return *this;
        }

        inline Color& set(Byte _r, Byte _g, Byte _b, Byte _a)
        {
             r = _r; g = _g; b = _b; a = _a;
             return *this;
        }

        inline Color& set(unsigned _r, unsigned _g, unsigned _b, unsigned _a)
        {
            r = (Byte)_r; g = (Byte)_g; b = (Byte)_b; a = (Byte)_a;
            return *this;
        }

        inline Color& set(int _r, int _g, int _b, int _a)
        {
            r = (Byte)_r; g = (Byte)_g; b = (Byte)_b; a = (Byte)_a;
            return *this;
        }

        inline unsigned int code()const
        {
            unsigned int color = 0U;
            color |= ( r   << 24U );
            color |= ( g << 16U );
            color |= ( b << 8U );
            color |= a;
            return color;
        }

        inline float redf()const{ return   r/255.0f; }
        inline float greenf()const{ return g/255.0f; }
        inline float bluef()const{ return  b/255.0f; }
        inline float alphaf()const{ return a/255.0f; }
        
        static Color createWidthHSL(float _h , float _s,float _l,float _a = 1.0f)
        {
            Color color(0.0f,0.0f,0.0f,_a);
            ColorConverter::hslToRgb(_h,_s,_l,color.mem);
            return color;
        }
    };

    namespace Colors
    {
        static Color ZeroColor = 0U;
        static Color AliceBlue = 0xF0F8FFFF;
        static Color AntiqueWhile = 0xFAEBD7FF;
        static Color Aqua = 0x00FFFFFF;
        static Color Aquamarine = 0x7FFFd4FF;
        static Color Azure = 0xF0FFFFFF;
        static Color Beiqe = 0xF5F5DCFF;
        static Color Bisque = 0xFFE4C4FF;
        static Color Black = 0x000000FF;
        static Color BlanchedAlmond = 0xFFEBCDFF;
        static Color Blue = 0x0000FFFF;
        static Color BlueViolet = 0x8A2BE2FF;
        static Color Brown = 0xA52A2AFF;
        static Color BurlyWood = 0xDEB887FF;
        static Color CadetBlue = 0x5F9EA0FF;
        static Color Chartreuse = 0x7FFF00FF;
        static Color Chocolate = 0xD2691EFF;
        static Color Coral = 0xFF7F50FF;
        static Color CornflowerBlue= 0x6495EDFF;
        static Color Cornsilk = 0xFFF8DCFF;
        static Color Crimson = 0xDC143CFF;
        static Color Cyan = 0x00FFFFFF;
        static Color DarkBlue  = 0x00008BFF;
        static Color DarkCyan = 0x008B8BFF;
        static Color DarkGoldenRod = 0xB8860BFF;
        static Color DarkGray = 0xA9A9A9FF;
        static Color DarkGreen = 0x006400FF;
        static Color DarkKhaki = 0xBDB76BFF;
        static Color DarkMagenta = 0x8B008BFF;
        static Color DarkOliveGreen = 0x556B2FFF;
        static Color Darkorange = 0xFF8C00FF;
        static Color DarkOrchid = 0x9932CCFF;
        static Color DarkRed = 0x8B0000FF;
        static Color DarkSalmon = 0xE9967AFF;
        static Color DarkSeaGreen = 0x8FBC8FFF;
        static Color DarkSlateBlue = 0x483D8BFF;
        static Color DarkSlateGray = 0x2F4F4FFF;
        static Color DarkTurquoise = 0x00CED1FF;
        static Color DarkViolet = 0x9400D3FF;
        static Color DeepPink = 0xFF1493FF;
        static Color DeepSkyBlue = 0x00BFFFFF;
        static Color DimGray = 0x696969FF;
        static Color DodgerBlue = 0x1E90FFFF;
        static Color Feldspar = 0xD19275FF;
        static Color FireBrick = 0xB22222FF;
        static Color FloralWhite = 0xFFFAF0FF;
        static Color ForestGreen = 0x228B22FF;
        static Color Fuchsia = 0xFF00FFFF;
        static Color Gainsboro = 0xDCDCDCFF;
        static Color GhostWhite = 0xF8F8FFFF;
        static Color Gold = 0xFFD700FF;
        static Color GoldenRod = 0xDAA520FF;
        static Color Gray = 0x808080FF;
        static Color Green = 0x008000FF;
        static Color GreenYellow = 0xADFF2FFF;
        static Color HoneyDew = 0xF0FFF0FF;
        static Color HotPink = 0xFF69B4FF;
        static Color IndianRed = 0xCD5C5CFF;
        static Color Indigo = 0x4B0082FF;
        static Color Ivory = 0xFFFFF0FF;
        static Color Khaki = 0xF0E68CFF;
        static Color Lavender = 0xE6E6FAFF;
        static Color LavenderBlush = 0xFFF0F5FF;
        static Color LawnGreen = 0x7CFC00FF;
        static Color LemonChiffon = 0xFFFACDFF;
        static Color LightBlue = 0xADD8E6FF;
        static Color LightCoral = 0xF08080FF;
        static Color LightCyan = 0xE0FFFFFF;
        static Color LightGoldenRodYellow = 0xFAFAD2FF;
        static Color LightGrey = 0xD3D3D3FF;
        static Color LightGreen = 0x90EE90FF;
        static Color LightPink = 0xFFB6C1FF;
        static Color LightSalmon = 0xFFA07AFF;
        static Color LightSeaGreen = 0x20B2AAFF;
        static Color LightSkyBlue = 0x87CEFAFF;
        static Color LightSlateBlue = 0x8470FFFF;
        static Color LightSlateGray = 0x778899FF;
        static Color LightSteelBlue = 0xB0C4DEFF;
        static Color LightYellow = 0xFFFFE0FF;
        static Color Lime = 0x00FF00FF;
        static Color LimeGreen = 0x32CD32FF;
        static Color Linen = 0xFAF0E6FF;
        static Color Magenta = 0xFF00FFFF;
        static Color Maroon = 0x800000FF;
        static Color MediumAquaMarine = 0x66CDAAFF;
        static Color MediumBlue = 0x0000CDFF;
        static Color MediumOrchid = 0xBA55D3FF;
        static Color MediumPurple = 0x9370D8FF;
        static Color MediumSeaGreen = 0x3CB371FF;
        static Color MediumSlateBlue = 0x7B68EEFF;
        static Color MediumSpringGreen = 0x00FA9AFF;
        static Color MediumTurquoise = 0x48D1CCFF;
        static Color MediumVioletRed = 0xC71585FF;
        static Color MidnightBlue = 0x191970FF;
        static Color MintCream = 0xF5FFFAFF;
        static Color MistyRose = 0xFFE4E1FF;
        static Color Moccasin = 0xFFE4B5FF;
        static Color NavajoWhite = 0xFFDEADFF;
        static Color Navy = 0x000080FF;
        static Color OldLace = 0xFDF5E6FF;
        static Color Olive = 0x808000FF;
        static Color OliveDrab = 0x6B8E23FF;
        static Color Orange = 0xFFA500FF;
        static Color OrangeRed = 0xFFA500FF;
        static Color Orchid = 0xDA70D6FF;
        static Color PaleGoldenRod = 0xEEE8AAFF;
        static Color PaleGreen = 0x98FB98FF;
        static Color PaleTurquoise = 0xAFEEEEFF;
        static Color PaleVioletRed = 0xD87093FF;
        static Color PapayaWhip = 0xFFEFD5FF;
        static Color PeachPuff = 0xFFDAB9FF;
        static Color Peru = 0xCD853FFF;
        static Color Pink = 0xFFC0CBFF;
        static Color Plum = 0xDDA0DDFF;
        static Color PowderBlue = 0xB0E0E6FF;
        static Color Purple = 0x800080FF;
        static Color Red = 0xFF0000FF;
        static Color RosyBrown = 0xBC8F8FFF;
        static Color RoyalBlue = 0x4169E1FF;
        static Color SaddleBrown = 0x8B4513FF;
        static Color Salmon = 0xFA8072FF;
        static Color SandyBrown = 0xF4A460FF;
        static Color SeaGreen = 0x2E8B57FF;
        static Color SeaShell = 0xFFF5EEFF;
        static Color Sienna = 0xA0522DFF;
        static Color Silver = 0xC0C0C0FF;
        static Color SkyBlue = 0x87CEEBFF;
        static Color SlateBlue = 0x6A5ACDFF;
        static Color SlateGray = 0x708090FF;
        static Color Snow = 0xFFFAFAFF;
        static Color SpringGreen = 0x00FF7FFF;
        static Color SteelBlue = 0x4682B4FF;
        static Color Tan = 0xD2B48CFF;
        static Color Teal = 0x008080FF;
        static Color Thistle = 0xD8BFD8FF;
        static Color Tomato = 0xFF6347FF;
        static Color Turquoise = 0x40E0D0FF;
        static Color Violet = 0xEE82EEFF;
        static Color VioletRed = 0xD02090FF;
        static Color Wheat = 0xF5DEB3FF;
        static Color White = 0xFFFFFFFF;
        static Color WhiteSmoke = 0xF5F5F5FF;
        static Color Yellow = 0xFFFF00FF;
        static Color YellowGreen = 0x9ACD32FF;
    }

    /** @brief Get hex code string from color */
    string to_string(const Color& color);
}

#endif //__NanoCanvas_Color_H__
