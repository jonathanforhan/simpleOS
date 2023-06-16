/* multiboot2.h - Multiboot 2 header file. */
#pragma once

/**
 * @file
 *
 * This multiboot2 header was taken from the GNU grub2 manual
 * source: https://www.gnu.org/software/grub/manual/multiboot2/multiboot.pdf
 */

/** How many bytes from the start of the file we search for the header */
#define MULTIBOOT_SEARCH                        32768
#define MULTIBOOT_HEADER_ALIGN                  8

/** Multiboot2 magic number for BIOS detection */
#define MULTIBOOT2_HEADER_MAGIC                 0xe85250d6

/** Magic number identifying a valid multiboot2 compliant bootloader */
#define MULTIBOOT2_BOOTLOADER_MAGIC             0x36d76289

/** Alignment of multiboot modules. */
#define MULTIBOOT_MOD_ALIGN                     0x00001000

/** Alignment of the multiboot info structure. */
#define MULTIBOOT_INFO_ALIGN                    0x00000008

/** Flags set in the 'flags' member of the multiboot header */

#define MULTIBOOT_TAG_ALIGN                  8
#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_CMDLINE           1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
#define MULTIBOOT_TAG_TYPE_MODULE            3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_BOOTDEV           5
#define MULTIBOOT_TAG_TYPE_MMAP              6
#define MULTIBOOT_TAG_TYPE_VBE               7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
#define MULTIBOOT_TAG_TYPE_APM               10
#define MULTIBOOT_TAG_TYPE_EFI32             11
#define MULTIBOOT_TAG_TYPE_EFI64             12
#define MULTIBOOT_TAG_TYPE_SMBIOS            13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
#define MULTIBOOT_TAG_TYPE_NETWORK           16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
#define MULTIBOOT_TAG_TYPE_EFI_BS            18
#define MULTIBOOT_TAG_TYPE_EFI32_IH          19
#define MULTIBOOT_TAG_TYPE_EFI64_IH          20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21

#define MULTIBOOT_HEADER_TAG_END                    0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST    1
#define MULTIBOOT_HEADER_TAG_ADDRESS                2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS          3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS          4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER            5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN           6
#define MULTIBOOT_HEADER_TAG_EFI_BS                 7
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32    8
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64    9
#define MULTIBOOT_HEADER_TAG_RELOCATABLE            10

#define MULTIBOOT_ARCHITECTURE_I386     0
#define MULTIBOOT_ARCHITECTURE_MIPS32   4
#define MULTIBOOT_HEADER_TAG_OPTIONAL   1

#define MULTIBOOT_LOAD_PREFERENCE_NONE  0
#define MULTIBOOT_LOAD_PREFERENCE_LOW   1
#define MULTIBOOT_LOAD_PREFERENCE_HIGH  2

#define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED    1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED  2

#ifndef __ASSEMBLER__

typedef unsigned char       multiboot_uint8_t;
typedef unsigned short      multiboot_uint16_t;
typedef unsigned int        multiboot_uint32_t;
typedef unsigned long long  multiboot_uint64_t;

/**
 * The layout of multiboot2 header must be as follows:
 * |offset  |type   |field name     |note       |
 * |:-------|:------|:--------------|:----------|
 * |0       |u32    |magic          |required   |
 * |4       |u32    |architecture   |required   |
 * |8       |u32    |header_length  |required   |
 * |12      |u32    |checksum       |required   |
 * |16-XX   |       |tags           |required   |
 */
struct multiboot_header {
    /**  Must be set to MULTIBOOT_MAGIC */
    multiboot_uint32_t magic;

    /** ISA (instruction set architecture) must be i386 or MIPS */
    multiboot_uint32_t architecture;

    /** Total multiboot header length */
    multiboot_uint32_t header_length;

    /** The above fields plus this one must equal 0 mod 2^32 */
    multiboot_uint32_t checksum;
};

/**
 * Tags constitutes a buffer of structures following each other padded when necessary in order
 * for each tag to start at 8-bytes aligned address. Tags are terminated by a tag of type ‘0’
 * and size ‘8’. Every structure has following format:
 *
 * - u16 | type
 * - u16 | flags
 * - u32 | size
 */
struct multiboot_header_tag {
    /** type if divided into 2 parts, the lower contains an identifier of contents of the rest
    of the tag */
    multiboot_uint16_t type;

    /** if bit 0 of flags (aka 'optional') **is set** the bootloader my ignore this tag */
    multiboot_uint16_t flags;

    /** contains size of tag including header files */
    multiboot_uint32_t size;
};

/**
 * If this tag is present and 'optional' is set to 0, the bootloader must support the
 * requested tag and be able to provide relevant information to the image if it is available. If
 * the bootloader does not understand the meaning of the requested tag it must fail with an
 * error. However, if it supports a given tag but the information conveyed by it is not available
 * the bootloader does not provide the requested tag in the Multiboot2 information structure
 * and passes control to the loaded image as usual */
struct multiboot_header_tag_information_request {
    /** type = 1 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;

    /** an array of u32's, each one representing an information request */
    multiboot_uint32_t requests[0];
};

/**
 * tag describing physical addresses of key segments, may be omitted if the kernel image
 * is in ELF format */
struct multiboot_header_tag_address {
    /** type = 2 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;

    /**
     * contains physical address of the beginning of the multiboot2 header, address
     * where the magic number is located */
    multiboot_uint32_t header_addr;

    /** contains physical address of the beginning of text segment */
    multiboot_uint32_t load_addr;

    /** contains physical address of the end of data segment */
    multiboot_uint32_t load_end_addr;

    /** contains physical address of the end of the bss segment */
    multiboot_uint32_t bss_end_addr;
};

struct multiboot_header_tag_entry_address {
    /** type = 3 / 8 / 9  (ISA and EFI dependant see gnu source) */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;

    /** physical address to jump to start the OS */
    multiboot_uint32_t entry_addr;
};

/**
 * If this tag is present and bit 0 of 'console_flags' is set at least one of supported
 * consoles must be present and information about it must be available in mbi. If bit 1 of
 * 'console_flags' is set it indicates that the OS image has EGA text support */
struct multiboot_header_tag_console_flags {
    /** type = 4 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;
    multiboot_uint32_t console_flags;
};

/**
 * this tag specifies the preferred graphic mode. If this tag is present bootloader 
 * assumes that the payload has framebuffer support */
struct multiboot_header_tag_framebuffer {
    /** type = 5 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;

    /** 
     * contains the number of columns, this is specified in pixels in graphics mode
     * and characters in text mode, 0 indicates no preference */
    multiboot_uint32_t width;

    /** 
     * contains the number of columns, this is specified in pixels in graphics mode
     * and characters in text mode, 0 indicates no preference */
    multiboot_uint32_t height;

    /** contains the number of bits per pixel in a graphics mode and zero in text mode */
    multiboot_uint32_t depth;
};

/** if this tag is present modules must be page aligned */
struct multiboot_header_tag_module_align {
    /** type = 6 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;
};

/** this tag indicates that the image is relocatable */
struct multiboot_header_tag_relocatable {
    /** type = 10 */
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;

    /** lowest possible memory address at which image should be loaded */
    multiboot_uint32_t min_addr;

    /** highest possible memory address at which image should be loaded */
    multiboot_uint32_t max_addr;

    /** image alignment e.g. 4096 */
    multiboot_uint32_t align;

    /** It contains load address placement suggestion for boot loader. Boot loader
     * should follow it. 0 means none, 1 means load image at lowest possible address
     * but not lower than min addr and 2 means load image at highest possible
     * address but not higher than max addr */
    multiboot_uint32_t preference;
};

struct multiboot_color {
    multiboot_uint8_t red;
    multiboot_uint8_t green;
    multiboot_uint8_t blue;
};

struct multiboot_mmap_entry {
    multiboot_uint64_t addr;
    multiboot_uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE       3
#define MULTIBOOT_MEMORY_NVS                    4
#define MULTIBOOT_MEMORY_BADRAM                 5
    multiboot_uint32_t type;
    multiboot_uint32_t zero;
};
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_tag {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
};

struct multiboot_tag_string {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    char string[0];
};

struct multiboot_tag_module {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t mod_start;
    multiboot_uint32_t mod_end;
    char cmdline[0];
};

struct multiboot_tag_basic_meminfo {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t mem_lower;
    multiboot_uint32_t mem_upper;
};

struct multiboot_tag_bootdev {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t biosdev;
    multiboot_uint32_t slice;
    multiboot_uint32_t part;
};

struct multiboot_tag_mmap {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t entry_size;
    multiboot_uint32_t entry_version;
    struct multiboot_mmap_entry entries[0];
};

struct multiboot_vbe_info_block {
    multiboot_uint8_t external_specification[512];
};

struct multiboot_vbe_mode_info_block {
    multiboot_uint8_t external_specification[256];
};

struct multiboot_tag_vbe {
    multiboot_uint32_t type;
    multiboot_uint32_t size;

    multiboot_uint16_t vbe_mode;
    multiboot_uint16_t vbe_interface_seg;
    multiboot_uint16_t vbe_interface_off;
    multiboot_uint16_t vbe_interface_len;

    struct multiboot_vbe_info_block vbe_control_info;
    struct multiboot_vbe_mode_info_block vbe_mode_info;
};

struct multiboot_tag_framebuffer_common {
    multiboot_uint32_t type;
    multiboot_uint32_t size;

    multiboot_uint64_t framebuffer_addr;
    multiboot_uint32_t framebuffer_pitch;
    multiboot_uint32_t framebuffer_width;
    multiboot_uint32_t framebuffer_height;
    multiboot_uint8_t framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED  0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB      1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT 2
    multiboot_uint8_t framebuffer_type;
    multiboot_uint16_t reserved;
};

struct multiboot_tag_framebuffer {
    struct multiboot_tag_framebuffer_common common;

    union {
        struct {
            multiboot_uint16_t framebuffer_palette_num_colors;
            struct multiboot_color framebuffer_palette[0];
        };
        struct {
            multiboot_uint8_t framebuffer_red_field_position;
            multiboot_uint8_t framebuffer_red_mask_size;
            multiboot_uint8_t framebuffer_green_field_position;
            multiboot_uint8_t framebuffer_green_mask_size;
            multiboot_uint8_t framebuffer_blue_field_position;
            multiboot_uint8_t framebuffer_blue_mask_size;
        };
    };
};

struct multiboot_tag_elf_sections {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t num;
    multiboot_uint32_t entsize;
    multiboot_uint32_t shndx;
    char sections[0];
};

struct multiboot_tag_apm {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint16_t version;
    multiboot_uint16_t cseg;
    multiboot_uint32_t offset;
    multiboot_uint16_t cseg_16;
    multiboot_uint16_t dseg;
    multiboot_uint16_t flags;
    multiboot_uint16_t cseg_len;
    multiboot_uint16_t cseg_16_len;
    multiboot_uint16_t dseg_len;
};

struct multiboot_tag_efi32 {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t pointer;
};

struct multiboot_tag_efi64 {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint64_t pointer;
};

struct multiboot_tag_smbios {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint8_t major;
    multiboot_uint8_t minor;
    multiboot_uint8_t reserved[6];
    multiboot_uint8_t tables[0];
};

struct multiboot_tag_old_acpi {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint8_t rsdp[0];
};

struct multiboot_tag_new_acpi {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint8_t rsdp[0];
};

struct multiboot_tag_network {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint8_t dhcpack[0];
};

struct multiboot_tag_efi_mmap {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t descr_size;
    multiboot_uint32_t descr_vers;
    multiboot_uint8_t efi_mmap[0];
};

struct multiboot_tag_efi32_ih {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t pointer;
};

struct multiboot_tag_efi64_ih {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint64_t pointer;
};

struct multiboot_tag_load_base_addr {
    multiboot_uint32_t type;
    multiboot_uint32_t size;
    multiboot_uint32_t load_base_addr;
};

#endif // __ASSEMBLER__

/*   Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
