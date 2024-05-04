#ifndef __GLUEDLL__
#define __GLUEDLL__

typedef struct _gldll{

    struct _gldll *left;
    struct _gldll *right;
} gldll_t;

void
gldll_add_next(gldll_t *base_gldll, gldll_t *new_gldll);

void
gldll_add_before(gldll_t *base_gldll, gldll_t *new_gldll);

void
remove_gldll(gldll_t *gldll);

void
init_gldll(gldll_t *gldll);

void
gldll_add_last(gldll_t *base_gldll, gldll_t *new_gldll);

#define IS_gldll_LIST_EMPTY(gldllptr)         \
    ((gldllptr)->right == 0 && (gldllptr)->left == 0)

#define gldll_TO_STRUCT(fn_name, structure_name, field_name)                        \
    static inline structure_name * fn_name(gldll_t *gldllptr){                   \
        return (structure_name *)((char *)(gldllptr) - (char *)&(((structure_name *)0)->field_name)); \
    }

/* delete safe loop*/
/*Normal continue and break can be used with this loop macro*/

#define BASE(gldllptr)   ((gldllptr)->right)

#define ITERATE_gldll_BEGIN(gldllptrstart, gldllptr)                                      \
{                                                                                                  \
    gldll_t *_gldll_ptr = NULL;                                                              \
    gldllptr = BASE(gldllptrstart);                                                          \
    for(; gldllptr!= NULL; gldllptr = _gldll_ptr){                                        \
        _gldll_ptr = (gldllptr)->right;

#define ITERATE_gldll_END(gldllptrstart, gldllptr)                                        \
        }}

#define gldll_GET_USER_DATA_FROM_OFFSET(gldllptr, offset)  \
    (void *)((char *)(gldllptr) - offset)

void
delete_gldll_list(gldll_t *base_gldll);

unsigned int 
get_gldll_list_count(gldll_t *base_gldll);

void
gldll_priority_insert(gldll_t *base_gldll,     
                         gldll_t *gldll,
                         int (*comp_fn)(void *, void *),
                         int offset);


#if 0
void *
gl_thread_search(gldll_t *base_gldll,
        void *(*thread_to_struct_fn)(gldll_t *),
        void *key,
        int (*comparison_fn)(void *, void *));

#endif
#endif /* __GLUEDLL__ */
