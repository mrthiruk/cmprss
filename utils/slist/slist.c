#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cmprss_common.h"
#include "mem.h"
#include "slist.h"

status_ct 
slist_insert_at_tail(slist_ct **head, void *data)
{
	if (!head || !data) {
		return CMPRSS_FAILURE;
	}
	slist_ct *tail = *head;
	while (tail && tail->next) {
		tail = tail->next;
	}
	slist_ct *item = mem_calloc(sizeof(slist_ct));
	item->dat = data;
	if (tail) {
		tail->next = item;
	} else {
		*head = item;
	}
	return CMPRSS_SUCCESS;
}

status_ct 
slist_insert_at_head(slist_ct **head, void *data)
{
	if (!head || !data) {
		return CMPRSS_FAILURE;
	}
	slist_ct *item = mem_calloc(sizeof(slist_ct));
	item->next = *head;
	*head = item;
	return CMPRSS_SUCCESS;
}

// Assumes the list to be non-empty & sorted in ascending order
status_ct 
slist_insert_after(slist_ct **head, void *data, 
		status_ct (*cmp_cback)(void *, void *))
{
	if (!head || !data || !cmp_cback) {
		return CMPRSS_FAILURE;
	}
	if (!(*head)) {
		*head = mem_calloc(sizeof(slist_ct));
		(*head)->dat = data;
		return CMPRSS_SUCCESS;
	}
	slist_ct *curr = *head,
			 *prev = NULL;
	while (curr) {
		if (CMPRSS_GREAT == cmp_cback(curr->dat, data)) {
			prev->next = mem_calloc(sizeof(slist_ct));
			prev->next->dat = data;
			prev->next->next = curr;
			return CMPRSS_SUCCESS;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = mem_calloc(sizeof(slist_ct));
	prev->next->dat = data;
	return CMPRSS_SUCCESS;
}

status_ct 
slist_delete(slist_ct **head, void *cmp_key, 
		status_ct (*cmp_cback)(void *, void *), 
		void (*del_cback)(void *), bool delete_dat, bool delete_first)
{
	if (!head || !cmp_key || !cmp_cback || !del_cback) {
		return CMPRSS_FAILURE;
	}
	slist_ct *prev = NULL,
			 *curr = slist_search(head, &prev, cmp_key, 
					 cmp_cback, delete_first);
	if (!curr) {
		return CMPRSS_FAILURE;
	}
	if (prev) {
		prev->next = curr->next;
	} else {
		*head = curr->next;
	}
	if (delete_dat) {
		del_cback(curr->dat);
	}
	mem_free(curr);
	return CMPRSS_SUCCESS;
}

slist_ct* 
slist_search(slist_ct **head, slist_ct **prev, void *cmp_key, 
		status_ct (*cmp_cback)(void *, void *), bool ret_first)
{
	slist_ct *curr = *head, 
			 *ret = NULL, 
			 *temp = NULL;
	*prev = NULL;
	while (curr) {
		if (CMPRSS_EQ == cmp_cback(curr->dat, cmp_key)) {
			if (ret_first && !ret) {
				*prev = temp;
				return curr;
			}
			*prev = temp;
			ret = curr;
		}
		temp = curr;
		curr = curr->next;
	}
	return ret;
}

void* 
slist_get_max(slist_ct **head, slist_ct **prev, 
		status_ct (*cmp_cback)(void *, void *))
{
	if (!head || !(*head) || !prev || cmp_cback) {
		return NULL;
	}
	slist_ct *max = *head,
			 *curr = (*head)->next;
	while (curr) {
		if (CMPRSS_GREAT == cmp_cback(max->dat, curr->dat)) {
			max = curr;
		}
		curr = curr->next;
	}
	return max->dat;
}

// TODO Add support for multiple sorting algorithms
status_ct 
slist_sort(slist_ct **head, status_ct (*cmp_cback)(void *, void*))
{
	if (!head || !(*head) || !cmp_cback) {
		return CMPRSS_FAILURE;
	}
	// Sort
	slist_ct *lvla = *head,
			 *lvlb = NULL;
	void *temp_dat = NULL;
	while (lvla) {
		lvlb = lvla->next;
		while (lvlb) {
			if (CMPRSS_GREAT == cmp_cback(lvla->dat, lvlb->dat)) {
				temp_dat = lvla->dat;
				lvla->dat = lvlb->dat;
				lvlb->dat = temp_dat;
			}
			lvlb = lvlb->next;
		}
		lvla = lvla->next;
	}
	return CMPRSS_SUCCESS;
}

status_ct 
slist_delete_list(slist_ct **head, void (*del_cback)(void *), bool delete_dat)
{
	if (!head) {
		return CMPRSS_FAILURE;
	}
	slist_ct *curr = *head, 
			 *temp = NULL;
	while (curr) {
		temp = curr;
		curr = curr->next;
		if (delete_dat) {
			del_cback(temp->dat);
		}
		mem_free(temp);
	}
	*head = NULL;
	return CMPRSS_SUCCESS;
}

#ifdef CMPRSS_DEBUG
void 
slist_print(slist_ct **head, void (*print_cback)(void *))
{
	if (!head || !(*head)) {
		return;
	}
	slist_ct *curr = *head;
	while (curr) {
		print_cback(curr->dat);
		curr = curr->next;
	}
}
#endif
