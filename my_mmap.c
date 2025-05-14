#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timekeeping.h>

static int __init my_mmap_init(void) {
  struct timespec64 ts;
  struct tm tm;

  ktime_get_real_ts64(&ts);
  time64_to_tm(ts.tv_sec, 0, &tm);

  printk(KERN_INFO "Simple Module: Loaded at %02d:%02d %02d/%02d/%04ld\n",
         tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

  return 0;
}

static void __exit my_mmap_exit(void) {
  struct timespec64 ts;
  struct tm tm;

  ktime_get_real_ts64(&ts);
  time64_to_tm(ts.tv_sec, 0, &tm);

  printk(KERN_INFO "Simple Module: Unloaded at %02d:%02d %02d/%02d/%04ld\n",
         tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

module_init(my_mmap_init);
module_exit(my_mmap_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Test Author");
MODULE_DESCRIPTION("A simple kernel module for testing");
MODULE_DESCRIPTION("Custom mmap implementation using kernel APIs");
