
CBLOCK
    R_MIN				;valor auxiliar de minutos
    DEC_MINUTOS				;decenas de minutos
    UNI_MINUTOS				;unidades de minutos
    R_SEG				;valor auxiliar de segundos
    DEC_SEGUNDOS			;decenas de segundos
    UNI_SEGUNDOS			;unidades de segundos
ENDC
  
;CONVERSOR DE MINUTOS   
CONVERSOR_M:				;conversor de minutos
    CLRF    DEC_MINUTOS			;limpieza de decenas de minutos
    CLRF    UNI_MINUTOS			;limpieza de unidades de minutos
    MOVWF   R_MIN			;asignacion del correspondiente valor de minutos para el temporizador elegido
DECENAS_M:  
    MOVLW   .10				    
    SUBWF   R_MIN,1			;resto 10 del valor de los minutos 
    BTFSS   STATUS,C			;testeo del carry (resultado positivo o negativo?)
	GOTO	UNIDADES_M		;resultado negativo envia a hallar unidades de minutos  
    INCF    DEC_MINUTOS			;resultado positivo incrementa el valor de decenas de minutos 
	GOTO	DECENAS_M		;se resta 10 hasta donde sea posible
    
UNIDADES_M:
    MOVLW   .10
    ADDWF   R_MIN,0			;se suma 10 al valor de los minutos para volver a un valor positivo 
    MOVWF   UNI_MINUTOS			;se asigna el resultado a unidades de minutos 
    
RETURN

;CONVERSOR DE SEGUNDOS
CONVERSOR_S:				;conversor de segundos
    CLRF    DEC_SEGUNDOS		;limpieza de decenas de segundos
    CLRF    UNI_SEGUNDOS		;limpieza de unidades de segundos
    MOVWF   R_SEG			;asignacion del correspondiente valor de segundos para el temporizador elegido
DECENAS_S:  
    MOVLW   .10
    SUBWF   R_SEG,1			;resto 10 del valor de los segundos
    BTFSS   STATUS,C			;testeo del carry (resultado positivo o negativo?)
	GOTO	UNIDADES_S		;resultado negativo envia a hallar unidades de segundos 
    INCF    DEC_SEGUNDOS		;resultado positivo incrementa el valor de decenas de segundos  
	GOTO	DECENAS_S		;se resta 10 hasta donde sea posible
    
UNIDADES_S:
    MOVLW   .10
    ADDWF   R_SEG,0			;se suma 10 al valor de los segundos para volver a un valor positivo 
    MOVWF   UNI_SEGUNDOS		;se asigna el resultado a unidades de segundos 
    
RETURN    
