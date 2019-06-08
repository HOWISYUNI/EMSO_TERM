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

#include <linux/net.h>
#include <linux/socket.h>

#define KSF_NET "ksf_net"

static dev_t dev_num;
static struct cdev *cd_cdev;

/*
 * @GET | type           | data      | cmd           
 * 'l'  : light value    | time      | 'a' : average
 * 's'  : soil value     |           | 's' : sum
 * @PUT |
 * 'a'  : alert led      | time      | '1' : on
 * 'b'  : buzzer         |           | '0' : off
 * 'c'  : camera         |           |
 * 'l'  : led            |           |
 * 'm'  : motor          |           |
 * 'p'  : water pump     |           |
 * 's'  : sprinkler      |           |
 * @POST|
 * 'l'  : light value    | DATA      | NULL
 * 's'  : soil value     |           |
 * 'a'  : alert info     |           |
 */

struct request{
    char method;
    char type;
    char cmd;
    size_t len;
    void *data;
};

/*
 *  type            | data
 *  's' : Success   | GET  : data
 *  'f' : Failure   | PUT  : result
 *  't' : Timeout   | POST : result
 */
struct response{
    char type;
    size_t len;
    void *data;
};

struct 

/* Socket init
 * return socket
 */
static int ksf_net_open(struct inode *inode, struct file *file);

/* Socket close
 * return result
 */
static int ksf_net_release(struct inode *inode, struct file *file);

/* ICOTL 1 : Server Init
 * IOCTL 2 : Client Init
 */
static long ksf_net_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

/* Send data
 * return result
 */
static int ksf_net_read(struct file *file, char *buf, size_t len, loff_t *loff);

/* receive data
 * return result
 */
static int ksf_net_write(struct file *file, const char *buf, size_t len, loff_t *loff);

