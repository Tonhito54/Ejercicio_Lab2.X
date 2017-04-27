;ASIGNACION DE LAS VENTANAS A CADA DISPLAY CORRESPONDIENTE
DISPLAYS:  
    ;VENTANA 1 DISPLAY 5
    ;se le asigna al display 5 un valor fijo de 0
    INCF    FSR,1
    MOVLW   0X00
    CALL    TABLA
    MOVWF   INDF
    
    ;VENTANA 3 DISPLAY 3
    ;se le asigna al display 3 el valor de las unidades de minutos
    MOVLW   VENTANA
    MOVWF   FSR
    MOVLW   .3
    ADDWF   FSR,1
    MOVF    INI_MINUTOS,0
    CALL    CONVERSOR_M
    MOVF    UNI_MINUTOS,0
    CALL    TABLA
    MOVWF   INDF
    
    ;VENTANA 2 DISPLAY 4
    ;se le asigna al display 4 el valor de las decenas de minutos
    DECF    FSR,1
    MOVF    DEC_MINUTOS,0
    CALL    TABLA
    MOVWF   INDF
    
    ;VENTANA 5 DISPLAY 1
    ;se le asigna al display 1 el valor de las unidades de segundos
    MOVLW   VENTANA
    MOVWF   FSR
    MOVLW   .5
    ADDWF   FSR,1
    MOVF    INI_SEGUNDOS,0
    CALL    CONVERSOR_S
    MOVF    UNI_SEGUNDOS,0
    CALL    TABLA
    MOVWF   INDF
    
    ;VENTANA 4 DISPLAY 2
    ;se le asigna al display 2 el valor de las decenas de segundos
    DECF    FSR
    MOVF    DEC_SEGUNDOS,0
    CALL    TABLA
    MOVWF   INDF
    
    CALL    VISUALIZAR		;llamado a visualizar

RETURN    

