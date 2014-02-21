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
 * xgc.c
 * This file is part of XGC, the X General Collection
 */


# include <xgc/xgc.h>
#include <stdlib.h>

/* create a node */
xnode make_node(elem_t data)
{
	xnode node = malloc(XNODE_SIZE);
	if (node != NULL) {
		node->data = data;
		node->prev = node->next = NULL;
	}
	return node;
}

/* remove node from memory */
void delete_node(xnode node)
{
	if (node != NULL)
		free(node);
}

