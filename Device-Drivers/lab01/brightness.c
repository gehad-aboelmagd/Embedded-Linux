#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/gpio.h>

#define LED_PIN     529

ssize_t led_get(struct file *file, char __user *user, size_t size, loff_t *off);
ssize_t	led_set(struct file *file, const char __user *user, size_t size, loff_t *off);

struct proc_ops led_ops = {
    .proc_read = led_get,
    .proc_write = led_set,
};

struct proc_dir_entry *proc_dir;
static char led_state[2] = "0";

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gehad");

__init static int led_init(void)
{    
    if (!gpio_is_valid(LED_PIN)) {
        return -EINVAL;
    }
    if (gpio_request(LED_PIN, "led_driver") < 0) {
        return -EBUSY;
    }
    gpio_direction_output(LED_PIN, 0);

    proc_dir = proc_create("brightness", 0666, NULL, &led_ops);
    if (!proc_dir) {
        gpio_free(LED_PIN);
        return -ENOMEM;
    }

    printk("inserting led module...\n");
    return 0;
}

ssize_t led_get(struct file *file, char __user *user, size_t size, loff_t *off)
{
    if(*off > 0)
        return 0;

    if(copy_to_user(user, led_state, 2))
        return -EFAULT;
        
    printk("led value = %s\n", led_state);

    *off += 2;
    return 2;
}

ssize_t	led_set(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    if(size != 2) 
    {
        printk("Invalid value to set the led!\n");
        return -EDOM;
    }

    if(copy_from_user(led_state, user, size))
    {
        return -EFAULT;
    }

    led_state[1] = '\0';
    switch (led_state[0])
    {
    case '0':
        gpio_set_value(LED_PIN, 0);
        break;

    case '1':
        gpio_set_value(LED_PIN, 1);
        break;

    default:
        printk("Invalid value to set the led\n");
        return -EDOM;
        break;
    }

    return size;
}

__exit static void led_deinit(void)
{
    printk("removing led module...\n");
    gpio_free(LED_PIN);
    proc_remove(proc_dir);
}

module_init(led_init);
module_exit(led_deinit);

