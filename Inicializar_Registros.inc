INI_REG:			    ;inicializacion de los 6 registros de las ventadas por direccionamiento indirecto
    MOVLW   VENTANA
    MOVWF   FSR
    CLRF    INDF
    INCF    FSR
    MOVLW   0X26
    XORWF   FSR,0
    BTFSS   STATUS,Z
	GOTO	$-5
RETURN


