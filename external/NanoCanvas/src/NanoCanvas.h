#ifndef __NANOCANVAS_H__
#define __NANOCANVAS_H__

#include <climits>
#include <algorithm>
#include <string>
#include <cmath>


namespace NanoCanvas
{
    using std::string;
    static string nullstr;
    
    /// The data structure for memery blocks
    struct Memery
    {
        /// The data of the memery block
        void * data = nullptr;
        
        /// Size of the memery block in bytes
        unsigned long size = 0UL;
        
        /// Check is the data is not NULL and size is not 0
        bool valid()const{ return ( data && size ); }
        
        /**
         * @brief Invalidate the memery object
         * @attention This method does NOT free the memery,you have to do it yourself!
         */
        void invalidate(){ data = nullptr ;size = 0UL; }
    };
    
    /// The π definition
    static constexpr long double PI = 3.14159265358979323846264338327L;
    
    /**
     * @brief Get a number in range @b [a,b]
     * @return The value between @e a and @e b
     * @li if @e a <= @e x <= @e b returns @e x
     * @li if @e x < @e a returns @e a
     * @li if @e x > @e b returns @e b
     */
    template<typename T>
    inline T clamp(T x, T a, T b)
    {
        return x < a ? a : (x > b ? b : x);
    }
    
    
    //Convert degree to radians
    template<typename T>
    T degree2Radians(const T _degree)
    {
        return _degree * ( PI / (T)180);
    }
    
    //Conver radians to degree
    template<typename T>
    T radians2Degree(const T _radians)
    {
        return _radians * ( ( (T)180 )/ PI) ;
    }
}

#include "Color.hpp"
#include "Text.h"
#include "Image.h"
#include "Paint.hpp"
#include "Canvas.h"

#endif //__NANOCANVAS_H__
