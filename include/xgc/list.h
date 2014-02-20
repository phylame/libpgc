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
extern "C"
#endif


#include "xgc.h"
#include <stdbool.h>

/* linked list */
typedef struct {
	xnode head;
	xnode tail;
	size_t size;
} XList;

/* create an empty list */
extern XList* mklist(void);

/* initializa list */
extern void initlist(XList *list);

/* remove list from memory */
extern void rmlist(XList *list);

/* clean list */
extern void clrlist(XList *list);

/* get the length of list */
extern size_t listlen(const XList *list);

/* travel list */
extern void listrv(XList *list, bool (*walk)(void *data));

extern void listadd(XList *list, const void *data);
extern void listins(XList *list, int index, const void *data);
extern void listext(XList *list, const XList *other);

extern void listdel(XList *list, const void *data);
extern void listpop(XList *list, int index);

extern int listloc(XList *list, const void *data);
extern bool listhas(XList *list, const void *data);

extern void listset(XList *list, int index, void *data);
extern void* listget(XList *list, int index);

#ifdef __cplusplus
}
#endif

#endif	/* _LIST_H_ */
