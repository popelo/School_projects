#include "htable.h"

 void htab_free( htab_t *t )
	{
		if ( t == NULL )
			return;
		
		htab_clear( t );
		free( t );
		t = NULL;
	}

