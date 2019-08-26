#ifndef PAINT_HPP
#define PAINT_HPP

namespace NanoCanvas
{
    /// The Paint can be used as gradiants and image patterns with Canvas::fillStyle
    /// @see Canvas::fillStyle 
    struct Paint
    {
        /// Paint type
        enum class Type
        {
            /// Liner gradiant
            Linear,
            /// Radial gradiant
            Radial,
            /// Box gradiant
            Box,
            /// Image pattern
            ImagePattern,
            /// Invalidate paint
            None
        } type = Type::None; /// The type of this paint
        float xx =0.0f, yy =0.0f , aa =0.0f, bb =0.0f, cc =0.0f,dd =0.0f;
        /// The nanovg image id of the image pattern
        int imageID  = 0;
        /// The start color of the gradiant
        Color sColor = Colors::ZeroColor;
        /// The end color of the gradiant
        Color eColor = Colors::ZeroColor;
    };
}

#endif // PAINT_HPP
