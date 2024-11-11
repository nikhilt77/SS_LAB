data segment
    msg1 db 10,13,'Sum Calculated$' 
    array db 01h,02h,03h,04h,05h
    length equ 5
    sum dw 3 dup(?)
data ends
code segment
    assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    mov cx,length 
    
    lea dx,msg1
    mov ah,09h
    int 21h 
    
    mov ax,00h
    mov bx,00h
    mov si,offset array
add_loop:
    mov bx,[si]
    add ax,bx
    inc si
    dec cx
    jnz add_loop
    mov di,offset sum
    mov [di],ax
    mov ah,4ch
    int 21h
end start
code ends    
    
