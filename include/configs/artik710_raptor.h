/*
 * (C) Copyright 2016 Nexell
 * Hyunseok, Jung <hsjung@nexell.co.kr>
 *
 * SPDX-License-Identifier:      GPL-2.0+
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <linux/sizes.h>

/*-----------------------------------------------------------------------
 *  u-boot-2016.01
 */
#define CONFIG_SYS_LDSCRIPT "arch/arm/cpu/armv8/u-boot.lds"

#define	CONFIG_MACH_S5P6818

/*-----------------------------------------------------------------------
 *  System memory Configuration
 */

#define	CONFIG_SYS_TEXT_BASE			0x43C00000
/* init and run stack pointer */
#define	CONFIG_SYS_INIT_SP_ADDR			CONFIG_SYS_TEXT_BASE

/* malloc() pool */
#define	CONFIG_MEM_MALLOC_START			0x44000000
/* more than 2M for ubifs: MAX 16M */
#define CONFIG_MEM_MALLOC_LENGTH		(32*1024*1024)

/* when CONFIG_LCD */
#define CONFIG_FB_ADDR				0x46000000

/* Download OFFSET */
#define CONFIG_MEM_LOAD_ADDR			0x48000000

#define CONFIG_SYS_BOOTM_LEN    (64 << 20)      /* Increase max gunzip size */

/* AARCH64 */
#define COUNTER_FREQUENCY			200000000
#define CPU_RELEASE_ADDR			CONFIG_SYS_INIT_SP_ADDR

/*-----------------------------------------------------------------------
 *  High Level System Configuration
 */

/* Not used: not need IRQ/FIQ stuff	*/
#undef  CONFIG_USE_IRQ
/* decrementer freq: 1ms ticks */
#define CONFIG_SYS_HZ				1000

/* board_init_f */
#define	CONFIG_SYS_SDRAM_BASE			0x40000000
#define	CONFIG_SYS_SDRAM_SIZE			0x38000000

/* dram 1 bank num */
#define CONFIG_NR_DRAM_BANKS			1

/* relocate_code and  board_init_r */
#define	CONFIG_SYS_MALLOC_END			(CONFIG_MEM_MALLOC_START + \
						 CONFIG_MEM_MALLOC_LENGTH)
/* board_init_f, more than 2M for ubifs */
#define CONFIG_SYS_MALLOC_LEN \
	(CONFIG_MEM_MALLOC_LENGTH - 0x8000)

/* kernel load address */
#define CONFIG_SYS_LOAD_ADDR			CONFIG_MEM_LOAD_ADDR

/* memtest works on */
#define CONFIG_SYS_MEMTEST_START		CONFIG_SYS_MALLOC_END
#define CONFIG_SYS_MEMTEST_END			((ulong)CONFIG_SYS_SDRAM_BASE \
						 + (ulong)CONFIG_SYS_SDRAM_SIZE)

/*-----------------------------------------------------------------------
 *  System initialize options (board_init_f)
 */

/* board_init_f->init_sequence, call arch_cpu_init */
#define CONFIG_ARCH_CPU_INIT
/* board_init_f->init_sequence, call board_early_init_f */
#define	CONFIG_BOARD_EARLY_INIT_F
/* board_init_r, call board_early_init_f */
#define	CONFIG_BOARD_LATE_INIT
/* board_init_f->init_sequence, call print_cpuinfo */
#define	CONFIG_DISPLAY_CPUINFO
/* board_init_f, CONFIG_SYS_ICACHE_OFF */
#define	CONFIG_SYS_DCACHE_OFF
/* board_init_r, call arch_misc_init */
#define	CONFIG_ARCH_MISC_INIT
/*#define	CONFIG_SYS_ICACHE_OFF*/

/*-----------------------------------------------------------------------
 *	U-Boot default cmd
 */
#define	CONFIG_CMD_MEMTEST

/*-----------------------------------------------------------------------
 *	U-Boot Environments
 */
/* refer to common/env_common.c	*/
#define CONFIG_BOOTDELAY			3

/*-----------------------------------------------------------------------
 * Miscellaneous configurable options
 */
#ifdef CONFIG_SYS_PROMPT
#undef CONFIG_SYS_PROMPT
/* Monitor Command Prompt   */
#define CONFIG_SYS_PROMPT			"artik710# "
#endif
/* undef to save memory	   */
#define CONFIG_SYS_LONGHELP
/* Console I/O Buffer Size  */
#define CONFIG_SYS_CBSIZE			1024
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE			(CONFIG_SYS_CBSIZE + \
						 sizeof(CONFIG_SYS_PROMPT)+16)
/* max number of command args   */
#define CONFIG_SYS_MAXARGS			16
/* Boot Argument Buffer Size    */
#define CONFIG_SYS_BARGSIZE			CONFIG_SYS_CBSIZE

/*-----------------------------------------------------------------------
 * allow to overwrite serial and ethaddr
 */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_SYS_HUSH_PARSER			/* use "hush" command parser */
#ifdef CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif

/*-----------------------------------------------------------------------
 * Etc Command definition
 */
#define	CONFIG_CMD_IMI				/* image info	*/
#define CONFIG_CMDLINE_EDITING			/* add command line history */
#define	CONFIG_CMDLINE_TAG			/* use bootargs commandline */
#undef	CONFIG_BOOTM_NETBSD
#undef	CONFIG_BOOTM_RTEMS
#define CONFIG_INITRD_TAG

/*-----------------------------------------------------------------------
 * serial console configuration
 */
#define CONFIG_S5P_SERIAL
#define CONFIG_S5P_SERIAL_INDEX			3
#define CONFIG_S5P_SERIAL_CLOCK			50000000

#define CONFIG_BAUDRATE				115200
#define CONFIG_SYS_BAUDRATE_TABLE \
		{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_S5P_SERIAL_FLUSH_ON_INIT

#define CONFIG_UART_CLKGEN_CLOCK_HZ		CONFIG_S5P_SERIAL_CLOCK

/*-----------------------------------------------------------------------
 * NOR FLASH
 */
#define	CONFIG_SYS_NO_FLASH

/*-----------------------------------------------------------------------
 * SD/MMC
 */

#define CONFIG_GENERIC_MMC
#define CONFIG_MMC
#define CONFIG_DWMMC
#define CONFIG_NEXELL_DWMMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_MMC

#if defined(CONFIG_MMC)
#define CONFIG_2NDBOOT_OFFSET		512
#define CONFIG_2NDBOOT_SIZE		(64*1024)
#define CONFIG_FIP_OFFSET		(CONFIG_2NDBOOT_OFFSET +\
					 CONFIG_2NDBOOT_SIZE)
#define CONFIG_FIP_SIZE			(3*1024*1024)
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define	CONFIG_ENV_OFFSET		(CONFIG_FIP_OFFSET +\
					 CONFIG_FIP_SIZE)
#define CONFIG_ENV_SIZE			(16*1024)	/* env size */
#endif

#if defined(CONFIG_MMC)
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_FAT
#define CONFIG_FS_FAT
#define CONFIG_FAT_WRITE

#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE
#define CONFIG_FS_EXT4
#define CONFIG_EXT4_WRITE
#endif

/*-----------------------------------------------------------------------
 * Default environment organization
 */
#if !defined(CONFIG_ENV_IS_IN_MMC) && !defined(CONFIG_ENV_IS_IN_NAND) && \
	!defined(CONFIG_ENV_IS_IN_FLASH) && !defined(CONFIG_ENV_IS_IN_EEPROM)
	/* default: CONFIG_ENV_IS_NOWHERE */
	#define CONFIG_ENV_IS_NOWHERE
	#define	CONFIG_ENV_OFFSET		1024
	#define CONFIG_ENV_SIZE			(4*1024)	/* env size */
	/* imls - list all images found in flash, default enable so disable */
	#undef	CONFIG_CMD_IMLS
#endif

/*-----------------------------------------------------------------------
 * PLL
 */

#define CONFIG_SYS_PLLFIN			24000000UL

/*-----------------------------------------------------------------------
 * Timer
 */

#define CONFIG_TIMER_SYS_TICK_CH		0

/*-----------------------------------------------------------------------
 * GPT
 */
#define CONFIG_CMD_GPT
#define CONFIG_EFI_PARTITION
#define CONFIG_PARTITION_UUIDS
#define CONFIG_RANDOM_UUID

/*-----------------------------------------------------------------------
 * Fastboot and USB OTG
 */

#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_CMD_FASTBOOT
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_FASTBOOT_FLASH_MMC_DEV   0
#define CONFIG_FASTBOOT_BUF_SIZE        (CONFIG_SYS_SDRAM_SIZE - SZ_1M)
#define CONFIG_FASTBOOT_BUF_ADDR        CONFIG_SYS_SDRAM_BASE
#define CONFIG_USB_GADGET
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_GADGET_VBUS_DRAW     0
#define CONFIG_USB_GADGET_DWC2_OTG
#define CONFIG_USB_GADGET_NX_UDC_OTG_PHY
#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_SYS_CACHELINE_SIZE       64
#define CONFIG_G_DNL_VENDOR_NUM         0x18d1  /* google */
#define CONFIG_G_DNL_PRODUCT_NUM        0x0002  /* nexus one */
#define CONFIG_G_DNL_MANUFACTURER       "Nexell Corporation"

/*-----------------------------------------------------------------------
 * Nexell USB Downloader
 */
#define CONFIG_NX_USBDOWN

/*-----------------------------------------------------------------------
 * PWM
 */
#define CONFIG_PWM_NX

/*-----------------------------------------------------------------------
 * OF_CONTROL
 */

#define CONFIG_FIT_BEST_MATCH
#define CONFIG_OF_LIBFDT

/*-----------------------------------------------------------------------
 * GMAC
 */
#define CONFIG_PHY_REALTEK

#define CONFIG_ETHPRIME			"RTL8211"
#define CONFIG_PHY_ADDR			3

#define CONFIG_DW_ALTDESCRIPTOR

#define CONFIG_PHY_GIGE
#define CONFIG_MII
#define CONFIG_CMD_MII

/* NET */
#define CONFIG_CMD_GEN_ETHADDR

/* FACTORY_INFO */
#define CONFIG_CMD_FACTORY_INFO
#define CONFIG_FACTORY_INFO_BUF_ADDR		0x70000000
#define CONFIG_FACTORY_INFO_START		0x1c00
#define CONFIG_FACTORY_INFO_SIZE		0x100
/*-----------------------------------------------------------------------
 * BOOTCOMMAND
 */
#define CONFIG_REVISION_TAG

#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC3,115200n8\0"

#define CONFIG_ROOT_DEV		0
#define CONFIG_BOOT_PART	1
#define CONFIG_MODULE_PART	2
#define CONFIG_ROOT_PART	3

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"fdt_high=0xffffffffffffffff\0"					\
	"initrd_high=0xffffffffffffffff\0"				\
	"kerneladdr=0x48000000\0"					\
	"kernel_file=uImage\0"						\
	"ramdiskaddr=0x49000000\0"					\
	"ramdisk_file=ramdisk.gz\0"					\
	"fdtaddr=0x4a000000\0"						\
	"load_fdt="							\
		"loop=$board_rev; "					\
		"number=$board_rev: "					\
		"success=0; "						\
		"until test $loop -eq 0 || test $success -ne 0; do "	\
			"if test $loop -lt 10; then "			\
				"number=0$loop; "			\
			"else number=$loop; "				\
			"fi; "						\
			"ext4load mmc $rootdev:$bootpart $fdtaddr s5p6818-artik710-raptor-rev${number}.dtb && setexpr success 1; " \
			"setexpr loop $loop - 1; "			\
			"done; "					\
		"if test $success -eq 0; then "				\
			"ext4load mmc $rootdev:$bootpart $fdtaddr s5p6818-artik710-raptor-rev00.dtb || "	\
			"ext4load mmc $rootdev:$bootpart $fdtaddr s5p6818-artik710-raptor.dtb; "	\
		"fi; \0"						\
	"console=" CONFIG_DEFAULT_CONSOLE				\
	"consoleon=set console=" CONFIG_DEFAULT_CONSOLE			\
		"; saveenv; reset\0"					\
	"consoleoff=set console=ram; saveenv; reset\0"			\
	"rootdev=" __stringify(CONFIG_ROOT_DEV) "\0"			\
	"rootpart=" __stringify(CONFIG_ROOT_PART) "\0"			\
	"bootpart=" __stringify(CONFIG_BOOT_PART) "\0"			\
	"root_rw=rw\0"							\
	"opts=loglevel=4\0"						\
	"rootfs_type=ext4\0"						\
	"lcd1_0=s6e8fa0\0"						\
	"lcd2_0=gst7d0038\0"						\
	"lcd_panel=s6e8fa0\0"						\
	"sdrecovery=sd_recovery mmc 1:3 48000000 partmap_emmc.txt\0"	\
	"factory_load=factory_info load mmc 0 "				\
		__stringify(CONFIG_FACTORY_INFO_START) " "		\
		__stringify(CONFIG_FACTORY_INFO_SIZE) "\0"		\
	"factory_save=factory_info save mmc 0 "				\
		__stringify(CONFIG_FACTORY_INFO_START) " "		\
		__stringify(CONFIG_FACTORY_INFO_SIZE) "\0"		\
	"factory_set_ethaddr=run factory_load; gen_eth_addr ;"		\
		"factory_info write ethaddr $ethaddr;"			\
		"run factory_save\0"					\
	"boot_cmd_initrd="						\
		"run load_fdt;"						\
		"ext4load mmc ${rootdev}:${bootpart} $kerneladdr $kernel_file;" \
		"ext4load mmc ${rootdev}:${bootpart} $ramdiskaddr $ramdisk_file;" \
		"bootm $kerneladdr - $fdtaddr\0"		\
	"ramfsboot=setenv bootargs ${console} "				\
		"root=/dev/ram0 ${root_rw} initrd=${ramdiskaddr},16M ramdisk=16384 "	\
		"${opts} ${recoverymode} bd_addr=${bd_addr} "		\
		"drm_panel=$lcd_panel;"					\
		"run boot_cmd_initrd\0"					\
	"mmcboot=setenv bootargs ${console} "				\
		"root=/dev/mmcblk${rootdev}p${rootpart} ${root_rw} "	\
		"${opts} bd_addr=${bd_addr} "				\
		"drm_panel=$lcd_panel;"					\
		"run boot_cmd_initrd\0"					\
	"recoveryboot=run sdrecovery; setenv recoverymode recovery;"	\
		"run ramfsboot\0"					\
	"hwtestboot=run sdrecovery; setenv rootdev 1;"			\
		"setenv opts rootfstype=ext4 rootwait loglevel=7;"	\
		"run mmcboot\0"						\
	"bootcmd=run mmcboot\0"

#endif /* __CONFIG_H__ */
