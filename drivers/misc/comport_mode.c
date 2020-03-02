#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
//#define IMX_GPIO_NR(bank, nr)		(((bank) - 1) * 32 + (nr))

#define SABRESD_COM3_MODE_0	   IMX_GPIO_NR(1, 4)
#define SABRESD_COM3_MODE_1	   IMX_GPIO_NR(1, 5)
#define SABRESD_COM3_TERM	       IMX_GPIO_NR(7, 11)

#define MODE_RS232_CMD          66
#define MODE_RS422_CMD          67
#define MODE_RS485_CMD          68
#define MODE_RS422TERM_CMD      69
#define MODE_RS485TERM_CMD      70
#define MODE_LOOPBACK_CMD       71
#define MODE_READ_TYPE          72

static int priv_mode=MODE_RS232_CMD;
static int curr_mode=MODE_RS232_CMD;

static ssize_t curr_mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", curr_mode);
}

static ssize_t curr_mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	priv_mode=curr_mode;
	sscanf(buf, "%du", &curr_mode);
	switch ( curr_mode ) {
		case MODE_RS232_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 0);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_RS232_CMD:%d\n",curr_mode);
			break;
		case MODE_RS422_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("MODE_RS422_CMD:%d\n",curr_mode);
			break;
		case MODE_RS485_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_RS232_CMD:%d\n",curr_mode);
			break;
		case MODE_RS422TERM_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 1);
			//printk("MODE_RS422TERM_CMD:%d\n",curr_mode);
			break;
		case MODE_RS485TERM_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 1);
			//printk("MODE_RS485TERM_CMD:%d\n",curr_mode);
			break;
		case MODE_LOOPBACK_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 0);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("MODE_LOOPBACK_CMD:%d\n",curr_mode);
			break;
		default:
			curr_mode=priv_mode;
			printk("RS232/RS485/RS422 control error.default(%d)\n",curr_mode);
			printk("MODE_RS232_CMD          66\n");
			printk("MODE_RS422_CMD          67\n");
			printk("MODE_RS485_CMD          68\n");
			printk("MODE_RS422TERM_CMD      69\n");
			printk("MODE_RS485TERM_CMD      70\n");
			printk("MODE_LOOPBACK_CMD       71\n");
			return -1;
			break;
	}
	return count;
}

static ssize_t priv_mode_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", priv_mode);
}

static ssize_t priv_mode_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
	sscanf(buf, "%du", &curr_mode);
	return count;
}

static struct kobj_attribute curr_mode_attribute =
	__ATTR(curr_mode, 0664, curr_mode_show, curr_mode_store);

static struct kobj_attribute priv_mode_attribute =
	__ATTR(priv_mode, 0664, priv_mode_show, priv_mode_store);

static struct attribute *attrs[] = {
	&curr_mode_attribute.attr,
	&priv_mode_attribute.attr,
	NULL,	/* need to NULL terminate the list of attributes */
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *comportmode_kobj;

static int comportmode_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int comportmode_close(struct inode *inode, struct file *file)
{
    return 0;
}

static ssize_t comportmode_read(struct file *file,
                        char __user *buf,
                        size_t count,
                        loff_t *pos)
{
    return 0;
}

static long comportmode_ioctl(struct file * file, unsigned int cmd, unsigned long arg) {

	switch ( cmd ) {
		case MODE_RS232_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 0);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_RS232_CMD");
			priv_mode=cmd;
			break;
		case MODE_RS485_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_RS485_CMD");
			priv_mode=cmd;
			break;
		case MODE_RS485TERM_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 1);
			//printk("TEST_RS485_CMD");
			priv_mode=cmd;
			break;
		case MODE_RS422_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_RS422_CMD");
			priv_mode=cmd;
			break;
		case MODE_RS422TERM_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 1);
			gpio_direction_output(SABRESD_COM3_MODE_1, 1);
			gpio_direction_output(SABRESD_COM3_TERM, 1);
			//printk("TEST_RS422_CMD");
			priv_mode=cmd;
			break;
		case MODE_LOOPBACK_CMD :
			gpio_direction_output(SABRESD_COM3_MODE_0, 0);
			gpio_direction_output(SABRESD_COM3_MODE_1, 0);
			gpio_direction_output(SABRESD_COM3_TERM, 0);
			//printk("TEST_LOOPBACK_CMD");
			priv_mode=cmd;
			
			break;
		default:
			printk("RS232/RS485/RS422 control error.\n");
			return -1;
		case MODE_READ_TYPE :
			break;
	}
	return priv_mode;
}

struct file_operations fops = {
    .owner      = THIS_MODULE,
    .open       = comportmode_open,
    .release    = comportmode_close,
    .read       = comportmode_read,
	.unlocked_ioctl = comportmode_ioctl,
};

struct miscdevice misc = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "com_mode",
    .fops   = &fops,
};

int __init comportmode_init(void)
{
    int ret;

	ret = gpio_request(SABRESD_COM3_MODE_0, "com3_mode_0");
	if ( ret ) {
        printk("get com3_mode_0 gpio FAILED!\n");
		return ret;
	}

	ret = gpio_request(SABRESD_COM3_MODE_1, "com3_mode_1");
	if ( ret ) {
		gpio_free(SABRESD_COM3_MODE_0);
        printk("get com3_mode_1 gpio FAILED!\n");
		return ret;
	}

	ret = gpio_request(SABRESD_COM3_TERM, "term");
	if ( ret ) {
		gpio_free(SABRESD_COM3_MODE_0);
		gpio_free(SABRESD_COM3_MODE_1);
        printk("get com3_term gpio FAILED!\n");
		return ret;
	}

	gpio_direction_output(SABRESD_COM3_MODE_0, 1);
	gpio_direction_output(SABRESD_COM3_MODE_1, 0);
	gpio_direction_output(SABRESD_COM3_TERM, 0);

    ret = misc_register(&misc);
    if(ret)
        printk("RS232_misc_register FAILED!\n");

	comportmode_kobj = kobject_create_and_add("comportmode", kernel_kobj);
	if (!comportmode_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	ret = sysfs_create_group(comportmode_kobj, &attr_group);
	if (ret)
		kobject_put(comportmode_kobj);

    return ret;
}


void __exit comportmode_exit(void)
{
	gpio_direction_output(SABRESD_COM3_MODE_0, 0);
	gpio_direction_output(SABRESD_COM3_MODE_1, 0);
	gpio_direction_output(SABRESD_COM3_TERM, 0);
	gpio_free(SABRESD_COM3_MODE_0);
	gpio_free(SABRESD_COM3_MODE_1);
	gpio_free(SABRESD_COM3_TERM);

	kobject_put(comportmode_kobj);
    misc_deregister(&misc);
}


module_init(comportmode_init);
module_exit(comportmode_exit);

MODULE_LICENSE("GPL");

