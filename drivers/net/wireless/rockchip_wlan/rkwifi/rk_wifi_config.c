/* rk_wifi_config.c
 *
 * RKWIFI driver version.
 *
 * Define the firmware and nvram path
 *
 * Define default Country Code
 *
 * gwl @ Rockchip
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/rfkill-wlan.h>

/* 
 * Set Firmware Path
 */
 
#define ANDROID_FW_PATH "/system/etc/firmware/"

extern int get_wifi_chip_type(void);
int rkwifi_set_firmware(char *fw, char *nvram)
{
    int chip = get_wifi_chip_type();
    
if (chip == WIFI_RK903) {
	sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK903b2.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_RK903_26M.cal");
}

if (chip == WIFI_RK901) {
	sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK901.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_RK901.txt");
}

#ifdef CONFIG_BCM4330
	sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm4330.bin");
#ifdef CONFIG_RK_CHECK_UACCESS
    sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_4330_oob.txt");
#else
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_4330.txt");
#endif
#endif

if (chip == WIFI_AP6181) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK901.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6181.txt");
}

if (chip == WIFI_AP6210) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK901.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6210.txt");
}

if (chip == WIFI_AP6212) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm43438a0.bin");
        sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_ap6212.txt");
}

if (chip == WIFI_AP6212A) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm43438a1.bin");
    sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_ap6212a.txt");
}

if (chip == WIFI_AP6234) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm43341b0_ag.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6234.txt");
}

if (chip == WIFI_AP6441) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm43341b0_ag.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6441.txt");
}

if (chip == WIFI_AP6335) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm4339a0_ag.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6335.txt");
}

if (chip == WIFI_AP6354) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_bcm4354a1_ag.bin");
        sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_ap6354.txt");
}

if (chip == WIFI_AP6476) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK901.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6476.txt");
}

if (chip == WIFI_AP6493) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK903.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6493.txt");
}

if (chip == WIFI_AP6330) {
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK903_ag.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_AP6330.txt");
}

#ifdef CONFIG_GB86302I
    sprintf(fw, "%s%s", ANDROID_FW_PATH, "fw_RK903_ag.bin");
	sprintf(nvram, "%s%s", ANDROID_FW_PATH, "nvram_GB86302I.txt");
#endif
	return 0;
}

EXPORT_SYMBOL(rkwifi_set_firmware);
