/******************************************************************************
 * vmcs-sysfs.c - A module implementing a sysfs interface to the VMCS.
 *
 * Patrick Jarrold
 * CS544 Project
 * Oregon State University
 * Spring 2016
 *
 * Attempted inotify code borrowed from http://www.linuxjournal.com/article/8478
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/vmx.h>
#include <linux/slab.h>
#include <linux/inotify.h>
#include <linux/fsnotify_backend.h>

#define WATCH_EVENT_SIZE (sizeof (struct inotify_event))
#define WATCH_EVENT_BUF_LEN (1024 * (WATCH_EVENT_SIZE + 16))

u64 enc_guest_activity_state = 0x00004826;

static unsigned long guest_activity_state;
module_param(guest_activity_state, ulong, 0644);

int ifd;
int wd_guest_activity_state;

/*
 * vmcs_sysfs_init - the init function, called when the module is loaded.
 * Returns zero if successfully loaded, nonzero otherwise.
 */
static int vmcs_sysfs_init(void)
{
		//char watch_event_buf[WATCH_EVENT_BUF_LEN];
		//int len, i = 0;

		struct vmcs *curr_vmcs;

		asm volatile("VMPTRST %0" : "=m"(curr_vmcs));
		asm volatile("VMREAD %0, %1"
						: "=r"(guest_activity_state)
						: "r"(enc_guest_activity_state)
						);
		printk(KERN_INFO "In vmcs_sysfs_init, guest activity state = %lu\n",
						guest_activity_state);

		/*
		ifd = inotify_init();
		if (ifd < 0) {
				printk(KERN_ERR "In vmcs_sysfs_init, failed to init inotify.\n");
		} else {
				wd_guest_activity_state = inotify_add_watch(ifd,
								"/sys/module/vmcs_sysfs/parameters/guest_activity_state",
								IN_ACCESS);
				if (wd_guest_activity_state < 0) {
						printk(KERN_ERR "In vmcs_sysfs_init, failed to init inotify \
										watch for guest_activity_state");
				} else {
						len = read(ifd, watch_event_buf, WATCH_EVENT_BUF_LEN);
						if (len < 0) {
								printk(KERN_ERR "In vmcs_sysfs_init, inotify read failed.\n");
						}

						while (i < len) {
								struct inotify_event *watch_event;

								watch_event = (struct inotify_event *)&watch_event_buf[i];

								printk(KERN_INFO "wd=%d mask=%u cookie=%u len=%u\n",
												watch_event->wd, watch_event->mask,
												watch_event->cookie, watch_event->len);

								if (watch_event->len)
										printk(KERN_INFO "name=%s\n", event->name);

								i += WATCH_EVENT_SIZE + watch_event->len;
						}
				}
		}
		*/

		return 0;
}

/*
 * vmcs_sysfs_exit - the exit function, called when the module is removed.
 */
static void vmcs_sysfs_exit(void)
{
		//int ret;

		printk(KERN_INFO "In vmcs_sysfs_exit, guest activity state = %lu\n",
						guest_activity_state);

		/*
		ret = inotify_rm_watch(ifd, wd_guest_activity_state);
		if (ret) {
				printk(KERN_ERR "In vmcs_sysfs_exit, failed to shut down inotify.\n");
		}
		*/
}

module_init(vmcs_sysfs_init);
module_exit(vmcs_sysfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Jarrold");
MODULE_DESCRIPTION("A module implementing a sysfs interface to the VMCS.");
