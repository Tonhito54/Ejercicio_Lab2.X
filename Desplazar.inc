CBLOCK
    M				    ;valor final de tabla de mensaje de reset (MENSAJE0)
ENDC    

;DESPLAZAMIENTO DE TODAS LAS VENTANAS 
DESPLAZAR:
    CALL    DESPLAZA_CARACTER	    ;desplazamiento de caracter
    MOVF    K,0			    ;posicion inicial en la tabla
    PAGESEL MENSAJE0		    ;paginado (PAGE 4)
    CALL    MENSAJE0		    ;tabla de mesajes de reset
    PAGESEL DESPLAZAR		    ;paginado (PAGE 1)
    MOVWF   INDF		    ;extraccion del dato en dicha posicion
    MOVF    M,0			    ;posicion final de la tabla del mensaje
    XORWF   K,0
    BTFSC   STATUS,Z		    ;testeo de culminacion del mensaje
	GOTO	$+4		    
    INCF    K,1			    ;incremento de la posicion de la tabla
    CALL    VISUALIZAR		    ;visualizacion del caracter
	GOTO	DESPLAZAR	    ;desplazamiento del caracter
    CLRF    K			    ;limpieza del contador K
RETURN

;DESPLAZAMIENTO DE CADA CARACTER EN LA SIGUIENTE VENTANA
DESPLAZA_CARACTER:
    MOVLW   VENTANA		    ;direccion 0X20
    MOVWF   FSR			    ;asignacion al apuntador
    INCF    FSR			    ;incremento del apuntador
    MOVF    INDF,0		    ;extraccion del respectivo dato
    DECF    FSR			    ;decremento del apuntador
    MOVWF   INDF		    ;asignacion del respectivo dato
    INCF    FSR			    ;incremento del apuntador 
    INCF    U			    ;incremento del contador U
    MOVLW   0X05		    
    XORWF   U,0			    
    BTFSS   STATUS,Z		    ;testeo U=5
	GOTO	DESPLAZA_CARACTER+2 
    CLRF    U			    ;limpieza del contador U
RETURN    
