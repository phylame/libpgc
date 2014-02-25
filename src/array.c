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
 * array.c
 * A simple array
 * This file is part of XGC, the X General Collection
 */

#include <xgc/array.h>
#include <stdlib.h>


static bool resize_array(XArray *ary, size_t new_cap)
{
	if (NULL == ary)
		return false;
	else if (new_cap == arycap(ary))
		return true;
	if (NULL == (ary->base = realloc(ary->base, new_cap * sizeof(elem_t))))
		return false;
	ary->capacity = new_cap < 0 ? 0 : new_cap;
	return true;
}

static bool increase_array(XArray *ary)
{
	return resize_array(ary, arycap(ary) + ary->increment);
}

static elem_t* get_elem_by_index(const XArray *ary, int index)
{
	if (NULL == ary || index < 0 || index >= arylen(ary))
		return NULL;
	return &ary->base[index];
}

int compare_element(XArray *ary, elem_t *a, elem_t *b)
{
	if (ary->cmp != NULL)
		return ary->cmp(*a, *b);
	else
		return *a - *b;
}

static bool move_forward(XArray *ary, int index, int num)
{
	int i;
	if (NULL == ary || index < 0 || index >= arylen(ary) || num < 0)
		return false;
	else if (0 == num)
		return true;
	if (num > index)	// overfolw
		return false;
	for (i = index; i < arylen(ary); ++i) {
		ary->base[i - num] = ary->base[i];
	}
	return true;
}

static bool move_backward(XArray *ary, int index, int num)
{
	int i, end;
	if (NULL == ary || index < 0 || index > arylen(ary) || num < 0)
		return false;
	else if (0 == num)
		return true;
	if (arylen(ary) + num > arycap(ary) && resize_array(ary,
				arycap(ary) + num))
		return false;
	end = arylen(ary) - 1;
	for (i = end; i >= index; --i) {
		ary->base[i + num] = ary->base[i];
	}
	return true;
}

static void copy_from(elem_t *dest, elem_t *begin, elem_t *end)
{
	elem_t *cur;
	for (cur = begin; cur != end; ++cur) {
		*dest++ = *cur;
	}
}

XArray *mkary(void)
{
	XArray *ary = malloc(sizeof(XArray));
	if (NULL == ary)
		return NULL;
	if (! initary(ary, ARRAY_CAPACITY, ARRAY_INCREMENT)) {
		free(ary);
		return NULL;
	}
	return ary;
}

XArray* aryfrom(elem_t *src, int index, size_t num)
{
	XArray *ary = malloc(sizeof(XArray));
	if (NULL == ary || NULL == src || index < 0)
		return NULL;
	if (! initary(ary, num, ARRAY_INCREMENT)) {
		free(ary);
		return NULL;
	}
	copy_from(ary->base, src + index, src + index + num);
	ary->size = num;
	ary->cmp = NULL;
	return ary;
}

bool initary(XArray *ary, size_t capacity, size_t increment)
{
	if (NULL == ary)
		return false;
	if (! resize_array(ary, capacity))
		return false;
	ary->increment = increment;
	ary->size = 0;
	ary->cmp = NULL;
	return true;
}

void rmary(XArray *ary)
{
	if (NULL == ary)
		return;
	free(ary->base);
	free(ary);
}

void clrary(XArray *ary)
{
	if (NULL == ary)
		return;
	ary->size = 0;
}

int arycmp(XArray *ary1, XArray *ary2)
{
	int i, ret = 0;
	if (arylen(ary1) > arylen(ary2))
		return 1;
	else if (arylen(ary1) < arylen(ary2))
		return -1;
	for (i = 0; i < arylen(ary1); ++i) {
		if ((ret = compare_element(ary1, ary1->base + i,
						ary2->base + i) != 0))
			return ret;
	}
	return ret;
}

bool arycpy(XArray *dest, const XArray *src, size_t num)
{
	if (NULL == dest || NULL == src)
		return false;
	return false;
}

void arytrv(XArray *ary, bool (*visit)(elem_t a, void *arg), void *arg)
{
	int i;
	if (NULL == ary || NULL == visit)
		return;
	for (i = 0; i < arylen(ary); ++i) {
		if (visit(ary->base[i], arg))
			break;
	}
}

bool aryadd(XArray *ary, elem_t value)
{
	if (NULL == ary)
		return false;
	else if (arylen(ary) >= arycap(ary)) {
		if (! increase_array(ary))
			return false;
	}
	ary->base[arylen(ary)] = value;
	++ary->size;
	return true;
}

bool aryins(XArray *ary, int index, elem_t value)
{
	if (NULL == ary || index < 0 || index >= arylen(ary))
		return false;
	else if (arylen(ary) >= arycap(ary)) {
		if (! increase_array(ary))
			return false;
	}
	if (! move_backward(ary, index, 1)) {	// cannot move
		return false;
	} else {
		ary->base[index] = value;
		++ary->size;
		return true;
	}
}

bool aryext(XArray *ary, const XArray *other)
{
	int i, free_space;
	if (NULL == ary || NULL == other)
		return false;
	free_space = arycap(ary) - arylen(ary);
	if (free_space < arylen(other)) {	// no more space
		if (! resize_array(ary, arycap(ary) + arylen(other)))
			return false;
	}
	for (i = 0; i < arylen(other); ++i) {
		ary->base[arylen(ary) + i] = other->base[i];
	}
	ary->size += arylen(other);
	return true;
}

bool arydel(XArray *ary, const elem_t value)
{
	int index = aryloc(ary, value);
	if (-1 == index)		// not in array
		return false;
	if (! move_forward(ary, index + 1, 1))
		return false;
	--ary->size;
	return true;
}

bool arypop(XArray *ary, int index, elem_t *value)
{
	elem_t *elem = get_elem_by_index(ary, index);
	if (NULL == elem)		// invalid index
		return false;
	if (value != NULL)
		*value = *elem;
	if (! move_forward(ary, index + 1, 1)) {
		return false;
	}
	--ary->size;
	return true;
}

int aryloc(const XArray *ary, const elem_t value)
{
	int i;
	if (NULL == ary)
		return -1;
	for (i = 0; i < arylen(ary); ++i) {
		if (ary->cmp != NULL) {
			if (0 == ary->cmp(ary->base[i], value))
				return i;
		} else if (value == ary->base[i]) {
			return i;
		}
	}
	return -1;
}

bool aryhas(const XArray *ary, const elem_t value)
{
	return aryloc(ary, value) != -1;
}

elem_t aryget(const XArray *ary, int index, elem_t def_value)
{
	elem_t *elem = get_elem_by_index(ary, index);
	if (NULL == elem)
		return def_value;
	else
		return *elem;
}

bool aryset(XArray *ary, int index, elem_t value)
{
	elem_t *elem = get_elem_by_index(ary, index);
	if (NULL == elem)
		return false;
	*elem = value;
	return true;
}

elem_t* arybeg(const XArray *ary)
{
	if (NULL == ary || 0 == arylen(ary))	// no elements
		return NULL;
	else
		return ary->base;
}

elem_t* aryend(const XArray *ary)
{
	if (NULL == ary || 0 == arylen(ary))
		return NULL;
	else
		return ary->base + arylen(ary);
}

elem_t* arynext(const XArray *ary, const elem_t *current)
{
	if (NULL == ary || 0 == arylen(ary))
		return NULL;
	if (current == aryend(ary))
		return NULL;
	return current + 1;
}
