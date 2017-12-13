#pragma once
/* AUTHOR: Dakota Simonds
 * DATE: Nov 5, 2017
 */

/*
* Copyright 2017 Dakota Simonds
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is furnished
* to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
* THE SOFTWARE.
*/

#include <functional>
#include <iostream>
 
template<typename coord_ty>
struct coord 
{
  coord_ty x;
  coord_ty y;

  explicit coord(coord_ty a = 0, coord_ty b = 0) 
  : x(a), y(b)
  {  }
  
  coord( const coord & rhs )
  {
    x = rhs.x;
    y = rhs.y;
  }

  bool operator==(const coord &rhs)
  {  return x == rhs.x && y == rhs.y;  }

  void display( )
  { std::cout << "(" << x << "," << y << ")" << std::endl; }
};

 
 /* Directions North and South (y value)
 * are flipped since the origin of the array
 * is in the top right corner and the xy coordinate plane
 * starts in the bottom left corner. */

template<typename num_ty>
coord<num_ty> NorthEast( coord<num_ty> point )
{
  return coord<num_ty>(point.x+1, point.y-1);
}

template<typename num_ty>
coord<num_ty> NorthWest( coord<num_ty> point )
{
  return coord<num_ty>(point.x-1, point.y-1);
}

template<typename num_ty>
coord<num_ty> SouthWest( coord<num_ty> point )
{
  return coord<num_ty>(point.x-1, point.y+1);
}

template<typename num_ty>
coord<num_ty> SouthEast( coord<num_ty> point )
{
  return coord<num_ty>(point.x+1, point.y+1);
}

template<typename num_ty>
coord<num_ty> East( coord<num_ty> point )
{
  return coord<num_ty>(point.x+1, point.y);
}

template<typename num_ty>
coord<num_ty> West( coord<num_ty> point )
{
  return coord<num_ty>(point.x-1, point.y);
}

template<typename num_ty>
coord<num_ty> North( coord<num_ty> point )
{
  return coord<num_ty>(point.x, point.y-1);
}

template<typename num_ty>
coord<num_ty> South( coord<num_ty> point )
{
  return coord<num_ty>( point.x, point.y+1 );
}
 



template<typename num_ty>
class Compass
{
  typedef std::function< coord<num_ty>(coord<num_ty>) >
    func;
  

  func f;
public:
  coord<num_ty> cur;

  explicit Compass(func eq)
  : f(eq), cur(0,0) /* cur starts at origin */
  { }

  coord<num_ty>& reset_coord()
  {
    cur.x = 0;
    cur.y = 0;
    return cur;
  }
  
  void set_coord( const coord<int> &to)
  {
    cur = to;
  }

  void set_coord( int x, int y)
  {
    cur.x = x;
    cur.y = y;
  }
 
  coord<num_ty>& advance( void )
  {
    cur = f(cur);
    return cur;
  }
};

template<typename item_ty>
struct direction {
  const char *name;
  Compass<item_ty> *eq;
  direction(const char *n, Compass<item_ty> *e) 
  : name(n), eq(e) {}
};
