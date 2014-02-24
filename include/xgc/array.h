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
 * array.h
 * A simple array
 * This file is part of XGC, the X General Collection
 */

#ifndef _ARRAY_H_
# define _ARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "xgc.h"	// elem_t
#include <stddef.h>	// size_t
#include <stdbool.h>	// bool

typedef struct _array {
	elem_t *base;
	int (*cmp)(const elem_t a, const elem_t b);
	size_t capacity;		// current capacity
	size_t increment;		// alloc increment
	size_t size;			// contains elements count
} XArray;

#define ARRAY_CAPACITY		30
#define ARRAY_INCREMENT			20

extern XArray* mkary(void);

extern bool initary(XArray *ary, size_t capacity, size_t increment);

extern void rmary(XArray *ary);

extern void clrary(XArray *ary);

#define	arylen					xxxlen
#define arycap(ary)				(NULL == ary ? 0 : ary->capacity)

extern void arytrv(XArray *ary, bool (*visit)(elem_t value, void *arg),
	void *arg);

extern bool aryadd(XArray *ary, elem_t value);

extern bool aryins(XArray *ary, int index, elem_t value);

extern bool aryext(XArray *ary, const XArray *other);

extern bool arydel(XArray *ary, const elem_t value);

extern bool arypop(XArray *ary, int index, elem_t *value);

extern int aryloc(const XArray *ary, const elem_t value);

extern bool aryhas(const XArray *ary, const elem_t value);

extern elem_t aryget(const XArray *ary, int index, elem_t def_value);

extern bool aryset(XArray *ary, int index, elem_t value);

/* base point */
extern elem_t* arybeg(const XArray *ary);

/* end point */
extern elem_t* aryend(const XArray *ary);

/* next point */
extern elem_t* arynext(XArray *ary, elem_t *current);

#ifdef __cplusplus
}
#endif

#endif	/* _ARRAY_H_ */
