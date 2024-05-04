/*
 * =====================================================================================
 *
 *    Description:  Implementation of glue doubly link list Library
 * =====================================================================================
 */


#include "gldll.h"
#include <stdlib.h>

void
init_gldll(gldll_t *gldll){

    gldll->left = NULL;
    gldll->right = NULL;
}

void
gldll_add_next(gldll_t *curr_gldll, gldll_t *new_gldll){

    if(!curr_gldll->right){
        curr_gldll->right = new_gldll;
        new_gldll->left = curr_gldll;
        return;
    }

    gldll_t *temp = curr_gldll->right;
    curr_gldll->right = new_gldll;
    new_gldll->left = curr_gldll;
    new_gldll->right = temp;
    temp->left = new_gldll;
}

void
gldll_add_before(gldll_t *curr_gldll, gldll_t *new_gldll){
    
    if(!curr_gldll->left){
        new_gldll->left = NULL;
        new_gldll->right = curr_gldll;
        curr_gldll->left = new_gldll;
        return;
    }
    
    gldll_t *temp = curr_gldll->left;
    temp->right = new_gldll;
    new_gldll->left = temp;
    new_gldll->right = curr_gldll;
    curr_gldll->left = new_gldll;
}

void
remove_gldll(gldll_t *curr_gldll){
    
    if(!curr_gldll->left){
        if(curr_gldll->right){
            curr_gldll->right->left = NULL;
            curr_gldll->right = 0;
            return;
        }
        return;
    }
    if(!curr_gldll->right){
        curr_gldll->left->right = NULL;
        curr_gldll->left = NULL;
        return;
    }

    curr_gldll->left->right = curr_gldll->right;
    curr_gldll->right->left = curr_gldll->left;
    curr_gldll->left = 0;
    curr_gldll->right = 0;
}

void
delete_gldll_list(gldll_t *base_gldll){

    gldll_t *gldllptr = NULL;
               
    ITERATE_gldll_BEGIN(base_gldll, gldllptr){
        remove_gldll(gldllptr);
    } ITERATE_gldll_END(base_gldll, gldllptr);
}

void
gldll_add_last(gldll_t *base_gldll, gldll_t *new_gldll){

    gldll_t *gldllptr = NULL,
               *prevgldllptr = NULL;
    
    ITERATE_gldll_BEGIN(base_gldll, gldllptr){
        prevgldllptr = gldllptr;
    } ITERATE_gldll_END(base_gldll, gldllptr);
  
    if(prevgldllptr) 
        gldll_add_next(prevgldllptr, new_gldll); 
    else
        gldll_add_next(base_gldll, new_gldll);
}

unsigned int
get_gldll_list_count(gldll_t *base_gldll){

    unsigned int count = 0;
    gldll_t *gldllptr = NULL;

    ITERATE_gldll_BEGIN(base_gldll, gldllptr){
        count++;
    } ITERATE_gldll_END(base_gldll, gldllptr);
    return count;
}


void
gldll_priority_insert(gldll_t *base_gldll, 
                         gldll_t *gldll,
                         int (*comp_fn)(void *, void *),
                         int offset){


    gldll_t *curr = NULL,
               *prev = NULL;

    init_gldll(gldll);

    if(IS_gldll_LIST_EMPTY(base_gldll)){
        gldll_add_next(base_gldll, gldll);
        return;
    }

    /* Only one node*/
    if(base_gldll->right && !base_gldll->right->right){
        if(comp_fn(gldll_GET_USER_DATA_FROM_OFFSET(base_gldll->right, offset), 
                gldll_GET_USER_DATA_FROM_OFFSET(gldll, offset)) == -1){
            gldll_add_next(base_gldll->right, gldll);
        }
        else{
            gldll_add_next(base_gldll, gldll);
        }
        return;
    }

    if(comp_fn(gldll_GET_USER_DATA_FROM_OFFSET(gldll, offset), 
            gldll_GET_USER_DATA_FROM_OFFSET(base_gldll->right, offset)) == -1){
        gldll_add_next(base_gldll, gldll);
        return;
    }

    ITERATE_gldll_BEGIN(base_gldll, curr){

        if(comp_fn(gldll_GET_USER_DATA_FROM_OFFSET(gldll, offset), 
                gldll_GET_USER_DATA_FROM_OFFSET(curr, offset)) != -1){
            prev = curr;
            continue;
        }

        if(!prev)
            gldll_add_next(base_gldll, gldll);
        else
            gldll_add_next(prev, gldll);
        
		return;

    }ITERATE_gldll_END(base_gldll, curr);

    /*Add in the end*/
    gldll_add_next(prev, gldll);
} 

#if 0
void *
gl_thread_search(gldll_t *base_gldll, 
                 void *(*thread_to_struct_fn)(gldll_t *), 
                 void *key, 
                 int (*comparison_fn)(void *, void *)){

    return NULL;
}
#endif
