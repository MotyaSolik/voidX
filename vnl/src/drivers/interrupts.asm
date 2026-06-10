[bits 32]

; Экспортируем имя нашей ASM-заглушки наружу, чтобы C-код её увидел
global keyboard_handler_asm

; Импортируем имя C-функции, которую мы будем вызывать внутри
extern keyboard_handler_c

keyboard_handler_asm:
    pusha          ; Сохраняем все общие регистры (EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI)
    push ds        ; Сохраняем сегментные регистры
    push es
    push fs
    push gs

    ; На всякий случай явно устанавливаем сегменты данных ядра (0x10)
    mov ax, 0x10
    mov ds, ax
    mov es, ax

    ; Вызываем чистую C-логику
    call keyboard_handler_c

    pop gs         ; Восстанавливаем сегментные регистры в обратном порядке
    pop fs
    pop es
    pop ds
    popa           ; Восстанавливаем общие регистры
    
    iret           ; Тот самый безопасный выход, на котором мы падали!
