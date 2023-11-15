// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Tiniakova Kseniia <ksenpati@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct my_data {
struct list_head list;
ktime_t timestamp;
};

static LIST_HEAD(my_list);

static unsigned int hello_count = 1;

module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!' (default=1)");

static int __init hello_init(void)
{
struct my_data *data;
int i;

	if (hello_count == 0 || (hello_count < 10 && hello_count > 5))
		printk(KERN_WARNING "Warning! It`s better to use another value!");
	else if (hello_count > 10)
		BUG_ON(1);
	for (i = 0; i < hello_count; ++i) {
		data = kmalloc(sizeof(struct my_data), GFP_KERNEL);
		if (!data)
			BUG_ON(1);
		if (i == hello_count - 1)
			BUG_ON(1);
		data->timestamp = ktime_get();
		INIT_LIST_HEAD(&data->list);
		list_add(&data->list, &my_list);
		printk(KERN_INFO "Hello, world!\n");
	}

return 0;
}

static void __exit hello_exit(void)
{
struct my_data *data, *temp;
ktime_t delta;

list_for_each_entry_safe(data, temp, &my_list, list) {
	delta = ktime_sub(ktime_get(), data->timestamp);
	printk("Time elapsed: %lld ns\n", (long long)ktime_to_ns(delta));
	list_del(&data->list);
	kfree(data);
}

printk(KERN_INFO "Goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);
