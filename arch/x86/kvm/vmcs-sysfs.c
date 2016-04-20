/******************************************************************************
 * vmcs-sysfs.c - A module implementing a sysfs interface to the VMCS.
 *
 * Patrick Jarrold
 * CS544 Project
 * Oregon State University
 * Spring 2016
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int self_destruct = 0;			/* default to off */
module_param(self_destruct, bool, 0644);	/* a Boolean type */

/*
 * vmcs_sysfs_init - the init function, called when the module is loaded.
 * Returns zero if successfully loaded, nonzero otherwise.
 */
static int vmcs_sysfs_init(void)
{
	printk(KERN_INFO "In init, self destruct = %d\n", self_destruct);
	return 0;
}

/*
 * vmcs_sysfs_exit - the exit function, called when the module is removed.
 */
static void vmcs_sysfs_exit(void)
{
	printk(KERN_INFO "In exit, self destruct = %d\n", self_destruct);
}

module_init(vmcs_sysfs_init);
module_exit(vmcs_sysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Jarrold");
MODULE_DESCRIPTION("A module implementing a sysfs interface to the VMCS.");
