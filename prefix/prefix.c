/* AUTHOR: Dakota Simonds
 * DATE: Nov 6, 2017
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


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "prefix.h"

pre_node *
prefix_init( char c, pre_node *next_lvl, pre_node *child )
{
  pre_node *created = (pre_node*)malloc( sizeof(pre_node) );
  if(NULL == created) return NULL;
  created->c = c;
  created->next_lvl = next_lvl;
  created->child = child;
  return created;
}

pre_node *
prefix_new( char c )
{
  return prefix_init(c, NULL, NULL);
}

/* stuff this double pointer syntax into inline functions */


pre_node **
prefix_next_lvl( pre_node **node)
{ return &( (*node)->next_lvl ); }



pre_node **
prefix_next_child( pre_node **node)
{ return &( (*node)->child); }


char
prefix_get_c( pre_node **node )
{ return (*node)->c; }

/** find first occurance of c in the tree 
 * otherwise return a pointer to the pointer that contains null */
pre_node **
prefix_find_in_lvl( pre_node **lvl, char c )
{
  if(NULL == lvl) return NULL;

  while(NULL != *lvl)
    if( prefix_get_c(lvl) == c)
      return lvl;
    else
      lvl = prefix_next_child(lvl);

  return lvl; /* is null */
}

void prefix_insert(pre_node **root, const char *string)
{
  if(NULL == root) return;
  pre_node **cur_node = root;
  size_t str_len = strlen(string) + 1; /* +1 to include null */
  size_t pos;
  /* Traverse the tree and carry the string along with it. 
   * When we hit a null start inserting nodes till the end of the string.
   * Level and pos are in sync. */
  for( pos = 0; pos < str_len; pos++ ){
   cur_node = prefix_find_in_lvl(cur_node, string[pos]);  
   if( NULL == *cur_node )              /* Do we have the char in our level? */
     *cur_node=prefix_new(string[pos]); /* create new node and attatch if not */
   cur_node=prefix_next_lvl(cur_node);  /* advance possition in tree */
  }
}


short prefix_find( pre_node **root, const char *string )
{
  if(NULL == root) return 0;

  pre_node **cur_node = root;
  size_t str_len = strlen(string) + 1; /* +1 to include null */
  size_t pos;

  for( pos = 0; pos < str_len; pos++ ){
    cur_node = prefix_find_in_lvl(cur_node, string[pos]);
    if( NULL == *cur_node )
      return 0;
    cur_node = prefix_next_lvl(cur_node);
  }

   //if(NULL != *cur_node && NULL != (*cur_node)->next_lvl)
   //  return 0; /* disallow sub-word */

  return 1;
}

void prefix_destruct_tree( pre_node *node )
{
  if(NULL == node) return;
  prefix_destruct_tree( node->child );
  prefix_destruct_tree( node->next_lvl );
  free(node);
}

/* these next functions, prefix_depth, see_child, and prefix_show, are mostly for debugging purposes */

void prefix_show(pre_node *node)
{
  if(NULL == node) return;
  putc( node->c, stdout );
  prefix_show(node->child);
  putc( '\n', stdout );
  prefix_show(node->next_lvl);
}

unsigned prefix_depth_( pre_node *node, unsigned depth )
{
  if(NULL == node) return depth;
  unsigned a = prefix_depth_( node->next_lvl, depth+1 );
  unsigned b = prefix_depth_( node->child, depth);
  return a > b ? a : b;
}


unsigned prefix_depth( pre_node *node )
{
  return prefix_depth_(node, 0);
}

void see_child( pre_node *node )
{
  if(NULL == node){ printf("\n"); return; }
  putc(node->c, stdout);
  see_child(node->child);
}
