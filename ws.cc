/* AUTHOR: Dakota Simonds
 * DATE: Oct 14, 2017
 */

#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include "data_horse.hpp"


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
class ActionEq : public Equation
{
  typedef std::function< coord<num_ty>(coord<num_ty>) >
    func;
  

  func f;
public:
  coord<num_ty> cur;

  explicit ActionEq(func eq)
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
  ActionEq<item_ty> *eq;
  direction(const char *n, ActionEq<item_ty> *e) 
  : name(n), eq(e) {}
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

/* it's not pretty but it's prettier */
template<typename item_ty>
inline
void add_dr( std::vector< direction<item_ty> > &dr_vec,
        /* name of the cardinal direction. East, West, etc. */
        const char *dr_name,
        /* A direction function defined above */
        std::function< coord<item_ty>(coord<item_ty>) > dr_fun) 
{
    dr_vec.push_back( /* push_back a direction struct */
      direction<item_ty>( /* direction struct is composed 
                           * of a name and a function object pointer */
        dr_name, new ActionEq<item_ty>( dr_fun ) ));
}


template<typename grid_ty, const int SIZE>
class grid
{
  grid_ty the_grid[SIZE][SIZE] = {};
  std::vector<std::string> word_list;
  std::vector< direction<int> > dr;
public:
  explicit grid( std::vector<std::string> & wl )
  : word_list(wl), dr()
  {
    /* add each direction. An inline function was used here
     * to try and clean up the boiler plate. */  
    try{
    add_dr<int>(dr, "South", South<int> );
    add_dr<int>(dr, "North", North<int>);
    add_dr<int>(dr, "East", East<int>);
    add_dr<int>(dr, "West", West<int>);
    add_dr<int>(dr, "NorthWest", NorthWest<int>);
    add_dr<int>(dr, "NorthEast", NorthEast<int>);
    add_dr<int>(dr, "SouthEast", SouthEast<int>);
    add_dr<int>(dr, "SouthWest", SouthWest<int>);
    } catch(...){} /* prevent memory leak in case of an exception */
  }

  ~grid()
  {
    for( auto itr = dr.begin(); itr != dr.end(); itr++)
      delete itr->eq;
  }

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

  bool in_cell( grid_ty & item, const coord<int> &loc )
  {
    /* are we within bounds ? */
    if(   loc.y < 0     || loc.x < 0 
       || loc.y >= SIZE || loc.x >= SIZE )
      return false; 
    return the_grid[ loc.y ][ loc.x ] == item;
  }

  bool word_in_direction(std::string &word, ActionEq<int> &drct )
  {
    static const unsigned WORD_MIN = 4;
    size_t len = word.length();
    if(len < WORD_MIN) return false;
    for( size_t i = 0; i < len; i++){
      if( in_cell(word[i], drct.cur) ){
        drct.advance();
      } else {
        return false;
      } 
    }
    return true;
  }

  int solve()
  {
    int count = 0;
    
    for(size_t row = 0; row < SIZE; row++)
      for(size_t col = 0; col < SIZE; col++){
        for(auto w_itr = word_list.begin(); w_itr != word_list.end(); w_itr++){
          for(auto itr = dr.begin(); itr != dr.end(); itr++){
            /* The direction equations are relative to the pos in the matrix */
            itr->eq->set_coord( static_cast<int>(col), static_cast<int>(row) );
  
            if( word_in_direction(*w_itr, *(itr->eq) ) )
            {
              count++;
              std::cout << "found " << *w_itr  
                << " at (" << col+1 << "," << row+1 << ")"
                << " in direction " << itr->name << std::endl;
            } 
          }
        }
      }
    return count;
  }
};




int main(int argc, char *argv[])
{
  std::string wordlist_name;
  std::string grid_name;
  
  /* refactor this */
  if( argc >= 2 )
    wordlist_name = argv[1];
  if( argc >= 3 ) 
    grid_name = argv[2];
   
  std::cout << "wordsearch";
  if(argc > 1)
    std::cout << " - " << wordlist_name << " " << grid_name;
  std::cout<< std::endl;

  FileData<std::string> word_list(wordlist_name);

  for(auto itr = word_list.begin(); itr != word_list.end(); itr++)
    to_lower(*itr);
 
  if(wordlist_name == "" || word_list.fail()){
    std::cout << "no wordlist found " << wordlist_name << std::endl 
              << "Exiting" << std::endl;
    return 1;
  }
  

  grid<char, 15> tron(word_list);
  if( grid_name == "" || !tron.load(grid_name) ){
    std::cout << "No grid file found " << grid_name << std::endl 
              << "Exiting" << std::endl;  
    return 1;
  }
  
  tron.show();
  std::cout << tron.solve() << " words found" << std::endl;
  return 0;
}
