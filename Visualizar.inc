VISUALIZAR:
    CLRF    PORTC			;limpieza del puerto C
    BSF	    STATUS,C			;seteado del Carry
    MOVLW   VENTANA			;direccion 0X20
    MOVWF   FSR				
    MOVF    INDF,0			;extraccion del dato en esa direccion
    MOVWF   PORTA			;envio del dato al puerto A
    RLF	    PORTC,1			;rotacion del Carry por el puerto C			
    CALL    RETARDO			;retardo de 2,5ms
    INCF    FSR,1			;incremento del apuntador
    INCF    I,1				;incremento de la variable contadora de cada una de las ventanas 
    MOVLW   0X06			
    XORWF   I,0	    
    BTFSS   STATUS,Z			;testeo I=6
	GOTO	$-9			;vuelta a extraer el dato en la siguiente posicion 
    CLRF    I				;reseteo del contador I
    INCF    J,1				;incremento de la variable contadora del numero de veces de visuzalizacion por el total de ventanas 
    MOVLW   .68				;2.5ms*68*6= 1s 
    XORWF   J,0				
    BTFSS   STATUS,Z			;testeado de culminacion del segundo
	GOTO	VISUALIZAR		;vuelta a visualizar
    CLRF    J				;reseteo del contador J
RETURN