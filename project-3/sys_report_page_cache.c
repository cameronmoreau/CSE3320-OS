#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/mmzone.h>
#include <linux/page-flags.h>
#include <asm/pgtable.h>

asmlinkage int sys_report_page_cache(void) {
  struct zone *zone;
  struct page *cached_page;
  struct zone_lru lru;
  int i;
  int active_pages = 0, inactive_pages = 0;
  int active_ref = 0, inactive_ref = 0;

  /* N^3 solution */
  for_each_zone(zone) {
    for_each_lru(i) {
      lru = zone->lru[i];
      printk("loop %i\n", i);
      list_for_each_entry(cached_page, &lru.list, lru) {
        printk("for each loop\n");
        if(i == LRU_ACTIVE_ANON || i == LRU_ACTIVE_FILE) {
          active_pages++;
          if(PageReferenced(cached_page)) active_ref++;
        } else {
          inactive_pages++;
          if(PageReferenced(cached_page)) inactive_ref++;
        }
      }
    }
  }

  /* Print stuff */
  printk("$$ - Printing Linux's Cache Money - $$\n");
  printk("==> Total Pages: %i\n", active_pages + inactive_pages);
  printk("==> # Active: %i\n", active_pages);
  printk("==> # Inactive: %i\n", inactive_pages);
  printk("==> # Active Referenced: %i\n", active_ref);
  printk("==> # Inactive Referenced: %i\n", inactive_ref);
  return 1;
}
