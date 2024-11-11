data segment 
    msg1 db 10,13,'String is palindrome$'
    msg2 db 10,13,'String is not Palindrome$'
    str1 db 50 dup(?)
    msg3 db 10,13,'Enter String:$'
data ends
code segment
     assume cs:code,ds:data
start:
    mov ax,data
    mov ds,ax
    lea dx,msg3
    mov ah,09h
    int 21h
    lea si,str1
    lea di,str1   
read:
    mov ah,01h
    int 21h
    cmp al,13
    JE end_point
    mov [di],al
    inc di
    jmp read
end_point:
    mov al,'$'
    mov [di],al
    dec di
    mov bx,di
check:
    mov al,[si]
    mov bl,[di]
    cmp al,bl
    JNE notpalindrome
    inc si
    dec di
    cmp si,di
    JL check
palindrome: 
    lea dx,msg1
    mov ah,09h
    int 21h
    JMP end
notpalindrome:
    lea dx,msg2
    mov ah,09h
    int 21h
end:     
    mov ah,4ch
    int 21h
    
code ends
end start
    
            
      
