mov si,3000h
mov bx,[si]
dec bx
fl:
mov cx,[si]
dec cx
mov si,3002h
nn:
mov al,[si]
inc si
cmp al,[si]
jl nc
xchg al,[si]
dec si
mov [si],al
nc:
dec cx
jnz nn
dec bx
mov si,3000h
jnz fl
hlt
