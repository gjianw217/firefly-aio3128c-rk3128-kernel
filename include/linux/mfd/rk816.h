/* include/linux/regulator/rk816.h
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __LINUX_REGULATOR_rk816_H
#define __LINUX_REGULATOR_rk816_H

#include <linux/gpio.h>
#include <linux/regulator/machine.h>
#include <linux/wakelock.h>
#include <linux/power_supply.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/of_regulator.h>
#include <linux/mfd/core.h>
#include <linux/regmap.h>
#include <linux/syscore_ops.h>
#include <linux/irq.h>
#include <linux/iio/iio.h>
#include <linux/iio/machine.h>
#include <linux/iio/driver.h>
#include <linux/iio/consumer.h>

/*************************** RK805 ********************************************/
/*INTERRUPT REGISTER*/
#define RK805_INT_STS_REG			0x4C
#define RK805_INT_STS_MSK_REG			0x4D
#define RK805_GPIO_IO_POL_REG			0x50
#define RK805_OUT_REG				0x52
#define RK805_ON_SOURCE_REG			0xAE
#define RK805_OFF_SOURCE_REG			0xAF

/*POWER CHANNELS ENABLE REGISTER*/
#define RK805_DCDC_EN_REG			0x23
#define RK805_SLP_DCDC_EN_REG			0x25
#define RK805_SLP_LDO_EN_REG			0x26
#define RK805_LDO_EN_REG			0x27

/*CONFIG REGISTER*/
#define RK805_THERMAL_REG			0x22

/*BUCK AND LDO CONFIG REGISTER*/
#define RK805_BUCK_LDO_SLP_LP_EN_REG		0x2A
#define RK805_BUCK1_CONFIG_REG			0x2E
#define RK805_BUCK1_ON_VSEL_REG			0x2F
#define RK805_BUCK1_SLP_VSEL_REG		0x30
#define RK805_BUCK2_CONFIG_REG			0x32
#define RK805_BUCK2_ON_VSEL_REG			0x33
#define RK805_BUCK2_SLP_VSEL_REG		0x34
#define RK805_BUCK3_CONFIG_REG			0x36
#define RK805_BUCK4_CONFIG_REG			0x37
#define RK805_BUCK4_ON_VSEL_REG			0x38
#define RK805_BUCK4_SLP_VSEL_REG		0x39
#define RK805_LDO1_ON_VSEL_REG			0x3B
#define RK805_LDO1_SLP_VSEL_REG			0x3C
#define RK805_LDO2_ON_VSEL_REG			0x3D
#define RK805_LDO2_SLP_VSEL_REG			0x3E
#define RK805_LDO3_ON_VSEL_REG			0x3F
#define RK805_LDO3_SLP_VSEL_REG			0x40

/* IRQ Definitions */
#define RK805_IRQ_PWRON_RISE			0
#define RK805_IRQ_VB_LOW			1
#define RK805_IRQ_PWRON				2
#define RK805_IRQ_PWRON_LP			3
#define RK805_IRQ_HOTDIE			4
#define RK805_IRQ_RTC_ALARM			5
#define RK805_IRQ_RTC_PERIOD			6
#define RK805_IRQ_PWRON_FALL			7

#define RK805_IRQ_PWRON_RISE_MSK		BIT(0)
#define RK805_IRQ_VB_LOW_MSK			BIT(1)
#define RK805_IRQ_PWRON_MSK			BIT(2)
#define RK805_IRQ_PWRON_LP_MSK			BIT(3)
#define RK805_IRQ_HOTDIE_MSK			BIT(4)
#define RK805_IRQ_RTC_ALARM_MSK			BIT(5)
#define RK805_IRQ_RTC_PERIOD_MSK		BIT(6)
#define RK805_IRQ_PWRON_FALL_MSK		BIT(7)

#define RK805_PWR_RISE_INT_STATUS		BIT(0)
#define RK805_VB_LOW_INT_STATUS			BIT(1)
#define RK805_PWRON_INT_STATUS			BIT(2)
#define RK805_PWRON_LP_INT_STATUS		BIT(3)
#define RK805_HOTDIE_INT_STATUS			BIT(4)
#define RK805_ALARM_INT_STATUS			BIT(5)
#define RK805_PERIOD_INT_STATUS			BIT(6)
#define RK805_PWR_FALL_INT_STATUS		BIT(7)

#define RK805_PWRON_FALL_RISE_INT_EN		0x0
#define RK805_PWRON_FALL_RISE_INT_MSK		0x81

#define RK805_NUM_REGULATORS			7

/*************************** RK816 ********************************************/
#define RK816_I2C_SPEED				(200 * 1000)
#define RK816_DCDC1				0
#define RK816_LDO1				4

/*RTC REGISTER*/
#define RK816_SECONDS_REG			0x00
#define RK816_MINUTES_REG			0x01
#define RK816_HOURS_REG				0x02
#define RK816_DAYS_REG				0x03
#define RK816_MONTHS_REG			0x04
#define RK816_YEARS_REG				0x05
#define RK816_WEEKS_REG				0x06
#define RK816_ALARM_SECONDS_REG			0x08
#define RK816_ALARM_MINUTES_REG			0x09
#define RK816_ALARM_HOURS_REG			0x0A
#define RK816_ALARM_DAYS_REG			0x0B
#define RK816_ALARM_MONTHS_REG			0x0C
#define RK816_ALARM_YEARS_REG			0x0D
#define RK816_RTC_CTRL_REG			0x10
#define RK816_RTC_STATUS_REG			0x11
#define RK816_RTC_INT_REG			0x12
#define RK816_RTC_COMP_LSB_REG			0x13
#define RK816_RTC_COMP_MSB_REG			0x14
#define RK816_CLK32OUT_REG			0x20

/*VERSION REGISTER*/
#define RK816_CHIP_NAME_REG			0x17
#define RK816_CHIP_VER_REG			0x18
#define RK816_OTP_VER_REG			0x19

/*POWER ON/OFF REGISTER*/
#define RK816_VB_MON_REG			0x21
#define RK816_THERMAL_REG			0x22
#define RK816_PWRON_LP_INT_TIME_REG		0x47
#define RK816_PWRON_DB_REG			0x48
#define RK816_DEV_CTRL_REG			0x4B
#define RK816_ON_SOURCE_REG			0xAE
#define RK816_OFF_SOURCE_REG			0xAF

/*POWER CHANNELS ENABLE REGISTER*/
#define RK816_DCDC_EN_REG1			0x23
#define RK816_DCDC_EN_REG2			0x24
#define RK816_SLP_DCDC_EN_REG			0x25
#define RK816_SLP_LDO_EN_REG			0x26
#define RK816_LDO_EN_REG1			0x27
#define RK816_LDO_EN_REG2			0x28

/*BUCK AND LDO CONFIG REGISTER*/
#define RK816_SW_BUCK_LDO_CONFIG_REG		0x2A
#define RK816_SW2_CONFIG_REG			0xA6
#define RK816_BUCK5_ON_VSEL_REG			0x2B
#define RK816_BUCK5_SLP_VSEL_REG		0x2C
#define RK816_BUCK5_CONFIG_REG			0x2D
#define RK816_BUCK1_CONFIG_REG			0x2E
#define RK816_BUCK1_ON_VSEL_REG			0x2F
#define RK816_BUCK1_SLP_VSEL_REG		0x30
#define RK816_BUCK2_CONFIG_REG			0x32
#define RK816_BUCK2_ON_VSEL_REG			0x33
#define RK816_BUCK2_SLP_VSEL_REG		0x34
#define RK816_BUCK3_CONFIG_REG			0x36
#define RK816_BUCK4_CONFIG_REG			0x37
#define RK816_BUCK4_ON_VSEL_REG			0x38
#define RK816_BUCK4_SLP_VSEL_REG		0x39
#define RK816_LDO1_ON_VSEL_REG			0x3B
#define RK816_LDO1_SLP_VSEL_REG			0x3C
#define RK816_LDO2_ON_VSEL_REG			0x3D
#define RK816_LDO2_SLP_VSEL_REG			0x3E
#define RK816_LDO3_ON_VSEL_REG			0x3F
#define RK816_LDO3_SLP_VSEL_REG			0x40
#define RK816_LDO4_ON_VSEL_REG			0x41
#define RK816_LDO4_SLP_VSEL_REG			0x42
#define RK816_LDO5_ON_VSEL_REG			0x43
#define RK816_LDO5_SLP_VSEL_REG			0x44
#define RK816_LDO6_ON_VSEL_REG			0x45
#define RK816_LDO6_SLP_VSEL_REG			0x46

/*INTERRUPT REGISTER*/
#define RK816_INT_STS_REG1			0x49
#define RK816_INT_STS_MSK_REG1			0x4A
#define RK816_INT_STS_REG2			0x4C
#define RK816_INT_STS_MSK_REG2			0x4D
#define RK816_INT_STS_REG3			0x4E
#define RK816_INT_STS_MSK_REG3			0x4F
#define RK816_GPIO_IO_POL_REG			0x50

/*CHARGER BOOST AND OTG REGISTER*/
#define RK816_OTG_BUCK_LDO_CONFIG_REG		0x2A
#define RK816_CHRG_CONFIG_REG			0x2B
#define RK816_GPIO_IO_POL_REG			0x50
#define RK816_BOOST_ON_VESL_REG			0x54
#define RK816_BOOST_SLP_VSEL_REG		0x55
#define RK816_CHRG_BOOST_CONFIG_REG		0x9A
#define RK816_SUP_STS_REG			0xA0
#define RK816_USB_CTRL_REG			0xA1
#define RK816_CHRG_CTRL_REG1			0xA3
#define RK816_CHRG_CTRL_REG2			0xA4
#define RK816_CHRG_CTRL_REG3			0xA5
#define RK816_BAT_CTRL_REG			0xA6
#define RK816_BAT_HTS_TS_REG			0xA8
#define RK816_BAT_LTS_TS_REG			0xA9

/*ADC AND FUEL GAUGE REGISTER*/
#define RK816_HTS_TS_REG			0xA8
#define RK816_LTS_TS_REG			0xA9
#define RK816_TS_CTRL_REG			0xAC
#define RK816_ADC_CTRL_REG			0xAD
#define RK816_GGCON_REG				0xB0
#define RK816_GGSTS_REG				0xB1
#define RK816_ZERO_CUR_ADC_REGH			0xB2
#define RK816_ZERO_CUR_ADC_REGL			0xB3
#define RK816_GASCNT_CAL_REG3			0xB4
#define RK816_GASCNT_CAL_REG2			0xB5
#define RK816_GASCNT_CAL_REG1			0xB6
#define RK816_GASCNT_CAL_REG0			0xB7
#define RK816_GASCNT_REG3			0xB8
#define RK816_GASCNT_REG2			0xB9
#define RK816_GASCNT_REG1			0xBA
#define RK816_GASCNT_REG0			0xBB
#define RK816_BAT_CUR_AVG_REGH			0xBC
#define RK816_BAT_CUR_AVG_REGL			0xBD
#define RK816_TS_ADC_REGH			0xBE
#define RK816_TS_ADC_REGL			0xBF
#define RK816_USB_ADC_REGH			0xC0
#define RK816_USB_ADC_REGL			0xC1
#define RK816_BAT_OCV_REGH			0xC2
#define RK816_BAT_OCV_REGL			0xC3
#define RK816_BAT_VOL_REGH			0xC4
#define RK816_BAT_VOL_REGL			0xC5
#define RK816_RELAX_ENTRY_THRES_REGH		0xC6
#define RK816_RELAX_ENTRY_THRES_REGL		0xC7
#define RK816_RELAX_EXIT_THRES_REGH		0xC8
#define RK816_RELAX_EXIT_THRES_REGL		0xC9
#define RK816_RELAX_VOL1_REGH			0xCA
#define RK816_RELAX_VOL1_REGL			0xCB
#define RK816_RELAX_VOL2_REGH			0xCC
#define RK816_RELAX_VOL2_REGL			0xCD
#define RK816_RELAX_CUR1_REGH			0xCE
#define RK816_RELAX_CUR1_REGL			0xCF
#define RK816_RELAX_CUR2_REGH			0xD0
#define RK816_RELAX_CUR2_REGL			0xD1
#define RK816_CAL_OFFSET_REGH			0xD2
#define RK816_CAL_OFFSET_REGL			0xD3
#define RK816_NON_ACT_TIMER_CNT_REG		0xD4
#define RK816_VCALIB0_REGH			0xD5
#define RK816_VCALIB0_REGL			0xD6
#define RK816_VCALIB1_REGH			0xD7
#define RK816_VCALIB1_REGL			0xD8
#define RK816_FCC_GASCNT_REG3			0xD9
#define RK816_FCC_GASCNT_REG2			0xDA
#define RK816_FCC_GASCNT_REG1			0xDB
#define RK816_FCC_GASCNT_REG0			0xDC
#define RK816_IOFFSET_REGH			0xDD
#define RK816_IOFFSET_REGL			0xDE
#define RK816_SLEEP_CON_SAMP_CUR_REG		0xDF

/*DATA REGISTER*/
#define RK816_SOC_REG				0xE0
#define	RK816_REMAIN_CAP_REG3			0xE1
#define	RK816_REMAIN_CAP_REG2			0xE2
#define	RK816_REMAIN_CAP_REG1			0xE3
#define	RK816_REMAIN_CAP_REG0			0xE4
#define	RK816_UPDAT_LEVE_REG			0xE5
#define	RK816_NEW_FCC_REG3			0xE6
#define	RK816_NEW_FCC_REG2			0xE7
#define	RK816_NEW_FCC_REG1			0xE8
#define	RK816_NEW_FCC_REG0			0xE9
#define RK816_NON_ACT_TIMER_CNT_REG_SAVE	0xEA
#define RK816_OCV_VOL_VALID_REG			0xEB
#define RK816_REBOOT_CNT_REG			0xEC
#define RK816_PCB_IOFFSET_REG			0xED
#define RK816_MISC_MARK_REG			0xEE
#define RK816_HALT_CNT_REG			0xEF
#define RK816_CALC_REST_REGH			0xF0
#define RK816_CALC_REST_REGL			0xF1
#define DATA18_REG				0xF2

/* IRQ Definitions */
#define RK816_IRQ_PWRON_FALL			0
#define RK816_IRQ_PWRON_RISE			1
#define RK816_IRQ_VB_LOW			2
#define RK816_IRQ_PWRON				3
#define RK816_IRQ_PWRON_LP			4
#define RK816_IRQ_HOTDIE			5
#define RK816_IRQ_RTC_ALARM			6
#define RK816_IRQ_RTC_PERIOD			7
#define RK816_IRQ_USB_OV			8
#define RK816_IRQ_PLUG_IN			9
#define RK816_IRQ_PLUG_OUT			10
#define RK816_IRQ_CHG_OK			11
#define RK816_IRQ_CHG_TE			12
#define RK816_IRQ_CHG_TS			13
#define RK816_IRQ_CHG_CVTLIM			14
#define RK816_IRQ_DISCHG_ILIM			15

#define RK816_IRQ_PWRON_FALL_MSK		BIT(5)
#define RK816_IRQ_PWRON_RISE_MSK		BIT(6)
#define RK816_IRQ_VB_LOW_MSK			BIT(1)
#define RK816_IRQ_PWRON_MSK			BIT(2)
#define RK816_IRQ_PWRON_LP_MSK			BIT(3)
#define RK816_IRQ_HOTDIE_MSK			BIT(4)
#define RK816_IRQ_RTC_ALARM_MSK			BIT(5)
#define RK816_IRQ_RTC_PERIOD_MSK		BIT(6)
#define RK816_IRQ_USB_OV_MSK			BIT(7)
#define RK816_IRQ_PLUG_IN_MSK			BIT(0)
#define RK816_IRQ_PLUG_OUT_MSK			BIT(1)
#define RK816_IRQ_CHG_OK_MSK			BIT(2)
#define RK816_IRQ_CHG_TE_MSK			BIT(3)
#define RK816_IRQ_CHG_TS_MSK			BIT(4)
#define RK816_IRQ_CHG_CVTLIM_MSK		BIT(6)
#define RK816_IRQ_DISCHG_ILIM_MSK		BIT(7)

#define RK816_NUM_REGULATORS			10

#define RK816_VBAT_LOW_2V8			0x00
#define RK816_VBAT_LOW_2V9			0x01
#define RK816_VBAT_LOW_3V0			0x02
#define RK816_VBAT_LOW_3V1			0x03
#define RK816_VBAT_LOW_3V2			0x04
#define RK816_VBAT_LOW_3V3			0x05
#define RK816_VBAT_LOW_3V4			0x06
#define RK816_VBAT_LOW_3V5			0x07
#define RK816_PWR_FALL_INT_STATUS		(0x1 << 5)
#define RK816_PWR_RISE_INT_STATUS		(0x1 << 6)
#define RK816_ALARM_INT_STATUS			(0x1 << 5)

/******************************************************************************/
#define VBAT_LOW_VOL_MASK			(0x7 << 0)
#define EN_VABT_LOW_SHUT_DOWN			(0x0 << 4)
#define EN_VBAT_LOW_IRQ				(0x1 << 4)
#define VBAT_LOW_ACT_MASK			(0x1 << 4)
#define SLP_SD_MSK				(0x3 << 2)
#define SHUTDOWN_FUN				(0x2 << 2)
#define SLEEP_FUN				(0x1 << 2)
#define RTC_TIMER_ALARM_INT_MSK			(0x3 << 2)
#define RTC_TIMER_ALARM_INT_DIS			(0x0 << 2)
#define RTC_PERIOD_ALARM_INT_MSK		(0x3 << 5)
#define RTC_PERIOD_ALARM_INT_ST			(0x3 << 5)
#define RTC_PERIOD_ALARM_INT_DIS		(0x3 << 5)
#define RTC_PERIOD_ALARM_INT_EN			(0x9f)
#define VB_LOW_IRQ_DIS				(1 << 1)
#define VB_LOW_IRQ_EN				(0 << 1)
#define VB_LOW_IRQ_MSK				(1 << 1)
#define REG_WRITE_MSK				0xff
#define TEMP105C				0x08
#define TEMP115C				0x0c
#define TEMP_HOTDIE_MSK				0x0c
#define BUCK4_MAX_ILIMIT			0x2c
#define BUCK_RATE_MSK				(0x3 << 3)
#define BUCK_RATE_12_5MV_US			(0x2 << 3)
#define ALL_INT_FLAGS_ST			0xff
#define PLUGIN_OUT_INT_EN			0xfc
#define RK816_PWRON_FALL_RISE_INT_EN		0x9f
#define DEV_OFF					(1 << 0)
#define RK816_CHIP_VERSION_MASK                        0x0f
#define RK816_TYPE_ES2                         0x5
#define RK816_BUCK_DVS_CONFIRM                 BIT(7)
		
enum rk805_reg_id {
	RK805_ID_DCDC1,
	RK805_ID_DCDC2,
	RK805_ID_DCDC3,
	RK805_ID_DCDC4,
	RK805_ID_LDO1,
	RK805_ID_LDO2,
	RK805_ID_LDO3,
};

enum rk816_reg_id {
	RK816_ID_DCDC1,
	RK816_ID_DCDC2,
	RK816_ID_DCDC3,
	RK816_ID_DCDC4,
	RK816_ID_LDO1,
	RK816_ID_LDO2,
	RK816_ID_LDO3,
	RK816_ID_LDO4,
	RK816_ID_LDO5,
	RK816_ID_LDO6,
};

struct rk816_board {
	int irq;
	int irq_base;
	int irq_gpio;
	struct regulator_init_data *rk816_init_data[RK816_NUM_REGULATORS];
	struct device_node *of_node[RK816_NUM_REGULATORS];
	int pmic_sleep_gpio; /* */
	bool pmic_sleep;
	bool pm_off;
};

struct rk816 {
	struct device *dev;
	struct mutex io_lock;
	struct i2c_client *i2c;
	int num_regulators;
	struct regulator_dev **rdev;
	int irq_base;
	int irq_gpio;
	int chip_irq;
	int pmic_sleep_gpio; /* */
	bool pmic_sleep;
	struct regmap *regmap;
	struct regmap_irq_chip_data *irq_data;
	struct regmap_irq_chip_data *battery_irq_data;
};

struct rk8xx_pwrkey_data {
	u8 int_status_reg;
	u8 pwr_fall_int_status;
	u8 pwr_rise_int_status;
	int pwr_fall_irq;
	int pwr_rise_irq;
};

struct rk8xx_rtc_data {
	u8 int_status_reg;
	u8 alarm_int_status;
	int alarm_irq;
};

struct rk8xx_regulator_data {
	u8 dcdc1_id;
	u8 ldo1_id;
	u8 slp_ldo_en_reg;
	u8 slp_dcdc_en_reg;
	u8 num_regulators;
	const struct regulator_desc *reg_desc;
	struct of_regulator_match *reg_matches;
};

struct rk8xx_gpio_reg {
	u8 reg;
	u8 dir_msk;
	u8 val_msk;
	u8 fun_msk;
};

struct rk8xx_gpio_data {
	int ngpio;
	struct rk8xx_gpio_reg *gpio_reg;
};

struct rk8xx_reg_data {
	u8 reg;
	u8 val;
	u8 mask;
};

struct rk8xx_platform_data {
	const char *chip_name;
};

struct rk8xx_mfd_data {
	int cell_num;
	struct mfd_cell *cell;
	int init_reg_num;
	struct rk8xx_reg_data *init_reg;
	int suspend_reg_num;
	struct rk8xx_reg_data *suspend_reg;
	int resume_reg_num;
	struct rk8xx_reg_data *resume_reg;
	const struct regmap_config *regmap_config;
	struct regmap_irq_chip *irq_chip;
	struct regmap_irq_chip *irq_battery_chip;
	const char *parse_dt_pm_lable;
	void (*register_pm_power_off)(struct rk816_board *pdev);
};

int rk816_i2c_read(struct rk816 *rk816, char reg, int count, u8 *dest);
int rk816_i2c_write(struct rk816 *rk816, char reg, int count, const u8 src);
int rk816_set_bits(struct rk816 *rk816, u8 reg, u8 mask, u8 val);
int rk816_clear_bits(struct rk816 *rk816, u8 reg, u8 mask);
int rk816_reg_read(struct rk816 *rk816, u8 reg);
int rk816_reg_write(struct rk816 *rk816, u8 reg, u8 val);
int rk816_bulk_read(struct rk816 *rk816, u8 reg, int count, u8 *buf);
int rk816_bulk_write(struct rk816 *rk816, u8 reg, int count, u8 *buf);

#endif

