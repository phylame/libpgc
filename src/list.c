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
 * list.c
 * A common linked list
 * This file is part of XGC, the X General Collection
 */

#include <xgc/list.h>
#include <stdlib.h>	// malloc, free
#include <stdbool.h>	// bool
#include <stddef.h>	// size_t

/* remove xnode from list */
static void rmnod(xnode node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete_node(node);
}

/* insert element before node */
static bool insnod(elem_t value, xnode pos)
{
	xnode node;
	if (NULL == pos)
		return false;
	node = make_node(value);
	if (NULL == node)
		return false;
	node->next = pos;
	node->prev = pos->prev;
	node->next->prev = node;
	node->prev->next = node;
	return true;
}

/* get node by value */
static xnode get_node_by_value(const XList *list, const elem_t value,
		int *index)
{
	xnode cur;
	int i = 0;
	if (NULL == list)
		return NULL;
	for (cur = list->head->next; cur != list->tail; cur = cur->next) {
		if (list->cmp != NULL) {	// has compared function
			if (0 == list->cmp(cur->data, value))
				break;
		} else if (cur->data == value) {
			break;
		}
		++i;
	}
	if (cur != list->tail) {
		if (index != NULL)
			*index = i;
		return cur;
	} else
		return NULL;
}

/* get node by index */
static xnode get_node_by_index(const XList *list, int index)
{
	xnode cur;
	int i = 0;
	if (NULL == list || index < 0)
		return NULL;
	cur = list->head->next;
	while (cur != list->tail && i < index) {
		cur = cur->next;
		++i;
	}
	if (cur == list->tail || i > index)
		return NULL;
	return cur;
}

XList* mklist(void)
{
	XList* list = malloc(sizeof(XList));
	if (NULL == list)
		return NULL;
	if (initlist(list))
		return list;
	else
		return NULL;
}

bool initlist(XList *list)
{
	if (NULL == list)
		return false;
	// two sentries
	list->head = make_node(NULL);
	list->tail = make_node(NULL);
	if (NULL == list->head || NULL == list->tail) {
		rmlist(list);
		return false;
	}
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->size = 0;
	return true;
}

void rmlist(XList *list)
{
	if (NULL == list)
		return;
	clrlist(list);			// clean all elements
	delete_node(list->head);	// remove head sentry
	delete_node(list->tail);	// remove tail sentry
	free(list);
}

void clrlist(XList *list)
{
	xnode cur;
	if (NULL == list)
		return;
	cur = list->head->next;
	while (cur != list->tail) {
		cur = cur->next;
		rmnod(cur->prev);
		--list->size;
	}
}

size_t listlen(const XList *list)
{
	return NULL == list ? 0 : list->size;
}

void listrv(XList *list, bool (*visit)(elem_t value, void *arg), void *arg)
{
	xnode cur;
	if (NULL == list || NULL == visit)
		return;
	for (cur = list->head->next; cur != list->tail; cur = cur->next) {
		if (visit(cur->data, arg))
			break;
	}
}

bool listadd(XList *list, elem_t value)
{
	if (NULL == list)
		return false;
	else if (! insnod(value, list->tail))
		return false;
	++list->size;
	return true;
}

bool listins(XList *list, int index, elem_t value)
{
	xnode pos;
	pos = get_node_by_index(list, index);
	if (NULL == pos)
		return false;
	else if (! insnod(value, pos))
		return false;
	++list->size;
	return true;
}

void listext(XList *list, const XList *other)
{
	xnode cur;
	if (NULL == list || NULL == other)
		return;
	for (cur = other->head->next; cur != other->tail; cur = cur->next) {
		if (! insnod(cur->data, list->tail))
			continue;
		++list->size;
	}
}

void listdel(XList *list, const elem_t value)
{
	xnode node = get_node_by_value(list, value, NULL);
	if (node != NULL) {
		rmnod(node);
		--list->size;
	}
}

void listpop(XList *list, int index)
{
	xnode node = get_node_by_index(list, index);
	if (NULL == node)
		return;
	rmnod(node);
	--list->size;
}

int listloc(const XList *list, const elem_t value)
{
	int index;
	xnode node = get_node_by_value(list, value, &index);
	if (node != NULL)
		return index;
	else
		return -1;
}

bool listhas(const XList *list, const elem_t value)
{
	return listloc(list, value) != -1;
}

bool listset(XList *list, int index, elem_t value)
{
	xnode node = get_node_by_index(list, index);
	if (NULL == node)
		return false;
	node->data = value;
	return true;
}

elem_t listget(const XList *list, int index, elem_t def_value)
{
	xnode node = get_node_by_index(list, index);
	if (NULL == node) {	// not found
		return def_value;
	} else {
		return node->data;
	}
}
