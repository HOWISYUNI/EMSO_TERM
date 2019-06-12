/* KU Smart Farm - Network - Data Communication - REST API
 * Msg    : @Request @Response
 * Method : @GET @POST @PUT
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
/* kernel socket programming */
#include <linux/net.h>
#include <linux/socket.h>
#include <linux/uio.h>
#include <linux/ip.h>
#include <linux/in.h>

#define KSF_NET "ksf_net"

#define DEFAULT_PORT 2325   /* Src */
#define CONNECT_PORT 23     /* Dest */
//#define INADDR_SEND ((unsigned long int)0x7f000001) /* 127.0.0.1 */
#define INADDR_SEND INADDR_LOOPBACK

static dev_t dev_num;
static struct cdev *cd_cdev;
/* src */
static struct socket *sock;
static struct sockaddr_in addr;
/* dest */
static struct socket *sock_send;
static struct sockaddr_in addr_send;

/* create socket */
static int ksf_net_open(struct inode *inode, struct file *file);

/* release socket */
static int ksf_net_release(struct inode *inode, struct file *file);

/*  */
//static long ksf_net_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Send data */
static int ksf_net_read(struct file *file, char *buf, size_t len, loff_t *loff);

/* receive data */
static int ksf_net_write(struct file *file, const char *buf, size_t len, loff_t *loff);

