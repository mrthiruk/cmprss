#ifndef _SLIST_H_
#define _SLIST_H_

typedef struct slist_ct slist_ct;
struct slist_ct {
	void *dat;
	struct slist_ct *next;
};

status_ct slist_insert_at_tail(slist_ct **head, void *data);

status_ct slist_insert_at_head(slist_ct **head, void *data);

status_ct slist_insert_after(slist_ct **head, void *data, 
		status_ct (*cmp_cback)(void *, void *));

status_ct slist_delete(slist_ct **head, void *cmp_key, 
		status_ct (*cmp_cback)(void *, void *), 
		void (*del_cback)(void *), bool delete_dat, bool delete_first);

slist_ct* slist_search(slist_ct **head, slist_ct **prev, void *cmp_key,
		status_ct (*cmp_cback)(void *, void *), bool find_first);

void* slist_get_max(slist_ct **head, slist_ct **prev, 
		status_ct (*cmp_cback)(void *, void *));

void* slit_get_min(slist_ct **head, slist_ct **prev, 
		status_ct (*cmp_cback)(void *, void *));

status_ct slist_sort(slist_ct **head, status_ct (*cmp_cback)(void *, void *));

status_ct slist_delete_list(slist_ct **head, 
		void (*del_cback)(void *), bool delete_dat);

#ifdef CMPRSS_DEBUG
void slist_print(slist_ct **head, void (*print_cback)(void *));
#endif

#endif
