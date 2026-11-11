#include <net/sock.h>
#include <linux/qos_type.h>
#include <ecnt_hook/ecnt_hook.h>

static struct qos_action qa[MAX_RULE_NUM];

int qostype_chk(int chk_type, int rule_no, char *wan_if, int rtp_match)
{
	struct qos_action *pqa = NULL;
	char value[MAX_BUF_LEN];
	char *pval = NULL;
	char *p = NULL;
	
	if (rule_no < 0 || rule_no > MAX_RULE_NUM - 1) {
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return -1;
	}

	pqa = qa + rule_no;
	
	if (chk_type == EBT_CHK_TYPE) {
		if (!strcmp(pqa->qm[0].type_name, "wan_if") || !strcmp(pqa->qm[1].type_name, "rtp_proto")) {
			return 0;
		}
		else {
			return -1;
		}
	}
	
	if (wan_if == NULL) {
		return -1;
	}

	if (!strcmp(pqa->qm[0].type_name, "wan_if")) {
		strcpy(value, pqa->qm[0].type_value);
		/* check if wan interface is in group */
		pval = value;
		while ((p = strsep(&pval, ",")) != NULL) {
			if (!strcmp(p, wan_if)) {
				goto rtp_proto_handle;
			}
		}
		return -1;
	}

rtp_proto_handle:
	if ( (strcmp(pqa->qm[1].type_name, "rtp_proto") != 0) || 
		 (!strcmp(pqa->qm[1].type_name, "rtp_proto") && (1 == rtp_match)) ) {
		return 0;
	}

	return -1;
}

#if defined(TCSUPPORT_CT_QOS)
int qostype_get(int rule_no, char *wan_if, int *p_mark)
{
	int idx = 0;
	int isQueueWanset = 0;
	int queue_idx = 0;
	
	if ( rule_no < 0 || rule_no > MAX_RULE_NUM - 1)
	{
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return 0;
	}

	if ( !wan_if || !p_mark )
		return 0;

	/*Check waninterface fail, looking for other waninterface qos rules. 
	However, it can't check the rules of other types which checked by ebtables.
	So,  the waninterface rule can't be combined with other rules.*/
	for ( idx=0; idx<MAX_RULE_NUM; idx++ )
	{
	    if ( 0 == qa[idx].qm[0].type_name[0] )
	        continue;

		queue_idx = (qa[idx].qm[0].type_mask & QOSTYPE_QUEUE_INDEX_MARK)
						>> QOSTYPE_QUEUE_INDEX_OFFSET;

	    if ( 0 == strcmp(qa[idx].qm[0].type_name, "wan_if") )
	    {
	    	if ( 0 == isQueueWanset
				&& queue_idx == rule_no )
				isQueueWanset = 1; /* queue match */

	        if ( 0 == strcmp(qa[idx].qm[0].type_value, wan_if) )
			{
				*p_mark = qa[idx].qm[0].type_mask;
	            return queue_idx;
	    	}
		}
	}

	/* wan type in queue, but not match */
	if ( 1 == isQueueWanset )
		return -1;
	else
		return 0;
}

int qostype_wan_check(int rule_no, struct net_device *dev, int *p_mark)
{
	if ( dev->priv_flags & IFF_OSMUX )
	{
		return qostype_get(rule_no, dev->name, p_mark);
	}

	return 0;
}

int qos_wan_interface_hook(struct sk_buff *skb)
{
	int queue_num = 0;
	int ret_qoswan = 0;
	int qos_type_mark = 0;
	struct net_device *dev = NULL;

	if ( NULL == skb || NULL== skb->dev )
		return ECNT_CONTINUE;

	dev = skb->dev;
	queue_num = (skb->mark & QOS_FILTER_MARK) >> 4;
	if ( queue_num > 0
		&& (skb->mark & 0xf0000000) )
	{
		ret_qoswan = qostype_wan_check(queue_num, dev, &qos_type_mark);
		if ( 0 != ret_qoswan )			
		{
			skb->mark &= (~QOS_FILTER_MARK);
			skb->mark &= (~QOSTYPE_8021P_MARK);
			if( ret_qoswan > 0 )
			{
				skb->mark |= (ret_qoswan << 4);
				skb->mark |= (qos_type_mark & QOSTYPE_8021P_MARK);
			}
		}
	}

	return ECNT_CONTINUE;
}
#endif

int set_tos(int rule_no, unsigned int tos)
{
	struct qos_action *pqa = NULL;
	if (rule_no < 0 || rule_no >= MAX_RULE_NUM) {
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return -1;
	}

	pqa = &qa[rule_no];

	pqa->dscp_flag = 1;
	pqa->dscp = tos;
	return 0;
}

int unset_tos(int rule_no)
{
	struct qos_action *pqa = NULL;
	if (rule_no < 0 || rule_no >= MAX_RULE_NUM) {
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return -1;
	}

	pqa = &qa[rule_no];

	pqa->dscp_flag = 0;

	return 0;
}

int get_tos(int rule_no, unsigned int *tos)
{
	struct qos_action *pqa = NULL;
	if (rule_no < 0 || rule_no >= MAX_RULE_NUM) {
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return -1;
	}

	pqa = &qa[rule_no];

	if (0 == pqa->dscp_flag) {
		return -1;
	}

	*tos = pqa->dscp;

	return 0;
}

static int qostype_settype(struct qos_type *pqt)
{
	int rule_no = pqt->rule_no;
	if (rule_no < 0 || rule_no > MAX_RULE_NUM - 1) {
		printk("%s:rule no should be between 0 and %d.\n", __FUNCTION__, MAX_RULE_NUM - 1);
		return -1;
	}

	memcpy(qa[pqt->rule_no].qm, pqt->qm, sizeof(struct qos_match)*2);

	return 0;
}

int
qostype_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct qos_type qt;
	
	switch (cmd) {
	case QOSTYPE_IOC_SET_TYPE:
		if (copy_from_user(&qt, (struct qos_type*)arg, sizeof(qt))) {
			return -EFAULT;
		}
		qostype_settype(&qt);
		break;
	default:
		break;
	}

	return 0;
}

int qostype_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static struct file_operations qostype_fops = {
	.owner =		THIS_MODULE,
	.write =		NULL,
	.read =			NULL,
	.unlocked_ioctl =		qostype_ioctl,
	.open =			qostype_open,
	.release =		NULL,
};

/***************************************************************************
 * Function Name: qostype_drv_init
 * Description  : Initialization of qostype driver
 * Returns      : 0
 ***************************************************************************/
static int __init qostype_drv_init(void)
{
	int status = 0;
	
	/* qostype ioctl */
	status = register_chrdev(QOSTYPE_MAJOR, "qostype", &qostype_fops);
	if (status < 0)
		return status;
	
	memset(qa, 0, sizeof(qa));

  	return 0;
}


/*_______________________________________________________________________
** Function Name: qostype_drv_exit
** Description  : qostype module clean routine
** Returns      : None
**_______________________________________________________________________
*/
static void __exit qostype_drv_exit(void)
{
	unregister_chrdev(QOSTYPE_MAJOR, "qostype");
}

EXPORT_SYMBOL(qostype_chk);
EXPORT_SYMBOL(set_tos);
EXPORT_SYMBOL(unset_tos);

module_init(qostype_drv_init);
module_exit(qostype_drv_exit);

