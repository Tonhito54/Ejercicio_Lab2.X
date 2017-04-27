CBLOCK
    AUX_REG			    ;registro auxiliar para salvaguardar el dato de posicion de la tabla
ENDC
    
ORG 0X1800			    ;direccion de PAGINA 4

MENSAJE_ESPERA: 
    MOVLW   VENTANA		    ;direccion 0X20
    MOVWF   FSR			    ;asignacion del apuntador
    MOVLW   .11			    
    MOVWF   L			    ;inicio en la posicion 11 de la tabla
    MOVF    L,0
    PAGESEL TABLA		    ;paginado (PAGE 1)
    CALL    TABLA		    ;tabla de mensaje ESPERA
    MOVWF   INDF		    ;extraccion del dato en la posicion
    PAGESEL MENSAJE_ESPERA	    ;paginado (PAGE 4)
    MOVLW   .16			    
    XORWF   L,0			    
    BTFSC   STATUS,Z		    ;testeado L=16    (caracter final del mensaje ESPERA)
	GOTO	$+4
    INCF    FSR,1		    ;incremento del apuntador
    INCF    L,1			    ;incremento del contador L
	GOTO	MENSAJE_ESPERA+4    ;asignacion del nuevo dato
    PAGESEL VISUALIZAR		    ;paginado (PAGE 1)
    CALL    VISUALIZAR		    ;visualizar mensaje
RETURN   	    
    
ORG 0X1900	
MENSAJE0:
    MOVWF   AUX_REG		    ;guardado de posicion de la tabla
    MOVLW   0X19		    
    MOVWF   PCLATH		    ;asignacion del valor del PCLATCH
    MOVF    AUX_REG,0		    ;recuperacion del valor de la posicion de la tabla
    ADDWF   PCL,1	    
    
;------------------------------------------------------------------
;El principito_Antoine de Saint-Exupery
    DT	0X79, 0X30, 0X08, 0X73, 0X50, 0X04, 0X54, 0X58, 0X04, 0X73
    DT	0X04, 0X46, 0X5C, 0X08, 0X77, 0X54, 0X46, 0X5C, 0X04, 0X54
    DT	0X79, 0X08, 0X5E, 0X79, 0X08, 0X6D, 0X77, 0X04, 0X54, 0X46
    DT	0X40, 0X79, 0X76, 0X1C, 0X73, 0X79, 0X50, 0X6E 
;------------------------------------------------------------------
;Sherlock Holmes_Arthur Conan Doyle    
    DT	0X6D, 0X74, 0X79, 0X50, 0X30, 0X5C, 0X58, 0X70, 0X08, 0X74
    DT	0X5C, 0X30, 0X37, 0X79, 0X6D, 0X08, 0X77, 0X50, 0X46, 0X74
    DT	0X1C, 0X50, 0X08, 0X58, 0X5C, 0X54, 0X77, 0X54, 0X08, 0X5E
    DT	0X5C, 0X6E, 0X30, 0X79
;------------------------------------------------------------------
;Frankenstein moderno prometeo_Mary Shelley    
    DT	0X71, 0X50, 0X77, 0X54, 0X70, 0X79, 0X54, 0X6D, 0X46, 0X79
    DT	0X04, 0X54, 0X08, 0X37, 0X5C, 0X5E, 0X79, 0X50, 0X54, 0X5C
    DT	0X08, 0X73, 0X50, 0X5C, 0X37, 0X79, 0X46, 0X79, 0X5C, 0X08
    DT	0X37, 0X77, 0X50, 0X6E, 0X08, 0X6D, 0X74, 0X79, 0X30, 0X30
    DT	0X79, 0X6E
;------------------------------------------------------------------
;Las Cronicas de Narnia_C.S.Lewis
    DT	0X30, 0X77, 0X6D, 0X08, 0X58, 0X50, 0X5C, 0X54, 0X04, 0X58
    DT	0X77, 0X6D, 0X08, 0X5E, 0X79, 0X08, 0X54, 0X77, 0X50, 0X54
    DT	0X04, 0X77, 0X08, 0X58, 0X08, 0X6D, 0X08, 0X30, 0X79, 0X1C
    DT	0X1C, 0X04, 0X6D
;------------------------------------------------------------------
;La historia interminable_Michael Ende    
    DT	0X30, 0X77, 0X08, 0X74, 0X04, 0X6D, 0X46, 0X5C, 0X50, 0X04
    DT	0X77, 0X08, 0X04, 0X54, 0X46, 0X79, 0X50, 0X37, 0X04, 0X54
    DT	0X77, 0X7C, 0X30, 0X79, 0X08, 0X37, 0X04, 0X58, 0X74, 0X77
    DT	0X79, 0X30, 0X08, 0X79, 0X54, 0X5E, 0X79 

   



