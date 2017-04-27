TEMPORIZAR:
    ;VENTANA 0 DISPLAY 6
    ;se asigna un valor de 0 al display 6
    MOVLW   VENTANA
    MOVWF   FSR
    MOVLW   0X00
    CALL    TABLA
    MOVWF   INDF
    
    CALL    DISPLAYS			;llamado a la asignacion de los demas displays
    
DECREMENTO:    
    ;DECREMENTO DE SEGUNDOS SI ES DIFERENTE DE CERO
    MOVLW   .0
    XORWF   INI_SEGUNDOS,0
    BTFSC   STATUS,Z
	GOTO	$+3
    DECF    INI_SEGUNDOS,1
	GOTO	TEMPORIZAR
    ;EVALUA SI CONTINUA O NO EL TEMPORIZADOR 
    MOVLW   .0
    XORWF   INI_MINUTOS,0
    BTFSC   STATUS,Z
	GOTO	$+5
    ;DECREMENTO MINUTOS Y REINICIO SEGUNDOS
    DECF    INI_MINUTOS,1
    MOVLW   .59
    MOVWF   INI_SEGUNDOS
	GOTO	TEMPORIZAR
	
NEGATIVO:				;CONTEOS NEGATIVOS
    BTFSS   PORTD,1			;testeo del bit 1 del puerto D
	GOTO	CONT_NEG		;cuenta negativamente
    CALL    RETARDO_B			;retardo de 25ms
    BTFSS   PORTD,1			;retesteo del bit 1 del puerto D
	GOTO	CONT_NEG		;cuenta negativamente
    CALL    INI_REG			;inicializacion de registros
    CALL    DESPLAZAR			;desplazamiento de mensajes de Reset
    GOTO    MAIN			;regreso a estado ESPERA
    CONT_NEG:
    CALL    CONT_NEGATIVO		;conteos negativos
	GOTO	NEGATIVO		;retesteo del reset 

CONT_NEGATIVO:	
    ;VENTANA 0 DISPLAY 6
    ;se le asigna un (-) al display 6
    MOVLW   VENTANA
    MOVWF   FSR
    MOVLW   0X0A
    CALL    TABLA
    MOVWF   INDF
    INCF    INI_SEGUNDOS
    
    ;INCREMENTO DE LOS SEGUNDOS 
    MOVLW   .60
    XORWF   INI_SEGUNDOS,0
    BTFSS   STATUS,Z		    ;si alcanzan un valor de 60 segundos
	GOTO	$+5
    INCF    INI_MINUTOS,1	    ;incrementan los minutos y se resetean los segundos y continua incrementando
    MOVLW   .0
    MOVWF   INI_SEGUNDOS
    INCF    INI_MINUTOS,1
    CALL    DISPLAYS		    ;asignacion de los demas displays
RETURN    

	
