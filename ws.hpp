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
using std::function;


void to_lower_word( string &subject )
{
  size_t len = subject.length();
  for(size_t i = 0; i < len; i++)
    subject[i] = tolower( subject[i] );
}

template<typename item_ty>
class direction_vec : public  vector< direction<item_ty> > {
public:
  using direction_fun = function< coord<item_ty>(coord<item_ty>) >;
  using vector_d = vector< direction<item_ty> >;
  direction_vec()
  {
    addDirection( "South", South<item_ty> );
    addDirection( "North", North<item_ty> );
    addDirection( "East", East<item_ty> );
    addDirection( "West", West<item_ty> );
    addDirection( "NorthWest", NorthWest<item_ty> );
    addDirection( "NorthEast", NorthEast<item_ty> );
    addDirection( "SouthEast", SouthEast<item_ty> );
    addDirection( "SouthWest", SouthWest<item_ty> );
  }

  ~direction_vec()
  {
    for( auto itr = vector_d::begin(); itr != vector_d::end(); itr++)
      delete itr->compass;
  }

  void addDirection( const char *dr_name, direction_fun dr_fun)  
  {
    vector_d::push_back( 
      direction<item_ty>( dr_name, new Compass<item_ty>( dr_fun ) )
    );
  } 
};

/** This is the class that stores the grid, prefix tree (wordlist), and 
 * and has the methods to solve the puzzle */
template<typename grid_ty>
class grid
{
  vector<string> the_grid;
  direction_vec< int > dr;
  Prefix ptree;
  Args &args;
  int X_SIZE;
  int Y_SIZE;
public:
  /** pass all parameters via an Args object. See relevant docs */
  explicit grid( Args &a )
  :  the_grid(), dr(), ptree(), args(a), X_SIZE(0), Y_SIZE(0)
  {
    bool goodWL = true;
    bool goodGrid = true;
    
    goodWL =  load_wordlist( args.get_wordlist_path() );
    if(! goodWL )
       args.flag( err_flag::WL_NOT_FOUND );   

    goodGrid =  load_grid( args.get_grid_path() );
    if(! goodGrid )
       args.flag( err_flag::GRID_NOT_FOUND );

    if( goodWL && goodGrid ) {
      Y_SIZE = the_grid.size();
      X_SIZE = the_grid.front().length(); 
    }
  }

  ~grid()
  {
  }

  /** display the grid on stdout */
  void show()
  {
    for(int row = 0; row < Y_SIZE; row++){
      for(int col = 0; col < X_SIZE; col++){
        std::cout << the_grid[row][col] << " ";
      }
      std::cout << std::endl;
    }
  }

  /** solve the puzzle and output it's solution on stdout */
  int solve()
  {
    int count = 0;
    string word; 
    Compass<int> * compass = nullptr;
    for(int row = 0; row < Y_SIZE; row++){
      for(int col = 0; col < X_SIZE; col++){
        for(auto itr = dr.begin(); itr != dr.end(); itr++){
            compass = itr->compass; 
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
  
  /* return a reference to the prefix tree being used for the wordlist */
  Prefix& get_prefix() const 
  { return ptree; }
 
private:
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
      the_grid.push_back( string() );
      while(cur != '\n' && col <= MAX_LINE_LEN){
        fsource.get(cur);
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

  /** test to see if item is in the grid at coord loc */
  bool in_cell( grid_ty & item, const coord<int> &loc )
  {
    return get_cell(loc) == item;
  }
  
  /* retreive cell at loc */ 
  grid_ty get_cell(const coord<int> &loc)
  {
    /* are we within bounds ? */
    if(   loc.y < 0     || loc.x < 0 
       || loc.y >= Y_SIZE || loc.x >= X_SIZE )
      return -1; 
    return the_grid[ loc.y ][ loc.x ];
  }

  /* given a word from a dictionary and uses the compass to compare
   * the chars one by one with the in_cell function */
  bool word_in_direction( string &word, Compass<int> &drct )
  {
    word = "";
    auto mon = ptree.monkey();
    
    while( mon.have_char( get_cell(drct.cur) ) )
    {
      word = word + get_cell(drct.cur);
      if(mon.look_ahead('\0')) return true;
      mon.advance_lvl();
      drct.advance();
    }
    
    return false;
  }

};
