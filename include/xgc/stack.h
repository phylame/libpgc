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
 * stack.h
 * FILO - stack
 * This file is part of XGC, the X General Collection
 */

#ifndef _STACK_H_
# define _STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"

// using the XList
typedef XList XStack;

#define mkstk mklist
#define rmstk rmlist
#define stklen listlen
#define stkpush listadd

/* pop an element */
void stkpop(XStack *stack);


#ifdef __cplusplus
}
#endif

#endif	/* _STACK_H_ */
