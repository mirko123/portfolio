model small
.stack 256
.data 
	newLine DB 13, 10, '$'
 	arrow DB 13, 10,"  ||", 13, 10,"  \/", 13, 10, "$"
	choseMSG DB 'Za crypt izberete 1, za decrypt izberete 2:$'
	choseType DB 10 dup(?)
	choseMSG1 DB "Vie izbrahte da cryptirate", 13, 10, '$'
	choseMSG2 DB "Vie izbrahte da decryptirate", 13, 10, '$'

	choseInputMSG DB 'Za izvlichane ot fail izberete 1, za vuvejdane ot klaviaturata 2:$'
	choseInputVal DB 10 dup(?)

	inputLength DW 2
	inputFileNameMSG DB "Vuvedete ime na vhodqshtiq fail:$"
	outputFileNameMSG DB "Vuvedete ime na izhodqshtiq fail:$"
	inputFileName DB 100 dup(?)
	outputFileName DB 100 dup(?)
	inputTextMSG DB "Vhod:$"
	inputText DB 255 dup(?)
	outputTextMSG DB "Resu:$"
	outputText DB 255 dup(?)
	;fileSize db 255

	choseSaveMSG DB "Vuvedete ime na fail za zapis ili Enter za izhod:", '$'
	choseSaveVal DB 10 dup(?)

	errorMSG_OF2 DB "failut ne e nameren", 13, 10, '$'
	errorMSG_OF3 DB "marshrutat ne e nameren", 13, 10, '$'
	errorMSG_OF4 DB "prekaleno mnogo otvoreni failove", 13, 10, '$'
	errorMSG_OF5 DB "otkazano obrushtenie _o", 13, 10, '$'
	errorMSG_OF12 DB "nevalidno obrushtenie ", 13, 10, '$'

	errorMSG_RF5 DB "otkazano obrushtenie _f", 13, 10, '$'
	errorMSG_RF6 DB "nevalidna duma za obrushtenie ", 13, 10, '$'

	passMSG DB "Vuvedete parola:$"
	passText DB 255 dup(?)
	passLen DW 2 
	len DW 2
	finalMSG DB "Za exit vuvedete <q>, inache drug symbol:$"
	finalChoseType DB 10 dup(?) ;10 за да не гърми пръ въвеждане на повече
	buff DB  255 dup(?)
.code
main:
	mov ax, @data
	mov ds, ax

	lea dx,choseInputMSG
	call print 

	lea bx,choseInputVal
	call read
	mov al,[bx]
	cmp al,'1'
	je from_file

	lea dx,inputTextMSG
	call print 
	lea bx,inputText
	call read 
	jmp passInput

from_file:
	lea dx,inputFileNameMSG
	call print
	lea bx,inputFileName
	call read 

	lea dx,inputFileName
	lea si,inputText
	call read_file

	lea dx,inputTextMSG
	call print 
	lea dx,inputText
	call print
	lea dx,newLine
	call print

	;lea dx,outputFileNameMSG
	;call print
	;lea bx,outputFileName
	;call read 

passInput:
	mov ax,[len]
	mov [inputLength],ax

	lea dx,passMSG
	call print
	lea bx,passText
	call read 
	mov ax,[len]
	mov [passLen],ax

	;lea dx,passText
	;call print
	;mov [passLen],ax

	;lea dx,passText
	;call print


	lea dx,choseMSG
	call print

	lea bx,choseType
	call read 

	cmp choseType,'1'
	je code_text

	jmp decode_text


code_text:
	lea dx,choseMSG1
	call print


	lea dx,inputText
	call print


	lea di,passText
	lea si,inputText
	;lea di,outputText
c0:
	mov ax,[passLen]
	cmp ax,0
	je e0

	mov ah,[di]
	mov al,[si]
	add al,ah
	mov [si],al

	inc di
	mov al,[di]
	cmp al,'$'
	jne e0
	lea di,passText 	
e0:
	inc si
	mov al,[si]
	cmp al,'$'
	jne c0



	lea dx,arrow
	call print
	lea dx,inputText
	call print


	;lea dx,outputFileName
	;call create_standart_file_and_close
	
	;lea dx,outputFileName
	;lea si,inputText
	;call write_file


	jmp final

decode_text:	
	lea dx,choseMSG2
	call print

	;lea dx,inputFileName
	;lea si,inputText
	;call read_file

	lea dx,inputText
	call print



	lea di,passText
	lea si,inputText
	;lea di,outputText
c1:
	mov ax,[passLen]
	cmp ax,0
	je e0
	
	mov ah,[di]
	mov al,[si]
	sub al,ah
	mov [si],al

	inc di
	mov al,[di]
	cmp al,'$'
	jne e1
	lea di,passText 	
e1:
	inc si
	mov al,[si]
	cmp al,'$'
	jne c1



	lea dx,arrow
	call print
	lea dx,inputText
	call print


	;lea dx,outputFileName
	;call create_standart_file_and_close
	
	;lea dx,outputFileName
	;lea si,inputText
	;call write_file






	jmp final
   
final:
	lea dx,newLine
	call print 
	lea dx,choseSaveMSG
	call print 

	lea bx,outputFileName ;празно за изход
	call read
	
	cmp ax,0
	je terminate

	lea dx,outputFileName
	call create_standart_file_and_close
	
	mov ax,[inputLength]
	mov [len],ax

	lea dx,outputFileName
	lea si,inputText
	call write_file

;	lea dx,finalMSG
;	call print
;
;	lea bx,finalChoseType
;	call read
;
;	cmp finalChoseType,'q'
;	jne main
terminate:
	mov ax, 4c00h
	int 21h


;si <- output
read_file: ;BX дума за обръщане, CX брой за четене, DS:DX buffer, AX брой прочетени байтове
	call open
	mov bx,ax
	xor ax,ax
	;lea dx,inputText
	mov dx,si
	mov cx,255
	mov ah,3Fh
	int 21h
	;mov cx,ax

	add si,ax
	mov [len],ax
   	mov al, '$'
	mov [si],al

	call parse_operation_errors
	ret


;BX дума за обръщение към файла 
;CX	брой на байтовете, които трябва да се запишат
;DS:DX указател към буфера
write_file: 
	call open
	mov cx,[len]
	mov bx,ax
	mov dx,si
	mov ah,40h
	
	;mov cx,255
	;mov cx,5
	int 21h

	call parse_operation_errors
	ret


parse_operation_errors: ;важи както за read, така и за write
	jnc exit_read
	cmp ax,5
	je rd_er5
	cmp ax,6
	je rd_er6

  rd_er5:
	lea dx,errorMSG_RF5
	jmp printError
  rd_er6:
	lea dx,errorMSG_RF6
	jmp printError

  exit_read:
	ret


create_standart_file_and_close: ;lea dx - име
	mov ah,3Ch
	mov cx,0
	int 21h
	call parse_open_errors
	mov bx,ax
	call close


parse_create_errors:
	jnc exit_open
	cmp ax,3
	je cr_er3
	cmp ax,4
	je cr_er4
	cmp ax,5
	je cr_er5

  cr_er3:
	lea dx,errorMSG_OF3
	jmp printError_cr
  cr_er4:
	lea dx,errorMSG_OF4
	jmp printError_cr
  cr_er5:
	lea dx,errorMSG_OF5
	jmp printError_cr
  printError_cr:	
	call print

  exit_create:
	ret	

open: ;DS:DX име, AX дума за четене
	mov ah,3Dh
    mov al,2
	mov cx,2
	int 21h
	;jnc exit_open
	call parse_open_errors
	ret

parse_open_errors:
	jnc exit_open
	cmp ax,2
	je op_er2
	cmp ax,4
	je op_er4
	cmp ax,5
	je op_er5
	cmp ax,12
	je op_er12

  op_er2:
	lea dx,errorMSG_OF2
	jmp printError
  op_er4:
	lea dx,errorMSG_OF4
	jmp printError
  op_er5:
	lea dx,errorMSG_OF5
	jmp printError
  op_er12:
	lea dx,errorMSG_OF12
	jmp printError
  printError:	
	call print

  exit_open:
	ret	


close: ;BX дума за четене
	mov ah,3eh
	mov cx,1
	int 21h
	ret

read: ;чете вход и го записва в bx, съхранява дължината на въведеното в ax
	mov ah,01h
	mov cx,255
	mov si, bx
   cucle:
	int 21h
	CMP AL,13
	je exit
	mov [si],al
	inc si
	loop cucle
   exit:	
   	mov al, '$'
	mov [si],al
	mov ax, si
	sub ax, bx ;съхранява дължината в ax
	;dec ax ;заради $
	mov [len],ax
	ret

print: ;принтира стринга с адрес в dx, завършващ с $
	;lea dx,buff
	mov ah,9
    int 21h 
	ret

end main
 







