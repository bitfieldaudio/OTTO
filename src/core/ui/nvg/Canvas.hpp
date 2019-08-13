#pragma once

#include <functional>

#include "Color.hpp"
#include "Image.hpp"
#include "Paint.hpp"
#include "Text.hpp"

struct NVGcontext;

namespace otto::nvg {

  using namespace TextAlign;

  struct Canvas; // FWDCL

  /// Anything that can be drawn on screen.
  ///
  /// Holds a pointer to its parent
  struct Drawable {
    Drawable() = default;

    virtual ~Drawable() = default;

    /// Draw this widget to the context.
    ///
    /// Called from the parent's draw method.
    /// \param ctx the canvas to draw on.
    virtual void draw(Canvas& ctx) = 0;
  };

  enum struct Winding {
    /// Counter clock wise
    CCW = 1,
    /// Clock wise
    CW = 2,
  };

  /// Line cap style
  enum struct LineCap {
    ///  A flat edge is added to each end of the line
    BUTT,
    /// A rounded end cap is added to each end of the line
    ROUND,
    /// A square end cap is added to each end of the line
    SQUARE

  };

  /// Line join style
  enum struct LineJoin {
    /// Creates a beveled corner
    BEVEL,
    /// Creates a rounded corner
    ROUND,
    /// Creates a sharp corner
    MITER
  };

  enum struct CompositeOperation {
    SOURCE_OVER,
    SOURCE_IN,
    SOURCE_OUT,
    ATOP,
    DESTINATION_OVER,
    DESTINATION_IN,
    DESTINATION_OUT,
    DESTINATION_ATOP,
    LIGHTER,
    COPY,
    XOR,
  };

  /**
   * @class Canvas
   * @author Geequlim
   * @file Canvas.h
   * @brief The HTML5's Canvas liked render API writing in C++11 based on NanoVG
   */
  struct Canvas {

    /**
     * @brief Construct a canvas with NanoVG Context
     * @param ctx The NanoVG Context used for this canvas
     * @param width The width of the canvas, in pixels
     * @param height The height of the canvas, in pixels
     * @param scaleRatio The device pixel ration
     */
    Canvas(NVGcontext* ctx, float width, float height, float scaleRatio = 1.0f);
    Canvas(NVGcontext* ctx, Size size, float scaleRatio = 1.0f);

    /// Canvas is non-copyable
    Canvas(const Canvas&) = delete;
    /// Canvas is non-copyable
    auto operator=(const Canvas&) = delete;

    /// Canvas is movable
    Canvas(Canvas&&) = default;
    /// Canvas is movable
    Canvas& operator=(Canvas&&) = default;

    /// Get the canvas size
    Size size() const noexcept;

    /* ------------------- Basic Path ----------------------*/

    /**
     * @brief Moves the path to the specified point in the canvas, without creating a line
     *
     * The moveTo() method moves the path to the specified point in the canvas, without creating a line.
     *
     * @param x The x-coordinate of where to move the path to
     * @param y The y-coordinate of where to move the path to
     * @return The Canvas to operate with
     */
    Canvas& moveTo(float x, float y);
    Canvas& moveTo(Point p);

    /**
     * @brief Adds a new point and creates a line from that point to the last specified point in the canvas
     *
     * The lineTo() method adds a new point and creates a line from that point to the last specified point in the canvas
     * (this method does not draw the line).
     *
     * @param x The x-coordinate of where to create the line to
     * @param y The y-coordinate of where to create the line to
     * @return The Canvas to operate with
     */
    Canvas& lineTo(float x, float y);
    Canvas& lineTo(Point p);

    /**
     * @brief Creates an arc/curve between two tangents on the canvas.
     * @param x1 The x-coordinate of the first tangent
     * @param y1 The y-coordinate of the first tangent
     * @param x2 The x-coordinate of the second tangent
     * @param y2 The y-coordinate of the second tangent
     * @param r  The radius of the arc
     * @return The Canvas to operate with
     */
    Canvas& arcTo(float x1, float y1, float x2, float y2, float r);
    Canvas& arcTo(Point p1, Point p2, float r);

    /**
     * @brief Creates a quadratic Bézier curve
     *
     * The quadraticCurveTo() method adds a point to the current path by using the specified control points that
     * represent a quadratic Bézier curve.@n A quadratic Bézier curve requires two points. The first point is a control
     * point that is used in the quadratic Bézier calculation and the second point is the ending point for the curve.
     * The starting point for the curve is the last point in the current path. If a path does not exist, use the
     * beginPath() and moveTo() methods to define a starting point.
     *
     * @param cpx The x-coordinate of the Bézier control point
     * @param cpy The y-coordinate of the Bézier control point
     * @param x The x-coordinate of the ending point
     * @param y The y-coordinate of the ending point
     * @return The Canvas to operate with
     */
    Canvas& quadraticCurveTo(float cpx, float cpy, float x, float y);
    Canvas& quadraticCurveTo(Point control, Point end);

    /**
     * @brief Creates a cubic Bézier curve
     *
     * The bezierCurveTo() method adds a point to the current path by using the specified control points that represent
     * a cubic Bézier curve.
     * @n
     * A cubic bezier curve requires three points.
     * The first two points are control points that are used in the cubic Bézier calculation and the last point is the
     * ending point for the curve. The starting point for the curve is the last point in the current path. If a path
     * does not exist, use the beginPath() and moveTo() methods to define a starting point.
     *
     * @param cp1x The x-coordinate of the first Bézier control point
     * @param cp1y The y-coordinate of the first Bézier control point
     * @param cp2x The x-coordinate of the second Bézier control point
     * @param cp2y The y-coordinate of the second Bézier control point
     * @param x The x-coordinate of the ending point
     * @param y The y-coordinate of the ending point
     * @return The Canvas to operate with
     */
    Canvas& bezierCurveTo(float cp1x, float cp1y, float cp2x, float cp2y, float x, float y);
    Canvas& bezierCurveTo(Point cp1, Point cp2, Point end);

    /**
     * @brief Creates an arc/curve (used to create circles, or parts of circles)
     * The arc() method creates an arc/curve (used to create circles, or parts of circles).
     * @note Tip: To create a circle with arc(): Set start angle to 0 and end angle to 2*π.
     * @param x The x-coordinate of the center of the circle
     * @param y The y-coordinate of the center of the circle
     * @param r The radius of the circle
     * @param sAngle The starting angle, in radians (0 is at the 3 o'clock position of the arc's circle)
     * @param eAngle The ending angle, in radians
     * @param counterclockwise Optional. Specifies whether the drawing should be counterclockwise or clockwise. False is
     * default, and indicates clockwise, while true indicates counter-clockwise.
     * @return
     */
    Canvas& arc(float x, float y, float r, float sAngle, float eAngle, bool counterclockwise = false);
    Canvas& arc(Point cp, float r, float sAngle, float eAngle, bool counterclockwise = false);

    /**
     * @brief Close current path with a line segment
     * @return The canvas to operate with
     */
    Canvas& closePath();


    /* ------------------- Advance Path --------------------*/

    /**
     * @brief Creates a rectangle
     *
     * The rect() method creates a rectangle.
     *
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @param w The width of the rectangle, in pixels
     * @param h The height of the rectangle, in pixels
     * @return The canvas which the path be added to
     */
    Canvas& rect(float x, float y, float w, float h);
    Canvas& rect(Point p, Size s);

    Canvas& rect(Box b);

    Canvas& centeredSquare(Point p, float side_length);

    /**
     * @brief Creates a  rounded rectangle
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @param w The width of the rectangle, in pixels
     * @param h The height of the rectangle, in pixels
     * @param r The radius of the circle formed by 4 corners of the rounded rectangle
     * @return The canvas to create path
     */
    Canvas& roundedRect(float x, float y, float w, float h, float r);
    Canvas& roundedRect(Point p, Size s, float r);

    Canvas& roundedRect(Box b, float r);

    /**
     * @brief Creates a circle
     * @param cx The x-coordinate of center point for the circle
     * @param cy The y-coordinate of center point for the circle
     * @param r The radius of the circle
     * @return The canvas to create path
     */
    Canvas& circle(float cx, float cy, float r);
    Canvas& circle(Point p, float r);

    /**
     * @brief Creates an ellipse
     * @param cx The x-coordinate of center point for the ellipse
     * @param cy The x-coordinate of center point for the ellipse
     * @param rx The radius of the ellipse in horizentoal
     * @param ry The radius of the ellipse in vertical
     * @return The canvas to create path
     */
    Canvas& ellipse(float cx, float cy, float rx, float ry);
    Canvas& ellipse(Point p, float rx, float ry);

    /* ------------------- Draw Action ---------------------*/

    /**
     * @brief Fills the current drawing (path)
     *
     * The fill() method fills the current drawing (path). The default color is black.
     *
     * @note If the path is not closed, the fill() method will add a line from the last point to the startpoint of the
     * path to close the path (like closePath()), and then fill the path.
     * @return The canvas to fill
     */
    Canvas& fill();
    Canvas& fill(const Color& color);

    /**
     * @brief Actually draws the path you have defined
     *
     * The stroke() method actually draws the path you have defined with all those moveTo() and lineTo() methods. The
     * default color is black.
     *
     * @return The canvas to stroke
     */
    Canvas& stroke();
    Canvas& stroke(const Color& color);

    /**
     * @brief Draws a "filled" rectangle
     *
     * The fillRect() method draws a "filled" rectangle. The default color of the fill is black.
     *
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @param w The width of the rectangle, in pixels
     * @param h The height of the rectangle, in pixels
     * @return The canvas to draw
     */
    Canvas& fillRect(float x, float y, float w, float h);

    /**
     * @brief Draws a rectangle (no fill)
     *
     * The strokeRect() method draws a rectangle (no fill). The default color of the stroke is black.
     *
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @param w The width of the rectangle, in pixels
     * @param h The height of the rectangle, in pixels
     * @return The canvas to draw
     */
    Canvas& strokeRect(float x, float y, float w, float h);

    /**
     * @brief Clear the canvas with color
     * @param color The color to fill the hole canvas
     * @return The canvas to operate with
     */
    Canvas& clearColor(const Color& color);


    /**
     * @brief Draws "filled" text on the canvas
     * @param text Specifies the text that will be written on the canvas
     * @param x The x coordinate where to start painting the text (relative to the canvas)
     * @param y The y coordinate where to start painting the text (relative to the canvas)
     * @param rowWidth The max row width of the text box,NAN is not limited
     * @return The canvas to operate with
     */
    Canvas& fillText(const std::string& text, float x, float y, float rowWidth = NAN);
    Canvas& fillText(const std::string& text, Point p, float rowWidth = NAN);

    /**
     * @brief Draws an image onto the canvas
     *
     * The drawImage() method can also draw parts of an image, and/or increase/reduce the image size.
     *
     * @param image Specifies the image to use
     * @param x The x coordinate where to place the image on the canvas
     * @param y The y coordinate where to place the image on the canvas
     * @param width The width of the image to use (stretch or reduce the image),NAN as the default be the same as wdith
     * of the clipped area
     * @param height The height of the image to use (stretch or reduce the image),NAN as the default be the same as
     * wdith of the clipped area
     * @param sx The x coordinate where to start clipping,0 as the default
     * @param sy The y coordinate where to start clipping,0 as the default
     * @param swidth The wdith of the clipped image,NAN as defualt to clip to right side of the image
     * @param sheight The height of the clipped image,NAN as defualt to clip to bottom side of the image
     * @return The canvas to draw this image
     */
    Canvas& drawImage(Image& image,
                      float x,
                      float y,
                      float width = NAN,
                      float height = NAN,
                      float sx = 0,
                      float sy = 0,
                      float swidth = NAN,
                      float sheight = NAN);


    Canvas& draw(Drawable& d);

    Canvas& draw(Drawable&& d);

    Canvas& drawAt(Point p, Drawable&& d);

    Canvas& drawAt(Point p, Drawable& d);

    template<typename FuncRef>
    Canvas& group(FuncRef&& func);

    template<typename FuncRef>
    Canvas& callAt(Point p, FuncRef&& f);

    template<typename It>
    Canvas& plotBezier(It pointB, It pointE, float f = 0.5, float t = 1);

    /// Draw a curve between points using only horizontal and vertical lines and
    /// rounded corners
    ///
    /// This is the algorithm used by the samplers, and in general to display waveforms
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \param maxR The maximum radius for curves, in pixels. If negative, there
    ///             is no limit
    /// \requires `It` shall be an `InputIterator<Point>`
    template<typename Iter>
    Canvas& plotRounded(Iter first, Iter last, float max_radius);

    /// Plot a curve between points using straight lines
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \requires `It` shall be an `InputIterator<Point>`
    template<typename Iter>
    Canvas& plotLines(Iter first, Iter last);

    /// A scatterplot of points
    ///
    /// \param first An iterator to the first point
    /// \param last An iterator one past the last point
    /// \param r The radius of the points
    /// \param c The colour of the points
    /// \requires `It` shall be an `InputIterator<Point>`
    ///
    template<typename It>
    Canvas& plotPoints(It first, It last, float r, Color c);

    // Debuging

    Canvas& debugDot(Point p, Color c = 0xFFFF00);
    /*-------------------- Style Control -------------------*/

    /**
     * @brief Set the style of the end caps for a line
     *
     * @param cap The line cap style
     * @return The canvas to operate with
     */
    Canvas& lineCap(LineCap cap);

    /**
     * @brief Set the type of corner created, when two lines meet
     * @param join The line join style
     * @return The canvas to operate with
     */
    Canvas& lineJoin(LineJoin join);

    /**
     * @brief Set the current line width
     * @param width The current line width, in pixels
     * @return The canvas to operate with
     */
    Canvas& lineWidth(float width);

    /**
     * @brief Sets the maximum miter length
     *
     * The miter length is the distance between the inner corner and the outer corner where two lines meet.
     * @n
     * The miter length grows bigger as the angle of the corner gets smaller.
     *
     * @note The miterLimit property works only if the lineJoin attribute is "miter".
     * @param limit A positive number that specifies the maximum miter length. If the current miter length exceeds the
     * miterLimit, the corner will display as lineJoin "bevel"
     * @return The canvas to operate with
     */
    Canvas& miterLimit(float limit);

    /**
     * @brief Sets the current alpha or transparency value of the drawing.
     * @param alpha new alpha vlaue of canvas
     * @return The canvas to operate with
     */
    Canvas& globalAlpha(float alpha);


    /**
     * @brief Sets the color to fill the drawing
     * @param color The color to fill with
     * @return The canvas to operate with
     */
    Canvas& fillStyle(const Color& color);

    /**
     * @brief Set the gradient or pattern paint used to fill the drawing
     * @param paint The paint used to fill the drawing
     * @return The canvas to operate with
     */
    Canvas& fillStyle(const Paint& paint);

    /**
     * @brief  Set the color used for strokes.
     * @param color Stroke color
     * @return The canvas to operate with
     */
    Canvas& strokeStyle(const Color& color);

    /**
     * @brief Set the gradient or pattern paint used for strokes
     * @param paint The paint used to fill the drawing
     * @return The canvas to operate with
     */
    Canvas& strokeStyle(const Paint& paint);


    /**
     * @brief Set current font for text rendering
     * @note If the face of the font is invalid ,it doesn't work
     * @see NanoCanvas::Font
     * @param font The font to use
     * @return The canvas to operate with
     */
    Canvas& font(const Font& font);

    /**
     * @brief Set font size for current text style.
     * @param size The font size
     * @return The canvas to operate with
     */
    Canvas& font(float size);

    /**
     * @brief Set current font and size for text rendering
     * @note If the face of the font is invalid, it doesn't work
     * @see NanoCanvas::Font
     * @param font The font to use
     * @param size The font size
     * @return The canvas to operate with
     */
    Canvas& font(const Font& f, float size);

    /**
     * @brief Sets the text alignment of current text style
     * @param hAlign The horizontak alignment
     * @param vAlign The verical alignment
     * @see TextAlign::HorizontalAlign
     * @see TextAlign::VerticalAlign
     * @return The canvas to operate with
     */
    Canvas& textAlign(HorizontalAlign hAlign, VerticalAlign vAlign);

    /**
     * @brief Set styles for text rendering
     * @param textStyle The text style to use
     * @see NanoCanvas::TextStyle
     * @return The canvas to operate with
     */
    Canvas& fillStyle(const TextStyle& textStyle);

    /**
     * @brief Creates a linear gradient (to use on canvas content)
     * @param x0 The x-coordinate of the start point of the gradient
     * @param y0 The y-coordinate of the start point of the gradient
     * @param x1 The x-coordinate of the end point of the gradient
     * @param y1 The y-coordinate of the end point of the gradient
     * @param scolor The start color
     * @param outter The end color
     * @return The created gradient style object.
     */
    static Paint createLinearGradient(float x0, float y0, float x1, float y1, const Color& scolor, const Color& ecolor);

    /**
     * @brief Creates a radial/circular gradient (to use on canvas content)
     * @param cx The x-coordinate of the circle of the gradient
     * @param cy The y-coordinate of the circle of the gradient
     * @param r1 The radius of the inner circle
     * @param r2 The radius of the outter circle
     * @param icolor The color on inner circle
     * @param ocolor The color on outer circle
     * @return The created gradient style object.
     */
    static Paint createRadialGradient(float cx, float cy, float r1, float r2, const Color& icolor, const Color& ocolor);

    /**
     * @brief Creates and returns a box gradient.
     * @par Box gradient is a feathered rounded rectangle, it is useful for rendering drop shadows or highlights for
     * boxes.
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @param w The width of the rectangle, in pixels
     * @param h The height of the rectangle, in pixels
     * @param r The radius of the circle formed by 4 corners of the rounded rectangle
     * @param f How blurry the border of the rectangle is
     * @param icol The inner color of the gradient
     * @param ocol The outer color of the gradient
     * @return The created gradient style object.
     */
    static Paint createBoxGradient(float x, float y, float w, float h, float r, float f, Color icol, Color ocol);

    /**
     * @brief Creates and returns an image pattern paint.
     * @param image Specifies the image of the pattern to use
     * @param ox The x-coordinate of the upper-left corner of the image would be draw
     * @param oy The y-coordinate of the upper-left corner of the image would be draw
     * @param w The width of the pattern
     * @param h The height of the pattern
     * @param angle The rotation around the top-left corner in radians
     * @param alpha The transparent of the image pattern
     * @return The patter paint created
     */
    static Paint
    createPattern(const Image& image, float ox, float oy, float w, float h, float angle = 0.0f, float alpha = 1.0f);

    /**
     * @brief Check the width of the text, before writing it on the canvas
     * @param text The text to be measured
     * @param rowWidth The max row width of the text box,NAN is not limited
     * @return The width of the specified text
     */
    float measureText(const std::string& text, float rowWidth = NAN);

    /**
     * @brief Check the boundary of the text, before writing it on the canvas
     * @param text The text to be measured
     * @param x The x-coordinate of the text
     * @param y The y-coordinate of the text
     * @param bounds [in] The float array to store boundary values should be a pointer to float[4]
     * @param rowWidth The max row width of the text box,NAN is not limited
     * @return The width of the specified text
     */
    float measureText(const std::string& text, float x, float y, float* bounds, float rowWidth = NAN);
    Box measureText(const std::string& text, Point p, float rowWidth = NAN);

    Canvas& globalCompositeOperation(CompositeOperation op);

    /*--------------------- Transformations ----------------*/

    /**
     * @brief Scales the current drawing, bigger or smaller.
     * @note If you scale a drawing, all future drawings will also be scaled. The positioning will also be scaled.
     * If you scale(2,2); drawings will be positioned twice as far from the left and top of the canvas as you specify.
     * @param scalewidth Scales the width of the current drawing (1=100%, 0.5=50%, 2=200%, etc.)
     * @param scaleheight Scales the height of the current drawing (1=100%, 0.5=50%, 2=200%, etc.)
     * @return The canvas to scale with
     */
    Canvas& scale(float scalewidth, float scaleheight);

    /**
     * @brief Scales the current drawing, bigger or smaller.
     * @note If you scale a drawing, all future drawings will also be scaled. The positioning will also be scaled.
     * If you scale(2,2); drawings will be positioned twice as far from the left and top of the canvas as you specify.
     * @param s Scales the width and height of the current drawing (1=100%, 0.5=50%, 2=200%, etc.)
     * @param p the point to scale towards (the point that doesnt move)
     * @return The canvas to scale with
     */
    Canvas& scaleTowards(float s, Point p);

    /**
     * @brief Rotates the current drawing
     * @note: The rotation will only affect drawings made AFTER the rotation is done.
     * @par To calculate from degrees to radians: degrees*Math.PI/180.
     * @n Example: to rotate 5 degrees, specify the following: 5*Math.PI/180
     * @param angle The rotation angle, in radians.
     * @return The canvas to rotate with
     */
    Canvas& rotate(float angle);

    /**
     * @brief Rotates the current drawing
     * @note: The rotation will only affect drawings made AFTER the rotation is done.
     * @par To calculate from degrees to radians: degrees*Math.PI/180.
     * @n Example: to rotate 5 degrees, specify the following: 5*Math.PI/180
     * @param angle The rotation angle, in radians.
     * @param p The point to rotate around.
     * @return The canvas to rotate with
     */
    Canvas& rotateAround(float r, Point p);

    /**
     * @brief Remaps the (0,0) position on the canvas
     * @note When you call a method such as fillRect() after translate(), the value is added to the x- and y-coordinate
     * values.
     * @param x The value to add to horizontal (x) coordinates
     * @param y The value to add to vertical (y) coordinates
     * @return The canvas to translate with
     */
    Canvas& translate(float x, float y);
    Canvas& translate(Point p);

    /**
     * @brief Replaces the current transformation matrix for the drawing
     * @par Each object on the canvas has a current transformation matrix. @n
     * The transform() method replaces the current transformation matrix. It multiplies the current transformation
     * matrix with the matrix described by: @n
     *
     * @li a    c   e
     * @li b    d   f
     * @li 0    0   1
     *
     * @par In other words, the transform() method lets you scale, rotate, move, and skew the current context.
     * @note The transformation will only affect drawings made after the transform() method is called.
     * @note  The transform() method behaves relatively to other transformations made by rotate(), scale(), translate(),
     * or transform(). Example: If you already have set your drawing to scale by two, and the transform() method scales
     * your drawings by two, your drawings will now scale by four.
     * @par Tip: Check out the setTransform() method, which does not behave relatively to other transformations.
     *
     * @param a Scales the drawing horizontally
     * @param b Skew the the drawing horizontally
     * @param c Skew the the drawing vertically
     * @param d Scales the drawing vertically
     * @param e Moves the the drawing horizontally
     * @param f Moves the the drawing vertically
     * @return The canvas to transform with
     */
    Canvas& transform(float a, float b, float c, float d, float e, float f);

    /**
     * @brief Resets the current transform to the identity matrix. Then runs transform()
     * @param a Scales the drawing horizontally
     * @param b Skew the the drawing horizontally
     * @param c Skew the the drawing vertically
     * @param d Scales the drawing vertically
     * @param e Moves the the drawing horizontally
     * @param f Moves the the drawing vertically
     * @see Canvas::transform()
     * @see Canvas::restTransform()
     * @return The canvas to set transform with
     */
    Canvas& setTransform(float a, float b, float c, float d, float e, float f);

    /**
     * @brief Resets the current transform to the identity matrix.
     * @return The canvas to set transform with
     */
    Canvas& restTransform();

    /*--------------------- Canvas Control -----------------*/
    /**
     * @brief Begin drawing a new frame
     *
     * Calls to Canvas drawing API should be wrapped in beginFrame() & endFrame()
     * beginFrame() defines the size of the window to render to in relation currently
     * set viewport (i.e. glViewport on GL backends).
     *
     * @param windowWidth Width of your window
     * @param windowHeight Height of your window
     * @return The canvas to begin frame with
     */
    Canvas& beginFrame(int windowWidth, int windowHeight);

    /**
     * @brief Cancels drawing the current frame.
     * @return The canvas to cancle draw
     */
    Canvas& cancelFrame();

    /** @brief Ends drawing flushing remaining render state. */
    void endFrame();

    /**
     * @brief Begins a path, or resets the current path
     * @return The canvas to create path
     */
    Canvas& beginPath();

    /**
     * @brief Sets the current path winding
     * @param dir CVS_CW or CVS_CW
     * @return The canvas to operate with
     */
    Canvas& pathWinding(Winding dir);


    /**
     * @brief Clip of a rectangular region
     * @param x The x-coordinate of the upper-left corner of the clip region
     * @param y The y-coordinate of the upper-left corner of the clip region
     * @param w The width of the clip region, in pixels
     * @param h The width of the clip region, in pixels
     * @return The canvas to clip with
     */
    Canvas& clip(float x, float y, float w, float h);

    /**
     * @brief Reset clip state ,remove all clip region
     * @return The canvas to reset
     */
    Canvas& resetClip();



    /* --------------------- State NanoVG Handling -------------------
     *
     *
     * NanoVG contains state which represents how paths will be rendered.
     * The state contains transform, fill and stroke styles, text and font styles,and scissor clipping.
     *
     *-----------------------------------------------------------------*/

    /**
     * @brief Pushe and save the current render state into a state stack.
     * @note  A matching restore() must be used to restore the state.
     * @return The canvas to save state
     */
    Canvas& save();

    /**
     * @brief Pop and restore current render state.
     * @return The canvas to restore state
     */
    Canvas& restore();

    /**
     * @brief Resets current render state to default values. Does not affect the render state stack.
     * @return The canvas to reset state
     */
    Canvas& reset();


    /*------------------ Canvas propoties ---------------------*/

    /**
     * @brief Check is the context avaliable
     * @return Is the context avaliable
     */
    inline bool valid() const
    {
      return m_nvgCtx;
    }

    /**
     * @brief Set canvas size
     * @param width  The width of the canvas, in pixels
     * @param height The height of the canvas, in pixels
     * @return The canvas to resize
     */
    inline Canvas& setSize(float width, float height)
    {
      m_width = width;
      m_height = height;
      return *this;
    }

    /**
     * @brief Set position of the canvas
     * @param x The x-coordinate of the upper-left corner of the rectangle
     * @param y The y-coordinate of the upper-left corner of the rectangle
     * @return The canvas to change position
     */
    inline Canvas& setPosition(float x, float y)
    {
      m_xPos = x;
      m_yPos = y;
      return *this;
    }

    /**
     * @brief Set scale ration of the canvas
     *
     * Device pixel ration allows to control the rendering on Hi-DPI devices.
     * For example, GLFW returns two dimension for an opened window: window size and
     * frame buffer size. In that case you would set windowWidth/Height to the window size
     * devicePixelRatio to: frameBufferWidth / windowWidth.
     *
     * @param ratio The device pixel ration
     * @return The canvas to set scale ration with
     */
    inline Canvas& setScaleRatio(float ratio)
    {
      m_scaleRatio = ratio;
      return *this;
    }

    /**
     * @brief Convert coordinates in canvas to coordinates in windows
     * @param x [inout] The x-coordinate to convert
     * @param y [inout] The x-coordinate to convert
     */
    inline void local2Global(float& x, float& y)
    {
      x = m_xPos + x;
      y = m_yPos + y;
    }

    /**
     * @brief Convert coordinates in windows to coordinates in canvas
     * @param x [inout] The x-coordinate to convert
     * @param y [inout] The x-coordinate to convert
     */
    inline void global2Local(float& x, float& y)
    {
      x = x - m_xPos;
      y = y - m_yPos;
    }


    /**
     * @brief Get the NanoVG context for advanced contol
     * @return The NanoVG context of this canvas
     */
    NVGcontext* nvgContext()
    {
      return m_nvgCtx;
    }

  protected:
    /// The NanoVG context
    NVGcontext* m_nvgCtx;
    /// The width of the canvas
    float m_width;
    /// The height of the canvas
    float m_height;
    /// Buffer / window size ratio
    float m_scaleRatio;
    /// The x-coordinate of the canvas in window
    float m_xPos;
    /// The y-coordinate of the canvas in window
    float m_yPos;
  };

  // Template definitions

  template<typename FuncRef>
  Canvas& Canvas::group(FuncRef&& func)
  {
    save();
    func();
    restore();
    return *this;
  }

  template<typename FuncRef>
  Canvas& Canvas::callAt(Point p, FuncRef&& f)
  {
    save();
    translate(p);
    f();
    restore();
    return *this;
  }

  template<typename It>
  Canvas& Canvas::plotBezier(It pointB, It pointE, float f, float t)
  {
    moveTo(*pointB);

    float m = 0;
    Point d1;

    Point prev = *pointB;
    Point cur = prev;
    Point next = prev;
    for (auto it = pointB; it != pointE; ++it) {
      prev = cur;
      cur = next;
      next = *it;
      if (cur == prev) continue;
      m = (next.y - prev.y) / (next.x - prev.x);
      Point d2 = {(next.x - cur.x) * -f, 0};
      d2.y = d2.x * m * t;
      bezierCurveTo(prev - d1, cur + d2, cur);
      d1 = d2;
    }
    return *this;
  }

  template<typename Iter>
  Canvas& Canvas::plotRounded(Iter first, Iter last, float max_radius)
  {
    if (first == last) return *this;

    moveTo(*first);
    auto prev = first;
    first++;
    for (auto iter = first; iter != last; iter++, prev++) {
      auto p1 = *prev;
      auto p2 = *iter;
      float dx = std::abs(p2.x - p1.x);
      float dy = std::abs(p2.y - p1.y);
      float r = std::min({dx / 2.f, dy / 2.f, max_radius});
      Point md = (p1 + p2) / 2.0;
      Point cp1 = {md.x, p1.y};
      Point cp2 = md;
      Point cp3 = {md.x, p2.y};

      arcTo(cp1, cp2, r);
      arcTo(cp3, p2, r);
    }
    lineTo(*(--last));
    return *this;
  }

  template<typename Iter>
  Canvas& Canvas::plotLines(Iter first, Iter last)
  {
    if (first == last) return *this;

    moveTo(*first++);
    std::for_each(first, last, [&](Point p) { lineTo(p); });
    return *this;
  }

  template<typename It>
  Canvas& Canvas::plotPoints(It first, It last, float r, Color c)
  {
    std::for_each(first, last, [this, c, r](Point p) { beginPath().circle(p, r).fill(c); });
    return *this;
  }

} // namespace otto::nvg
