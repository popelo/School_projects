//niake if def, pozrieť neskôr

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hash_function.h"

  struct htab_listitem 
	{
		char *key;
		unsigned long data;
		struct htab_listitem *next;
	};

  typedef struct htab_t
	{
		unsigned int htab_size;
		unsigned int ( *hash_fun_ptr )( const char *, unsigned );
		unsigned int n;
		struct htab_listitem *ptr[]; 
	} htab_t;
  
  htab_t *htab_init( unsigned int size );
  htab_t *htab_init2( unsigned int size, unsigned int ( *hashfunction )( const char *str, unsigned htab_size ) );

  struct htab_listitem *htab_lookup_add( htab_t *t, const char *key );

  void htab_foreach( htab_t *t, void ( *function )( const char *, unsigned int ) );
  void htab_remove( htab_t *t, const char *key );
  void htab_clear( htab_t *t );
  void htab_free( htab_t *t );	
