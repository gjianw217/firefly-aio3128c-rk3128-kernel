#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/rockchip/common.h>
#include <linux/rockchip/iomap.h>

static unsigned long system_status = 0;
static unsigned long ref_count[32] = {0};
static DEFINE_MUTEX(system_status_mutex);

static BLOCKING_NOTIFIER_HEAD(rk_system_status_chain_head);

static int fire_ver = -1;

int rockchip_register_system_status_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_register(&rk_system_status_chain_head, nb);
}
EXPORT_SYMBOL_GPL(rockchip_register_system_status_notifier);

int rockchip_unregister_system_status_notifier(struct notifier_block *nb)
{
	return blocking_notifier_chain_unregister(&rk_system_status_chain_head, nb);
}
EXPORT_SYMBOL_GPL(rockchip_unregister_system_status_notifier);

static int rockchip_system_status_notifier_call_chain(unsigned long val)
{
	int ret = blocking_notifier_call_chain(&rk_system_status_chain_head, val, NULL);

	return notifier_to_errno(ret);
}

int rockchip_set_system_status(unsigned long status)
{
	unsigned long old_system_status;
	unsigned int single_status_offset;

	mutex_lock(&system_status_mutex);

	old_system_status = system_status;

	while (status) {
		single_status_offset = fls(status) - 1;
		status &= ~(1<<single_status_offset);
		if (ref_count[single_status_offset] == 0) {
			system_status |= 1 << single_status_offset;
		}
		ref_count[single_status_offset]++;
	}
	if (old_system_status != system_status)
		rockchip_system_status_notifier_call_chain(system_status);

	mutex_unlock(&system_status_mutex);
	return 0;
}

int rockchip_clear_system_status(unsigned long status)
{
	unsigned long old_system_status;
	unsigned int single_status_offset;
	mutex_lock(&system_status_mutex);

	old_system_status = system_status;

	while (status) {
		single_status_offset = fls(status) - 1;
		status &= ~(1<<single_status_offset);
		if (ref_count[single_status_offset] == 0) {
			continue;
		} else {
			if (ref_count[single_status_offset] == 1) {
				system_status &= ~(1<<single_status_offset);
			}
			ref_count[single_status_offset]--;
		}
	}
	if (old_system_status != system_status)
		rockchip_system_status_notifier_call_chain(system_status);

	mutex_unlock(&system_status_mutex);

	return 0;
}

unsigned long rockchip_get_system_status(void)
{
	unsigned long ret;

	mutex_lock(&system_status_mutex);
	ret = system_status;
	mutex_unlock(&system_status_mutex);

	return ret;
}


enum fireprime_version fireprime_get_version(void)
{
	u32 reg_val;

	if(fire_ver < 0)
	{
		reg_val = *(((u32 *)RK_GRF_VIRT) + 0x1cc/4);
		if((3 == ((reg_val >> 13) & 0x7)))
			fire_ver = FIREPRIME_VERSION_V01;
		else
			fire_ver = FIREPRIME_VERSION_V00;
		printk("FirePrime hardware version: V%02x\n", fire_ver);
	}

	return fire_ver;
}
