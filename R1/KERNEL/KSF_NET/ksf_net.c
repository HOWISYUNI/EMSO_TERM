/* KU Smart Farm - Network - Data Communication - REST API
 * Msg    : @Request @Response
 * Method : @GET @POST @PUT
 * 
 */
#include "ksf_net.h"

/* create a socket */
static int ksf_net_open(struct inode *inode, struct file *file){
    int err;    

    if ( ( (err = sock_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &sock)) < 0) ||
         ( (err = sock_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &sock_send)) < 0 )) {
            printk(KERN_INFO KSF_NET": Could not create a datagram socket, error = %d\n", -ENXIO);
            return -1;
    }

    memset(&addr, 0, sizeof(struct sockaddr));
    memset(&addr_send, 0, sizeof(struct sockaddr));
    addr.sin_family      = AF_INET;
    addr_send.sin_family = AF_INET;

    addr.sin_addr.s_addr      = htonl(INADDR_ANY);
    addr_send.sin_addr.s_addr = htonl(INADDR_SEND);

    addr.sin_port      = htons(DEFAULT_PORT);
    addr_send.sin_port = htons(CONNECT_PORT);
    
    if ( ( (err = sock->ops->bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr) ) ) < 0) ||
           (err = sock_send->ops->connect(sock_send, (struct sockaddr *)&addr_send, sizeof(struct sockaddr), 0) < 0 )){
            printk(KERN_INFO KSF_NET": Could not bind or connect to socket, error = %d\n", -err);
            sock_release(sock);
            sock_release(sock_send);
            return -1;
    }

    return 0;
}

static int ksf_net_release(struct inode *inode, struct file *file){
    sock_release(sock);
    sock = NULL;

    printk(KERN_INFO KSF_NET": socket released\n");
    return 0;
}


static int ksf_net_read(struct file *file, char *buf, size_t len, loff_t *loff){
    struct msghdr msg;      /* Msg */
    struct iovec iov;       /* Data */
    int size = 0;
    unsigned long nr_segments = 1;
    size_t count = 1;

    if (sock->sk==NULL) 
        return 0;

    /* msg set */
    msg.msg_flags = 0;
    msg.msg_name = &addr;            /* Socket name */
    msg.msg_namelen  = sizeof(struct sockaddr_in);
    msg.msg_control = NULL;         /* (void*)msg Control */
    msg.msg_controllen = 0;
    /* Data set */
    iov.iov_base = buf;
    iov.iov_len = len;
    iov_iter_init(&msg.msg_iter, READ, &iov, nr_segments, count);
    /* receive msg */
    size = sock_recvmsg(sock, &msg, msg.msg_flags);

    return size;
}

static int ksf_net_write(struct file *file, const char *buf, size_t len, loff_t *loff){
    struct msghdr msg;
    struct iovec iov;
    int size = 0;
    void *k_buf;
    int ret;
    unsigned long nr_segments = 1;
    size_t count = 1;
    
    if(sock->sk == NULL)
        return 0;

    /* Msg Set */
    msg.msg_flags = 0;
    msg.msg_name = &addr;            /* Socket name */
    msg.msg_namelen  = sizeof(struct sockaddr_in);
    msg.msg_control = NULL;         /* (void*)msg Control */
    msg.msg_controllen = 0;
    /* Copy Data from user */
    k_buf = (void*)kmalloc(sizeof(len), GFP_KERNEL);
    ret = copy_from_user(k_buf, buf, len);
    if(ret < 0)
        return -1;
    /* Data set */
    iov.iov_base = k_buf;
    iov.iov_len = len;
    iov_iter_init(&msg.msg_iter, READ, &iov, nr_segments, count);
    /* Send msg */
    size = sock_sendmsg(sock, &msg);

    kfree(k_buf);
    return size;
}

struct file_operations ksf_net_fops =
{
	.read = ksf_net_read,
	.write = ksf_net_write,
	/* .unlocked_ioctl = ksf_net_ioctl, */
	.open = ksf_net_open,
	.release = ksf_net_release
};

static int __init ksf_net_init(void){

    /* Character Device init */
	alloc_chrdev_region(&dev_num, 0, 1, KSF_NET);
	cd_cdev = cdev_alloc();
	cdev_init(cd_cdev, &ksf_net_fops);
	cdev_add(cd_cdev, dev_num, 1);
	
    return 0;
}

static void __exit ksf_net_exit(void){

    /* Character Device free */
	cdev_del(cd_cdev);
	unregister_chrdev_region(dev_num, 1);
	
}


module_init(ksf_net_init);
module_exit(ksf_net_exit);
