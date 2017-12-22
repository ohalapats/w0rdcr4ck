#pragma once
/* AUTHOR: Dakota Simonds
 * DATE: Nov 5th, 2017
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

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include <cctype>
#include "direction.hpp"
#include "args.hpp"
#include "prefix/prefix.hpp"

using std::vector;
using std::string;
using std::fstream;

void to_lower_word( string &subject )
{
  for(size_t i = 0; i < subject.length(); i++)
    subject[i] = tolower( subject[i] );
}


/* it's not pretty but it's prettier */
template<typename item_ty>
inline
void add_dr( vector< direction<item_ty> > &dr_vec,
        /* name of the cardinal direction. East, West, etc. */
        const char *dr_name,
        /* A direction function */
        std::function< coord<item_ty>(coord<item_ty>) > dr_fun) 
{
    dr_vec.push_back( /* push_back a direction struct */
      direction<item_ty>( /* direction struct is composed 
                           * of a name and a function object pointer */
        dr_name, new Compass<item_ty>( dr_fun ) ));
}


template<typename grid_ty>
class grid
{
  vector<string> the_grid;
  vector<string> word_list;
  vector< direction<int> > dr;
  Prefix ptree;
  Args &args;
  int X_SIZE;
  int Y_SIZE;
public:
  explicit grid( Args &a )
  :  word_list(), dr(), ptree(), args(a), X_SIZE(0), Y_SIZE(0)
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

      load_wordlist(args.wordlist_name);
      load_grid(args.grid_name);
      Y_SIZE = the_grid.size();
      X_SIZE = the_grid[0].length(); /*TODO: this could fail. */
    } catch(...){} /* prevent memory leak in case of an exception */
  }

  ~grid()
  {
    for( auto itr = dr.begin(); itr != dr.end(); itr++)
      delete itr->walk;
  }
  void set_wordlist( vector<string> &wl)
  {
    word_list = wl;
  }

  bool load_wordlist(string source)
  {
    fstream fsource(source);
    if(fsource.fail()) 
      return false;
    string line;
    
    while(!fsource.eof()){
      fsource >> line;
      to_lower_word(line);
      ptree.insert(line);
    }
    
    fsource.close();
    return true;
  }

  bool load_grid(string source){
    fstream fsource(source);
    if(fsource.fail()) 
      return false;
 
    char cur = '\0';
    size_t col = 0;
    static size_t MAX_LINE_LEN = 4096;
    
    while(!fsource.eof() )
    {
      the_grid.push_back(string() );
      while(cur != '\n' && col <= MAX_LINE_LEN){
        fsource.read(&cur, 1);
        if(cur == '\n') break;
        the_grid.back().push_back( tolower(cur) );
        col++;
      }
      cur = '\0';
      col = 0;
    }
    fsource.close();
    return true;
  }

  void show()
  {
    for(int row = 0; row < Y_SIZE; row++){
      for(int col = 0; col < X_SIZE; col++){
        std::cout << the_grid[row][col] << " ";
      }
      std::cout << std::endl;
    }
  }
 

  bool in_cell( grid_ty & item, const coord<int> &loc )
  {
    return get_cell(loc) == item;
  }
  
  char get_cell(const coord<int> &loc)
  {
    /* are we within bounds ? */
    if(   loc.y < 0     || loc.x < 0 
       || loc.y >= Y_SIZE || loc.x >= X_SIZE )
      return '\0'; 
    return the_grid[ loc.y ][ loc.x ];
  }

  /* given a word from a dictionary and uses the compass to compare
   * the chars one by one with the in_cell function */
  bool word_in_direction( string &word, Compass<int> &drct )
  {
    word = "";
    auto mon = ptree.monkey();
    unsigned c = 0;
    while( mon.have_char( get_cell(drct.cur) ) )
    {
      word = word + get_cell(drct.cur);
      mon.advance_lvl();
      drct.advance();
      c++;
    }
    if(c > 4) return true; /* this is a hack hack. A hackers' hack. 
                            * It's so hacky that it hacked itself.
                            * Ideally we would be searching for an end-of-word
                            * character but this strategey works for now.
                            * TODO: use end-of-word char instead of 
                            * counting chars found */ return false;
  }

  int solve()
  {
    int count = 0;
    string word; 
    for(size_t row = 0; row < Y_SIZE; row++){
      for(size_t col = 0; col < X_SIZE; col++){
        for(auto itr = dr.begin(); itr != dr.end(); itr++){
            Compass<int> * compass = itr->walk; 
            /* The compasses are relative to the pos in the matrix */
            compass->set_coord(col, row);

            if( word_in_direction( word, *compass ) ) 
            {
              count++;
              std::cout << "found " << word 
                << " at (" << col+1 << "," << row+1 << ")"
                << " in direction " << itr->name << std::endl;
            }
          }
      }
    }
    return count;
  }

  Prefix& get_prefix()
  { return ptree; }
};
