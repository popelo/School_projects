#include "htable.h"

  void htab_foreach( htab_t *t, void ( *function )( const char *, unsigned int ) )
	{
		if ( t == NULL )
		{
			fprintf(stderr, "%s\n", "Invalid table(foreach)");
			return;
		}
	
		struct htab_listitem *items = NULL ;
		for ( unsigned int j = 0; j < t->htab_size; j++)
	{
		items = t->ptr[i];

		while ( items != NULL )
		{
			function(items->key, items->data);
			items = items->next;
		}
	}
}
