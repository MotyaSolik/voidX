; Gemini написал мне этот код
[bits 32]


global keyboard_handler_asm


extern keyboard_handler_c

keyboard_handler_asm:
    pusha          
    push ds        
    push es
    push fs
    push gs

    
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    
    call keyboard_handler_c

    pop gs         
    pop fs
    pop es
    pop ds
    popa           
    
    iret           

global timer_handler_asm
extern timer_handler_c

timer_handler_asm:
    pusha          
    push ds        
    push es
    push fs
    push gs

    mov ax, 0x10   
    mov ds, ax
    mov es, ax

    call timer_handler_c 

    pop gs         
    pop fs
    pop es
    pop ds
    popa
    iret           



extern exception_handler_c


%macro ISR_NOERRCODE 1
global isr%1
isr%1:
    push 0          
    push %1         
    jmp isr_common_stub
%endmacro


%macro ISR_ERRCODE 1
global isr%1
isr%1:
    push %1         
    jmp isr_common_stub
%endmacro


ISR_NOERRCODE 0   
ISR_NOERRCODE 1   
ISR_NOERRCODE 2   
ISR_NOERRCODE 3   
ISR_NOERRCODE 4   
ISR_NOERRCODE 5   
ISR_NOERRCODE 6   
ISR_NOERRCODE 7   
ISR_ERRCODE   8   
ISR_NOERRCODE 9   
ISR_ERRCODE   10  
ISR_ERRCODE   11  
ISR_ERRCODE   12  
ISR_ERRCODE   13  
ISR_ERRCODE   14  
ISR_NOERRCODE 15  
ISR_NOERRCODE 16  
ISR_ERRCODE   17  
ISR_NOERRCODE 18  
ISR_NOERRCODE 19  
ISR_NOERRCODE 20  
ISR_ERRCODE   21  

ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_ERRCODE   30
ISR_NOERRCODE 31


isr_common_stub:
    pusha          
    push ds        
    push es
    push fs
    push gs

    mov ax, 0x10   
    mov ds, ax
    mov es, ax

    call exception_handler_c 

    pop gs         
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     
    iret
