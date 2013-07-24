/* Necessary includes for device drivers */
#include <linux/init.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
//#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of meuDriver.c functions */
int meuDriver_open(struct inode *inode, struct file *filp);
int meuDriver_release(struct inode *inode, struct file *filp);
ssize_t meuDriver_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t meuDriver_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void meuDriver_exit(void);
int meuDriver_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations meuDriver_fops = {
  read: meuDriver_read,
  write: meuDriver_write,
  open: meuDriver_open,
  release: meuDriver_release
};

/* Declaration of the init and exit functions */
module_init(meuDriver_init);
module_exit(meuDriver_exit);

/* Global variables of the driver */
/* Major number */
int meuDriver_major = 60;
/* Buffer to store data */
char *meuDriver_buffer;


int meuDriver_init(void) {
  int result;

  /* Registering device */
  result = register_chrdev(meuDriver_major, "meuDriver", &meuDriver_fops);
  if (result < 0) {
    printk(
      "<1>meuDriver: cannot obtain major number %d\n", meuDriver_major);
    return result;
  }

  /* Allocating meuDriver for the buffer */
  meuDriver_buffer = kmalloc(60, GFP_KERNEL); 
  if (!meuDriver_buffer) { 
    result = -ENOMEM;
    goto fail; 
  } 
  memset(meuDriver_buffer, 0, 1);

  printk("<1>Inserting meuDriver module\n"); 
  return 0;

  fail: 
    meuDriver_exit(); 
    return result;
}

void meuDriver_exit(void) {
  /* Freeing the major number */
  unregister_chrdev(meuDriver_major, "meuDriver");

  /* Freeing buffer meuDriver */
  if (meuDriver_buffer) {
    kfree(meuDriver_buffer);
  }

  printk("<1>Removing meuDriver module\n");

}

int meuDriver_open(struct inode *inode, struct file *filp) {

  /* Success */
  return 0;
}

int meuDriver_release(struct inode *inode, struct file *filp) {
 
  /* Success */
  return 0;
}

ssize_t meuDriver_read(struct file *filp, char *buf, 
                    size_t count, loff_t *f_pos) { 
 
  /* Transfering data to user space */ 
  copy_to_user(buf,meuDriver_buffer,1);

  /* Changing reading position as best suits */ 
  if (*f_pos == 0) { 
    *f_pos+=1; 
    return 1; 
  } else { 
    return 0; 
  }
}

ssize_t meuDriver_write( struct file *filp, char *buf,
                      size_t count, loff_t *f_pos) {


  *buf = 'V';
  
  copy_from_user(meuDriver_buffer,buf,count);
  
  printk("write meuDriver_buffer: %c\n", *meuDriver_buffer);
  
  return 1;
}







