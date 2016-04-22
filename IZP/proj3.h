/** @file console.h
 * @brief Prototypes of functions.
 *
 *
 * Program for cluster analysis.
 *
 *
 * @author Filip Bednár(xbedna63)
 */

/** \defgroup Structures
 * @brief Object and cluster structure
 * @{
 */

/** @brief  obj_t declares an object.
 */

struct obj_t {
    int id; /**< Object ID  */
    float x; /**<X axis of a cluster */
    float y; /**<Y axis of a cluster*/
};

/** @brief  cluster_t declares a cluster.
 */

struct cluster_t {
    int size; /**< Number of objects in the cluster  */
    int capacity; /**< Maximum capacity for objects and clusters */
    struct obj_t *obj; /**< Obj is pointing at an array of objects */
};

/**
 * @}
 */

/** \defgroup Clusters
 * @brief Functions for cluster operations
 * @{
 */

/**
 * @brief Function initializes cluster 'c' and allocates memory for capacity 
 *
 * If the capacity is 0, cluster points to NULL.
 * @pre c != NULL
 * @pre cap >=0
 * @post Memory was allocated for the cluster.
 * @param *c Cluster pointer which will be initialized
 * @param cap Cluster capacity
 * @return void
 */
void init_cluster(struct cluster_t *c, int cap);

/** @brief Function will remove objects of cluster 'c' and initializes empty cluster.
 * @pre Cluster
 * @post Empty cluster
 * @param *c Pointer to the cluster was deleted
 * @return void
 */

void clear_cluster(struct cluster_t *c);

/** 
 * @brief Recommended value for resizing capacity
 */

extern const int CLUSTER_CHUNK;

/** @brief Function to resize cluster c to the new capacity 'new_cap'.
 *
 * @pre c
 * @pre c->capacity >= 0
 * @post Cluster resized to the new capacity
 * @post new_cap >= 0
 * @post The cluster was resized
 * @param *c Pointer to the cluster which will be resized
 * @param new_cap New capacity for cluster c
 * @return Capacity was resized
 */

struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/** @brief Function appends new object to the end of an array 'cluster->obj'.
 *
 *
 * @post  * @post New object was added to he cluster
 * @param *c Pointer to cluster
 * @param obj Object that will be added to the end of the cluster
 * @return void
 */

void append_cluster(struct cluster_t *c, struct obj_t obj);

/** @brief Function adds object from 'c2' to  'c1'.
 *
 * @pre c1 != NULL
 * @pre c2 != NULL
 * @post Objects from c2 were added to the c1
 * @param *c1 Pointer to the cluster(where are objects copied)
 * @param *c2 Pointer to the cluster(from which are objects copied)
 * @return void
 */

void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/** @brief Function removes cluster from the array of clusters.
 *
 * @pre idx < narr
 * @pre narr > 0
 * @post Cluster was removed from the array of clusters
 * @param *carr Pointer to the array of clusters
 * @param narr How many  clusters in the array
 * @param idx Position of cluster in the array
 * @return New order of the clusters in the array
 */

/**
 * @}
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/** \defgroup Object
 * @brief Functions for cluster operations
 * @{
 */

/** @brief Function calculates distance between two objects.
 * @pre o1 != NULL
 * @pre o2 != NULL
 * @post Distance between two objects
 * @param *o1 Pointer to the fisrt object
 * @param *o2 Pointer to the second object
 * @return Distance between two objects
 */

float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * @}
 */

/** \defgroup Cluster_functions
 * @{
 */

/** @brief Function to calculate distance between two clusters.
 * @pre c1 != NULL
 * @pre c1->size > 0
 * @pre c2 != NULL
 * @prec2->size > 0
 * @post Distance between two clusters
 * @param *c1 Pointer to the fist cluster
 * @param *c2 Pointer to the second cluster
 * @return Distance between two clusters
 */

float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/** @brief Function to find out two closets clusters in array.
 * @pre narr > 0
 * @post Index of the two closest clusters
 * @param *carr Point to the array of clusters
 * @param narr Number of clusters in the array
 * @param *c1 Pointer to the adress in memory  where is first cluster 
 * @param *c2 Pointer to the adress in memory  where is the second cluster 
 */

void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/** @brief Function sorts cluster 'c'.
 * @post Cluster c was sorted
 * @param *c Pointer to the cluster that will be sorted
 * @return void
 */

void sort_cluster(struct cluster_t *c);

/** @brief Function to print cluster.
 * @pre c != NULL
 * @post Cluster was printed
 * @param *c Pointer to cluster
 * @return void
 */

void print_cluster(struct cluster_t *c);

/** @brief Function reads objects from the file and creates a cluster for them.
 *
 * If the function can't read the object pointer, arr is set to NULL.
 *
 * @pre arr != NULL
 * @post Returning a number of clusters created and saved to the array arr
 * @param *filename Pointer to the name of the file function should read from
 * @param **arr Pointer to the array of clusters
 * @return number of created clusters
 */

int load_clusters(char *filename, struct cluster_t **arr);

/** @brief Function to print clusters from the array of clusters.
 * @pre carr = NULL
 * @pre narr > 0
 * @post Clusters were printed
 * @param *carr Pointer to the array fo clusters
 * @param narr How many clusters are in the array in the array
 * @return void
 */

/**
 * @}
 */

void print_clusters(struct cluster_t *carr, int narr);
