data segment 
    msg1 db 10,13,'Enter 5 numbers:$' 
    msg2 db 10,13,'Copied Array:$'
    arr1 db 20 dup(?)
    length equ 5
    arr2 db 20 dup(?)
data ends
code segment
    assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    lea dx,msg1
    mov ah,09h
    int 21h
    mov cx,length
    lea si,arr1
    lea di,arr2
input:
    mov ah,01h
    int 21h
    sub al,'0'
    mov [si],al 
    inc si
    dec cx
    jnz input
    mov cx,length
    lea si,arr1
    lea di,arr2
    lea dx,msg2
    mov ah,09h
    int 21h 
copy:          
    mov al,[si]
    mov [di],al
    inc si
    inc di
    dec cx
    jnz copy
    
    mov cx,length
    lea di,arr2
print:
    mov al,[di]    
    add al,'0'
    mov dl,al
    mov ah,02h
    int 21h
    inc di
    dec cx
    jnz print
    
    mov ah,4ch
    int 21h
code ends
end start
