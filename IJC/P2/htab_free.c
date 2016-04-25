// Filip Bednár
// xbedna63
// VUT FIT
// príklad (b 
// 14.4.2016

#include "htable.h"

 void htab_free( htab_t *t )
	{
		if ( t == NULL )
			return;
		
		htab_clear( t );
		free( t );
		t = NULL;
	}

