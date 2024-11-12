data segment 
    msg1 db 10,13,'Enter 5 elements:$'
    msg2 db 10,13,'Sum:$'
    array db 20 dup(?)
    length equ 5
data ends
code segment
    assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    lea dx,msg1
    mov ah,09h
    int 21h
    lea si,array  
    mov cx,length
    mov bl,0
input:
    mov ah,01h
    int 21h
    sub al,'0'
    mov [si],al
    inc si
    dec cx
    jnz input
    
    lea dx,msg2
    mov ah,09h
    int 21h
    lea si,array
    mov cx,length
calc:
    mov al,[si]
    add bl,al
    inc si
    dec cx
    jnz calc
    
    mov ax,bx
    mov cx,0
convert:
    mov dx,0
    mov bx,10
    div bx
    push dx
    inc cx
    cmp ax,0
    jne convert
print:
    pop dx
    mov al,dl
    add al,'0'
    mov dl,al
    mov ah,02h
    int 21h
    dec cx
    jnz print
    
    mov ah,4ch
    int 21h
code ends
end start
    
