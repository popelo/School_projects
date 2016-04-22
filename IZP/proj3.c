/**
 * Kostra programu pro 3. projekt IZP 2015/16
 *
 * Jednoducha shlukova analyza: 2D nejblizsi soused.
 * Single linkage
 * http://is.muni.cz/th/172767/fi_b/5739129/web/web/slsrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;		
    float x;		
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/

void init_cluster(struct cluster_t *c, int cap)
	{
    		assert(c != NULL);
    		assert(cap >= 0);
		// TODO 
			if(cap==0)
				{
					c->obj = NULL;
					c->size=0;
				}
			else
				{
					c->obj = malloc(cap*sizeof(struct obj_t));
        				c->capacity=cap;
				}
			if(c->obj==NULL)
					return;
	}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
	{
    	// TODO
		free(c->obj);
		c->obj = NULL;
         	c->size=0;
	}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */ 
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
	{
    	// TODO
		if(c->capacity == c->size)
			{
				c=resize_cluster(c, c->capacity+CLUSTER_CHUNK);
			}
		c->obj[c->size]=obj;
		c->size=c->size+1;
	}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */

void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */

void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
	{
    		assert(c1 != NULL);
    		assert(c2 != NULL);

    	// TODO
		if(c1->capacity < (c1->size + c2->size))
			c1=resize_cluster(c1, (c1->size+c2->size));
		for(int i=0; i<(c2->size);i++)
			{
				append_cluster(c1,c2->obj[i]);
			}
		sort_cluster(c1);	
	}	

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
	{
    		assert(idx < narr);
    		assert(narr > 0);
		// TODO
			clear_cluster(&carr[idx]);
			for(int i=idx;i<narr-1;i++)
				{
					carr[i]=carr[i+1];
				}
			return(narr-1);
	}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
	{
    		assert(o1 != NULL);
    		assert(o2 != NULL);
		// TODO
			return(sqrtf((o1->x-o2->x)*(o1->x-o2->x)+(o1->y-o2->y)*(o1->y-o2->y)));
	}
	
/*
 Pocita vzdalenost dvou shluku. Vzdalenost je vypoctena na zaklade nejblizsiho
 souseda.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
	{
    		assert(c1 != NULL);
    		assert(c1->size > 0);
    		assert(c2 != NULL);
    		assert(c2->size > 0);
		// TODO
			float min=INFINITY;
			float vzdialenost;
		for(int i=0; i<c1->size;i++)
			{
				for(int j=0; j<c2->size;j++)
					{
       						vzdialenost=obj_distance(&c1->obj[i],&c2->obj[j]);
						if(vzdialenost < min)
							min=vzdialenost;
					}
			}
		return(min);
	}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky (podle nejblizsiho souseda). Nalezene shluky
 identifikuje jejich indexy v poli 'carr'. Funkce nalezene shluky (indexy do
 pole 'carr') uklada do pameti na adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
	{
    		assert(narr > 0);
		// TODO
			int index1, index2;
			float min=INFINITY;
			float minMinimum=0;
			for(int i=0;i<narr -1;i++)
				{
					for(int j= i+1;j<narr;j++)
						{
							min=cluster_distance(&carr[i], &carr[j]);
							if (minMinimum == 0 || minMinimum > min )
								{
									index1= i;
									index2= j;
									minMinimum = min;
								}
						}
				}
			*c1 = index1;
			*c2 = index2;
	}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = a;
    const struct obj_t *o2 = b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
	{
    		assert(arr != NULL);
		// TODO
			int n;
			FILE *subor;
			subor = fopen(filename, "r");
			fscanf(subor,"count=%d", &n);
			int flag=0;
			struct cluster_t *zhluk=malloc(n*sizeof(struct cluster_t));
			if(zhluk == NULL)
			{
			return(-1);
			}
			for(int i=0; i<n; i++)
				{
					init_cluster(&zhluk[i],CLUSTER_CHUNK);
					fscanf(subor,"%d%g%g",&zhluk[i].obj[0].id,&zhluk[i].obj[0].x,&zhluk[i].obj[0].y);
						if(zhluk[i].obj[0].x < 0 || zhluk[i].obj[0].x >1000)
							flag=1;			
				         	if(zhluk[i].obj[0].y < 0 || zhluk[i].obj[0].y >1000)
                                                        flag=1;                                                        
                             			zhluk[i].size=1;
				}
			*arr=&zhluk[0];
			fclose(subor);
			if(flag==1)
			n=-1;
			return(n);
	}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/

void print_clusters(struct cluster_t *carr, int narr)
	{
    		printf("Clusters:\n");
    		for (int i = 0; i < narr; i++)
    			{
        			printf("cluster %d: ", i);
        			print_cluster(&carr[i]);
    			}
	}

int main(int argc, char *argv[])
	{
		struct cluster_t *clusters;
		// TODO
			int n,first,idx1,idx2;
			long int test;
			int err=0;
			if(argc==2)
				{
					n=1;	
				}
			else
				{
					if(argc>3 || argc<3)
						err=1;
				}
		first=load_clusters(argv[1], &clusters);
		if(first==-1)
			err=1;
		if(argc!=2)
			{
				sscanf(argv[2], "%ld",&test);
				if(test > UINT_MAX)
				err=1;
				sscanf(argv[2], "%d", &n);
			}
		if(n>first)
			err=1;
		if(n<=0)
			err=1;	
		if(err==1)
			{			                               
				while (first>0)
                                	{
                                        	first=remove_cluster(clusters,first,first-1);
                                	}
             	free(clusters);
		fprintf(stderr,"ERROR\n");
                return(-1);
			}		
	
       
		while (n != first)
			{
				find_neighbours(clusters, first, &idx1, &idx2);
	   			merge_clusters(&clusters[idx1], &clusters[idx2]);
				first=remove_cluster(clusters, first, idx2);
			}
		print_clusters(clusters, n);
		while (first>0)
			{
				first=remove_cluster(clusters,first,first-1);
			}
		free(clusters);
		return(0);
	}
 
