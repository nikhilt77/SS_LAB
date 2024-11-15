data segment
    msg1 db 10,13,'Enter String:$'
    msg2 db 10,13,'Enter Character:$'
    msg3 db 10,13,'Character found$'
    msg4 db 10,13,'Character not found$'
    str db 20 dup(?)
    target db ?
data ends
code segment
    assume cs:code,ds:data
start:    
    mov ax,data
    mov ds,ax
    lea dx,msg1
    mov ah,09h
    int 21h
    lea si,str 
input:
    mov ah,01h
    int 21h
    cmp al,13
    je terminate
    mov [si],al
    inc si
    jmp input
terminate:
    mov al,'$'
    mov [si],al
    dec si
    lea si,str
    lea dx,msg2
    mov ah,09h
    int 21h
    mov ah,01h
    int 21h
    mov [target],al
search:   
    mov al,[si]
    cmp al,'$'
    je not_found
    cmp al,[target]
    je found
    inc si
    jmp search
not_found:
    lea dx,msg4
    mov ah,09h
    int 21h
    jmp end
found:
    lea dx,msg3
    mov ah,09h
    int 21h
end:
    mov ah,4ch
    int 21h
code ends
end start
              
