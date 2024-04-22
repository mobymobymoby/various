#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <asm/pgtable.h>
#include <linux/mm_types.h>

MODULE_LICENSE("GPL");

static struct dentry *dir, *output;
static struct task_struct *task;

struct packet {
        pid_t pid;
        unsigned long vaddr;
        unsigned long paddr;
};

static ssize_t read_output(struct file *fp,
                        char __user *user_buffer,
                        size_t length,
                        loff_t *position)
{
        // Implement read file operation
        struct packet kpacket;
        int i, j;
        char *ptr;
        copy_from_user(&kpacket, user_buffer, sizeof(kpacket));
        struct pid *pid = find_vpid(3566139);
        if (pid == NULL)
        {
                goto err;
        }

        unsigned long va = kpacket.vaddr;
        task = pid_task(pid, PIDTYPE_PID);
        printk("%lp\n", 0xffffffffa8400010ULL);
        for (i = 0; i < 0x20; i++) {
                ptr = (char*)(0xffffffffa8400010ULL + i * 8);
                printk("%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx\n", 
                        ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]);
        }
err:
        return 0;
}

static const struct file_operations dbfs_fops = {
        // Mapping file operations with your functions
        .read = read_output
};

static int __init dbfs_module_init(void)
{
        // Implement init module

        dir = debugfs_create_dir("paddr", NULL);

        // Fill in the arguments below
        output = debugfs_create_file("output", 0777, dir, NULL, &dbfs_fops);

	printk("dbfs_paddr module initialize done\n");

        return 0;
}

static void __exit dbfs_module_exit(void)
{
        // Implement exit module

	printk("dbfs_paddr module exit\n");
        debugfs_remove_recursive(dir);
}

module_init(dbfs_module_init);
module_exit(dbfs_module_exit);
