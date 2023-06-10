;
; paging.S
;
;
; PAGING_INIT:
;       paging is a memory managemnet stategy in which we map the full 64-bit
;       address space to physical memory. This creates virtual memory used by
;       the software and physical memory used by the hardware. Paging also prevents
;       invalid read-write by software
;       to do paging the MMU needs us to setup a paging table, it has 4 levels
;               page-map level-4 table          (PML4)
;               page-directory pointer table    (PDP)
;               page-directory table            (PD)
;               page-table                      (PT)
;
; used with PAGING_BSS in the section .bss
%macro PAGING_INIT 0
;       point first entry of PML4 to first entry of PDP
        mov     eax, p3_table
        or      eax, 0b11               ; add 'present' (bit 1) and 'writable' (bit 2)
        mov     dword [p4_table + 0], eax

;       point first entry of PDP to first entry of PD
        mov     eax, p2_table
        or      eax, 0b11               ; add 'present' (bit 1) and 'writable' (bit 2)
        mov     dword [p3_table + 0], eax

;       point each PD entry to a page
        xor     ecx, ecx                ; i = 0
.map_p2_table:
        mov     eax, 0x00200000         ; 2MiB
        mul     ecx                     ; eax *= i
        or      eax, 0b10000011         ; set 'Huge page' bit 'present' bit and 'writable' bit
        mov     [p2_table + ecx * 8], eax ; segment pointer by 8 bytes (for 64 bit address)
        inc     ecx
        cmp     ecx, 512
        jne     .map_p2_table

;       load top level of paging table into cr3
        mov     eax, p4_table
        mov     cr3, eax

;       enable physical address extension
        mov     eax, cr4
        or      eax, 1 << 5
        mov     cr4, eax

;       set long mode
        mov     ecx, 0xc0000080
        rdmsr   ; read model specific register
        or      eax, 1 << 8
        wrmsr   ; write model specific register

;       finally enable paging
        mov     eax, cr0
        or      eax, 1 << 31
        or      eax, 1 << 16
        mov     cr0, eax
%endmacro


%macro PAGING_BSS 0
; page table:
;       align to 4096, this allows us to use certain bits as flags ie
;       setting 0b11 sets present and writable flags
align   4096
;       Page table setup, each page is 2MB
p4_table:               ; page map level 4 table        (PML4)
        resb    4096
p3_table:               ; page directory pointer table  (PDP)
        resb    4096
p2_table:               ; page directory table          (PD)
        resb    4096
; there is a p1 table   ; Page table                    (PT)
%endmacro
