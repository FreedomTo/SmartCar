/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM920T	1	/* This is an ARM920T Core	*/
#define CONFIG_S3C24X0	1	/* in a SAMSUNG S3C24x0-type SoC	*/
//#define CONFIG_S3C2410	1	/* specifically a SAMSUNG S3C2410 SoC	*/
#define CONFIG_SMDK2410	   1	/* on a SAMSUNG SMDK2410 Board  */

#define  CONFIG_S3C2440    1
#define  CONFIG_mini2440_LED  1

#define  CONFIG_S3C2440_NAND_BOOT    1

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000/* the SMDK2410 has 12MHz input clock */


#define USE_920T_MMU		1
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

/*
 * Hardware drivers
 */
#define CONFIG_NET_MULTI    1
//屏蔽掉u-boot默认对CS8900网卡的支持
//#define CONFIG_DRIVER_CS8900 1 /* we have a CS8900 on-board */
//#define CS8900_BASE    0x19000300
//#define CS8900_BUS16     1 /* the Linux driver does accesses as shorts */
//添加u-boot对DM9000X网卡的支持，其中CONFIG_DM9000_BASE宏是最重要的，因为这个就网卡的地址，不同的网卡有不同的地址，DM9000访问的基址为0x20000000,之所以再偏移0x300是由它的特性决定的。一般情况下，只有配正确这个地址，网卡的移植就会很顺利。mini2440的BACK4连接的外设就是网卡DM9000，BANK4的基地址就是0x20000000和0x20000004
#define CONFIG_DRIVER_DM9000    1
#define CONFIG_DM9000_NO_SROM    1
#define CONFIG_DM9000_BASE    0x20000300  //网卡片选地址
#define DM9000_IO    CONFIG_DM9000_BASE
#define DM9000_DATA    (CONFIG_DM9000_BASE + 4)  //网卡数据地址
//#define CONFIG_DM9000_USE_16BIT 1

/*
 * select serial console configuration
 */
#define CONFIG_S3C24X0_SERIAL
#define CONFIG_SERIAL1          1	/* we use SERIAL 1 on SMDK2410 */

/************************************************************
 * RTC
 ************************************************************/
#define	CONFIG_RTC_S3C24X0	1

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200


/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_ELF
#define CONFIG_CMD_NAND    //添加的定义
#define CONFIG_CMD_PING

#if defined (CONFIG_CMD_NAND)
#define CONFIG_NAND_S3C2440  //为了使s3c2440_nand.c文件编译进去，必须要定义。
#define CONFIG_SYS_NAND_BASE 0x4e000000  //NandFlash中的各个寄存器的地址，基址
#define CONFIG_SYS_MAX_NAND_DEVICE 1  //NandFlash设备的数目为1
#define CONFIG_MTD_NAND_VERIFY_WRITE 1
//#define NAND_SAMSUNG_LP_OPTIONS 1
#define NAND_MAX_CHIPS 1  //每个NandFlash设备，由1个NandFlash芯片组成。
#define CONFIG_SYS_64BIT_VSPRINTF
#endif

#define CONFIG_INITRD_TAG
#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS   1
#define  CONFIG_BOOTCOMMAND "nand read 0x30008000 0x60000 0x500000; bootm 0x30008000"

#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 ">"
#define CONFIG_CMDLINE_EDITING 

#define CONFIG_AUTO_COMPLETE

//恢复被注释掉的网卡MAC地址和修改你合适的开发板IP地址
#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS	"noinitrd  root=/dev/mtdblock3  init=/linuxrc  console=ttySAC0,115200 mem=64M"


#define CONFIG_ETHADDR    08:90:90:90:90:90  //开发板MAC地址
#define CONFIG_NETMASK    255.255.255.0
#define CONFIG_IPADDR    192.168.1.226 //开发板IP地址
#define CONFIG_SERVERIP    192.168.1.200 //Linux主机IP地址
/*#define CONFIG_BOOTFILE  "elinos-lart" */
/*#define CONFIG_BOOTCOMMAND  "tftp; bootm" */ 

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

/*
 * Miscellaneous configurable options
 */
#define	CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"[PAN_MINI2440]# "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM	*/

#define	CONFIG_SYS_LOAD_ADDR		0x33000000	/* default load address	*/

#define	CONFIG_SYS_HZ			1000

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#if 0
#define CONFIG_AMD_LV400	1	/* uncomment this if you have a LV400 flash */
#define CONFIG_AMD_LV800	1	/* uncomment this if you have a LV800 flash */
#endif

#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#ifdef CONFIG_AMD_LV800
#define PHYS_FLASH_SIZE		0x00100000 /* 1MB */
#define CONFIG_SYS_MAX_FLASH_SECT	(19)	/* max number of sectors on one chip */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x0F0000) /* addr of environment */
#endif
#ifdef CONFIG_AMD_LV400
#define PHYS_FLASH_SIZE		0x00080000 /* 512KB */
#define CONFIG_SYS_MAX_FLASH_SECT	(11)	/* max number of sectors on one chip */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x070000) /* addr of environment */
#endif

#define CONFIG_SST_39VF1601   1   
#define PHYS_FLASH_SIZE    0x200000
#define CONFIG_SYS_MAX_FLASH_SECT  (512)  
#define CONFIG_ENV_ADDR  (CONFIG_SYS_FLASH_BASE + 0x040000) 

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Write */

//#define	CONFIG_ENV_IS_IN_FLASH	1
//#define CONFIG_ENV_SIZE		0x10000	/* Total Size of Environment Sector */
#define CONFIG_ENV_IS_IN_NAND  1
#define CONFIG_ENV_OFFSET    0x60000 //将环境变量保存到nand中的0x60000位置
#define CONFIG_ENV_SIZE    0x20000 /* Total Size of Environment Sector */
#endif	/* __CONFIG_H */

#define    ENABLE_CMD_LOADB_X1

#define CONFIG_MTD_NAND_YAFFS2  1 //定义一个管理对Yaffs2支持的宏
//开启Nand Flash默认分区，注意此处的分区要和你的内核中的分区保持一致
#define MTDIDS_DEFAULT   "nand0=nandflash0"
#define MTDPARTS_DEFAULT  "mtdparts=nandflash0:384k(bootloader),"\
            "128k(params),"\
            "5m(kernel),"\
            "-(root)"  //这里要和Linux内核中的分区信息相一致
