/**
 * Copyright 2014 Peng Wan <minexiac@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * xgc.h
 * This file is part of XGC, the X General Collection
 */

#ifndef _XGC_H_
# define _XGC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ELEMENT_TYPE
# define ELEMENT_TYPE
# define elem_t void *
#endif

/* common node */
typedef struct _node {
	elem_t data;	// element
	struct _node *prev;	// point to previous node
	struct _node *next;	// point to next node
} *xnode;

/* size of _node */
#define XNODE_SIZE	(sizeof(struct _node))

/* create a node */
extern xnode make_node(elem_t data);

/* remove node from memory */
extern void delete_node(xnode node);


#ifdef __cplusplus
}
#endif

#endif	/* _XGC_H_ */
