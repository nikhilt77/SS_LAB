data segment 
    arr1 db 1,2,3,4,5
    length equ 5  
    msg db 10,13,'Copied$'
    arr2 db 20 dup(?)
data ends
code segment
    assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    mov cx,length
    lea si,arr1
    lea di,arr2
copy:         
    mov al,[si]
    mov [di],al
    inc si
    inc di
    dec cx
    jnz copy
    
    mov cx,length
    lea si,arr2
print:
    mov al,[si]
    add al,'0'
    mov dl,al
    mov ah,02h
    int 21h
    inc si
    dec cx
    jnz print
    lea dx,msg
    mov ah,09h
    int 21h
    mov ah,4ch
    int 21h
code ends
end start
        
    
        
