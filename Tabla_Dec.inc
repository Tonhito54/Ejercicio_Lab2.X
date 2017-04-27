CBLOCK
    AUX_REG1		    ;registro auxiliar para asignacion de valores del posiciones en la tabla
ENDC
    
ORG	0X7D0		    ;direccion de inicio para la tabla
    
TABLA:
    MOVWF   AUX_REG1	    ;aseguramiento del dato de posicion de la tabla
    MOVLW   0X07	
    MOVWF   PCLATH	    ;asignacion de 7 al PCLATH
    MOVF    AUX_REG1,0	    ;retoma el valor de la posicion en la tabla
    ADDWF   PCL,F
    ;DIGITOS EN DECIMAL
    DT	0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0XFF, 0X6F, 0X40
    ;MENSAJE ESPERA
    DT	0X79, 0X6D, 0X73, 0X79, 0X50, 0X77

