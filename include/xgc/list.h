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
 * list.h
 * A common linked list
 * This file is part of XGC, the X General Collection
 */

#ifndef _LIST_H_
# define _LIST_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "xgc.h"
#include <stdbool.h>
#include <stddef.h>

/* linked list */
typedef struct {
	xnode head;
	xnode tail;
	int (*cmp)(const elem_t a, const elem_t b);
	size_t size;
} XList;

/* create an empty list */
extern XList* mklist(void);

/* initializa list */
extern bool initlist(XList *list);

/* remove list from memory */
extern void rmlist(XList *list);

/* clean list */
extern void clrlist(XList *list);

/* get the length of list */
#define listlen xxxlen

/* travel list */
extern void listrv(XList *list, bool (*visit)(elem_t value, void *arg),
	void *arg);

/* append an element to the end of list */
extern bool listadd(XList *list, elem_t value);

/* insert an element before index in list */
extern bool listins(XList *list, int index, elem_t value);

/* extend list with other list */
extern void listext(XList *list, const XList *other);

/* remove an element from list */
extern void listdel(XList *list, const elem_t value);

/* remove an element from list by its index */
extern void listpop(XList *list, int index);

/* get the index of element in list */
extern int listloc(const XList *list, const elem_t value);

/* test element is in list */
extern bool listhas(const XList *list, const elem_t value);

/* set element at index in list */
extern bool listset(XList *list, int index, elem_t value);

/* get element at index in list */
extern elem_t listget(const XList *list, int index, elem_t def_value);

#ifdef __cplusplus
}
#endif

#endif	/* _LIST_H_ */
