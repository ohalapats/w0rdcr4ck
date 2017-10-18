/* AUTHOR: Dakota Simonds
 * DATE: Oct 14, 2017
 */

#include <iostream>
#include <functional>
#include <fstream>

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


class Equation {
public:
  Equation()
  {  }
  virtual ~Equation() = 0;
};

inline Equation::~Equation(){}


template<typename num_ty>
class ActionEquation : public Equation
{
  typedef std::function< coord<num_ty>(coord<num_ty>) >
    sigma;
public:
  explicit ActionEquation()
  {}
};


/* the equation y = 1(x) + 0
 * produces a 45 degree angle
 */
template<typename num_ty>
coord<num_ty> _45( coord<num_ty> point )
{
  return coord<num_ty>(point.x+1, point.y+1);
}


template<typename grid_ty, const int SIZE>
class grid
{
  grid_ty the_grid[SIZE][SIZE] = {};
public:
  grid(){}
  ~grid(){}

  bool load(std::string source){
    std::fstream fsource(source);
    if(fsource.fail()) 
      return false;

    char cur = '\0';
    size_t col = 0;
    size_t row = 0;

    while(row < SIZE)
    {
      while(!fsource.eof() && col < SIZE)
      {
        fsource.get(cur);
        /* avoid saving the newline char and start the next row */
        if(cur == '\n') break; 
        the_grid[row][col] = cur;
        col++;
      }
      col = 0; cur = '\0';
      row++;
    }
     
    return true;
  }

  void show()
  {
    for(int row = 0; row < SIZE; row++){
      for(int col = 0; col < SIZE; col++){
        std::cout << the_grid[row][col] << " ";
      }
      std::cout << std::endl;
    }
  }

};




int main(void)
{
  std::cout << "wordsearch" << std::endl;

  grid<char, 15> tron;
  tron.load("grid.txt");
  tron.show();
  

 
  return 0;
}
