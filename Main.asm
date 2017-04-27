    list p=16F887
    
#include "p16f887.inc"
    
; CONFIG1
; __config 0xE3F4
 __CONFIG _CONFIG1, _FOSC_INTRC_NOCLKOUT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_OFF & _FCMEN_OFF & _LVP_OFF
; CONFIG2
; __config 0xFEFF
 __CONFIG _CONFIG2, _BOR4V_BOR21V & _WRT_OFF
 
CBLOCK 0X20
    VENTANA : 6				;6 ventanas- 6 displays 
    SELECT				;Seleccionador de temporizador por dipswitch
    INI_SEGUNDOS			;valor de segundos 
    INI_MINUTOS				;valor de minutos
    I					;contador de visualizacion por cada una de las ventanas
    J					;contador de visualizacion por el numero total de las ventanas (1 segundo)
    K					;posicion inicial en la respectiva tabla de mensaje de reset
    L					;posicion en la tabla del mensaje espera
    U					;contador para desplazamineto de un caracter
ENDC 
    
    ORG .0				;llamado de las subrutinas de configuracion e inicializacion y limpieza de las variables
    CALL    CONFIGURACION
    CALL    INI_REG
    CLRF    INI_SEGUNDOS
    CLRF    INI_MINUTOS
    CLRF    SELECT
    CLRF    I
    CLRF    J
    CLRF    K
    CLRF    L
    CLRF    M
    CLRF    U
    
MAIN:					;inicio del programa (estado espera)
    BTFSS   PORTD,0			;testeo del bit 0 del puerto D
	GOTO	MENSAJE			;llamado de tabla con mensaje ESPERA
    CALL    RETARDO_B			;retardo de 25ms
    BTFSS   PORTD,0			;retesteo del puerto
	GOTO	MENSAJE			;llamado de tabla con mensaje ESPERA
	GOTO	OPCIONES		;menu de opciones (0, 50s; 1, 1m40s; 2, 2m30s; 3, 3m20s; 4, 4m10s)
    ;MENSAJE DE ESPERA
    MENSAJE:
    PAGESEL MENSAJE_ESPERA		;paginado (PAGE 4)
    CALL    MENSAJE_ESPERA		;mensaje ESPERA
    PAGESEL MAIN			;paginado (PAGE 1)
	GOTO	MAIN			;permanece en ESPERA

OPCIONES:    
    MOVF    PORTE,0			;PORTE entrada por dipswitch
    MOVWF   SELECT			;asignacion al selecccionador del temporizador 
    
    MOVLW   0X00			;opcion 0
    XORWF   SELECT,0			;comparacion con seleccionador
    BTFSC   STATUS,Z
	GOTO	T50s			;temporizador de 50s

    MOVLW   0X01			;opcion 1
    XORWF   SELECT,0			;comparacion con seleccionador
    BTFSC   STATUS,Z
	GOTO	T1m40s			;temporizador de 1m40s
	
    MOVLW   0X02			;opcion 2
    XORWF   SELECT,0			;comparacion con seleccionador
    BTFSC   STATUS,Z
	GOTO	T2m30s			;temporizador de 2m30s
	
    MOVLW   0X03			;opcion 3
    XORWF   SELECT,0			;comparacion con seleccionador
    BTFSC   STATUS,Z
	GOTO	T3m20s			;temporizador de 3m20s
	
    MOVLW   0X04			;opcion 4
    XORWF   SELECT,0			;comparacion con seleccionador
    BTFSC   STATUS,Z
	GOTO	T4m10s			;temporizador de 4m10s
	
    ;en los valores nos definidos realiza la temporizacion de 50s por defecto
	
T50s:
    MOVLW   0X00
    MOVWF   INI_MINUTOS			;minutos=0
    MOVLW   0X32
    MOVWF   INI_SEGUNDOS		;segundos=50
    MOVLW   .0
    MOVWF   K				;posicion inicial de tabla de mensaje reset (MENSAJE0) en 0
    MOVLW   .38
    MOVWF   M				;posicion final de tabla de mensaje reset (MENSAJE0) en 38
    CALL    TEMPORIZAR			;subrutina de temporizacion positiva
    GOTO    NEGATIVO			;temporizacion negativa
T1m40s:
    MOVLW   0X01
    MOVWF   INI_MINUTOS			;minutos=1
    MOVLW   0X28
    MOVWF   INI_SEGUNDOS		;segundos=40
    MOVLW   .38
    MOVWF   K				;posicion inicial de tabla de mensaje reset (MENSAJE0) en 38
    MOVLW   .72
    MOVWF   M				;posicion final de tabla de mensaje reset (MENSAJE0) en 72
    CALL    TEMPORIZAR			;subrutina de temporizacion positiva
    GOTO    NEGATIVO			;temporizacion negativa
T2m30s:
    MOVLW   0X02
    MOVWF   INI_MINUTOS			;minutos=2
    MOVLW   0X1E
    MOVWF   INI_SEGUNDOS		;segundos=30
    MOVLW   .72
    MOVWF   K				;posicion inicial de tabla de mensaje reset (MENSAJE0) en 72
    MOVLW   .114
    MOVWF   M				;posicion final de tabla de mensaje reset (MENSAJE0) en 114			    
    CALL    TEMPORIZAR			;subrutina de temporizacion positiva
    GOTO    NEGATIVO			;temporizacion negativa
T3m20s:
    MOVLW   0X03
    MOVWF   INI_MINUTOS			;minutos=3
    MOVLW   0X14
    MOVWF   INI_SEGUNDOS		;segundos=20
    MOVLW   .114
    MOVWF   K				;posicion inicial de tabla de mensaje reset (MENSAJE0) en 114
    MOVLW   .147
    MOVWF   M				;posicion final de tabla de mensaje reset (MENSAJE0) en 147
    CALL    TEMPORIZAR			;subrutina de temporizacion positiva
    GOTO    NEGATIVO			;temporizacion negativa
T4m10s:
    MOVLW   0X04
    MOVWF   INI_MINUTOSs		;minutos=4
    MOVLW   0X0A
    MOVWF   INI_SEGUNDOS		;segundos=10		
    MOVLW   .147
    MOVWF   K				;posicion inicial de tabla de mensaje reset (MENSAJE0) en 147
    MOVLW   .188
    MOVWF   M				;posicion final de tabla de mensaje reset (MENSAJE0) en 188
    CALL    TEMPORIZAR			;subrutina de temporizacion positiva
    GOTO    NEGATIVO			;temporizacion negativa
    
#include "Conversor.inc"
#include "Temporizar.inc"   
#include "Configuracion.inc"	      
#include "Visualizar.inc"
#include "Displays.inc"    
#include "Inicializar_Registros.inc"
#include "Retardo.inc"	
#include "Desplazar.inc"  
#include "Tabla_Dec.inc" 
#include "Mensajes.inc"   
    
END  