#lang racket

;Aldo Tena García - A01275222
;Actividad Integradora 3.4 Resaltador de sintaxis de C++

;Libreria que se utiliza para leer txt
(require 2htdp/batch-io)

;Lista con las letras de la "a" a la "z"
(define letras
  '("a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "ñ" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z")
)

;Lista con los números del 1 al 9
(define numeros
  '("1" "2" "3" "4" "5" "6" "7" "8" "9" "0")
)

;Lista con operadores de C++
(define operadores
  '("[" "]" "{" "}" "(" ")" ";" "," ":" "&" "|" "=" "<" ">" "%" "*" "/" "+" "-")
)

;Lista con palabras reservadas de C++
(define reservados_c++
 '("using" "namespace" "while" "do" "for" "if" "else" "switch" "case" "cout" "cin" "return" "true" "false" "endl")
)

;Lista con los tipos de datos
(define tipos_datos
  '("int" "long" "float" "double" "bool" "char" "string" "void")
)

;Lista con las librerias de C++
(define libreria_c++
  '("#include")
)

;Direccion del archivo txt de prueba (C++)
;Nota: En esta secion se debe escribir la direccion donde se encuentra el archivo input_c++.txt,
;dentro de la computadora de la persona que quiere ejecutar el programa
(define leer_archivo_c++
  "D:\\DocumentosDD\\Profesional\\4to Semestre\\Implementación de metodos computacionales\\TC2037\\ACT3.4\\input_c++.txt"
)

;Direccion donde se guarda el archivo html
;Nota: En esta secion se debe escribir la direccion donde se quiere guardar el archivo html con el output de este programa
;dentro de la computadora de la persona que quiere ejecutar el programa
(define escribir_archivo
  "D:\\DocumentosDD\\Profesional\\4to Semestre\\Implementación de metodos computacionales\\TC2037\\ACT3.4\\index.html"
)

;Se define una lista con el principio basico de un html
(define txt
  '("\n" "<body>" "\n"
"</head>" "\n"
"<title>Actividad Integradora 3.4 Resaltador de sintaxis</title>" "\n"
"<link rel='stylesheet' href='styles.css'>" "\n"
"<head>" "\n"
"<html>" "\n"
"<!DOCTYPE html>")
)


;Funcion que compara los caracteres de la lista enviada con los caracteres de las listas previamente definidas
(define buscar_en_lista
  (lambda (string list)
    (cond
     [(null? list) #f]
     [(string-ci=? string (car list)) #t]
     [else (buscar_en_lista string (cdr list))]
    )
  )
)

;Funcion que agrega al texto final los caracteres necesarios para imprimir un html correcto al encintrar una libreria de C++ 
(define continuidad_libreria_c++
  (lambda (list txt)
    (cond
      [(null? list) ((write escribir_archivo) txt)]
      [(string-ci=? (car list) "\n") (leer_c++ list (cons "</span>" txt))]
      [(string-ci=? (car list) "<") (continuidad_libreria_c++ (cdr list) (cons "&lt" txt))]
      [(string-ci=? (car list) ">") (continuidad_libreria_c++ (cdr list) (cons "&gt" txt))]
      [else (continuidad_libreria_c++ (cdr list) (cons (car list) txt))]
     )
  )
)
-
;Funcion que busca strings, los cuales sean palabras reservadas, librerias o tipos de dato en c++
(define palabra_c++
  (lambda (list txt palabra)
    (cond
      [(null? list) ((write escribir_archivo) (cons palabra txt))]
      [(and (not (buscar_en_lista (car list) letras))(buscar_en_lista palabra reservados_c++)) (leer_c++ list (cons "</span>" (cons palabra (cons "<span class='reserved'>" txt))))]
      [(and (not (buscar_en_lista (car list) letras))(buscar_en_lista palabra tipos_datos)) (leer_c++ list (cons "</span>" (cons palabra (cons "<span class='data_type'>" txt))))]
      [(and (not (buscar_en_lista (car list) letras))(buscar_en_lista palabra libreria_c++)) (continuidad_libreria_c++ list (cons palabra (cons "<span class='pragma'>" txt)))]
      [(string-ci=? (car list) " ") (leer_c++ list (cons palabra txt))]
      [(string-ci=? (car list) "\n") (leer_c++ list (cons palabra txt))]
      [(buscar_en_lista (car list) numeros) (leer_c++ list (cons palabra txt))]
      [(buscar_en_lista (car list) operadores) (leer_c++ list (cons palabra txt))]
      [else (palabra_c++ (cdr list) txt (~a palabra (car list)))]
   )
 )
)


;Funcion que agrega a una lista todos los caracteres entre comillas
(define comentario_c++
  (lambda (list txt)
    (cond
      [(null? list) ((write escribir_archivo) txt)]
      [(string-ci=? (car list) "\"") (leer_c++ (cdr list) (cons "</span>"(cons (car list) txt)))]
      [else (comentario_c++ (cdr list) (cons (car list) txt))]
     )
  )
)

;Funcion que agrega a una lista todos los caracteres que se encuentran despues de "//" y termina al encontrar un salto de linea
(define comentario_slash_c++
  (lambda (list txt)
    (cond
      [(null? list) ((write escribir_archivo) txt)]
      [(string-ci=? (car list) "\n") (leer_c++ (cdr list) (cons "</span>" (cons "<p>" (cons "\n" (cons "</p>" (cons (car list) txt))))))]
      [else (comentario_slash_c++ (cdr list) (cons (car list) txt))]
     )
  )
)

;Funcion que agrega a una lista todos los caracteres que se encuentran entre "/**/"
(define comentario_multiple_c++
  (lambda (list txt)
    (cond
      [(null? list) ((write escribir_archivo) txt)]
      [(string-ci=? (car list) "\n") (comentario_multiple_c++ (cdr list) (cons "<span class='comment'>"(cons "</span>" (cons "<p>" (cons "\n" (cons "</p>" txt))))))]
      [(and (string-ci=? (car list) "*") (string-ci=? (cadr list) "/") (leer_c++ (cddr list) (cons "</span>"(cons "*/" txt))))]
      [else (comentario_multiple_c++ (cdr list) (cons (car list) txt))]
     )
  )
)


;Funcion que que identifica los caracteres recibidos para añadirlos al html 
(define leer_c++
  (lambda (list txt)
    (cond
      [(null? list) ((write escribir_archivo) (cons "\n"(cons "</html>" (cons "\n" (cons "</body>" (cons "\n" txt))))))]
      [(string-ci=? (car list) " ") (leer_c++ (cdr list) (cons "&nbsp;" txt))]
      [(string-ci=? (car list) "\n") (leer_c++ (cdr list) (cons "<p>" (cons "\n" (cons "</p>" txt))))]
      [(and (string-ci=? (car list) "/") (string-ci=? (cadr list) "/") (comentario_slash_c++ (cddr list) (cons "//" (cons "<span class='comment'>" txt))))]
      [(and (string-ci=? (car list) "/") (string-ci=? (cadr list) "*") (comentario_multiple_c++ (cddr list) (cons "/*" (cons "<span class='comment'>" txt))))]
      [(string-ci=? (car list) "\"") (comentario_c++ (cdr list) (cons (car list) (cons "<span class='text'>" txt)))]
      [(buscar_en_lista (car list) numeros) (leer_c++ (cdr list) (cons "</span>" (cons (car list) (cons "<span class='number'>" txt))))]
      [(buscar_en_lista (car list) operadores) (leer_c++ (cdr list) (cons "</span>" (cons (car list) (cons "<span class='reserved'>" txt))))]
      [else (palabra_c++ (cdr list) txt (~a "" (car list)))]
     )
   )
)

;Funcion para identificar si recivimos un archivo de C++
(define identificar_archivo
  (lambda (archivo tipo_archivo)
  (cond
    [(string-ci=? tipo_archivo "c++") (leer_c++ (list archivo) txt)]
    [else ((write escribir_archivo) (cons "\n"(cons "</html>" (cons "\n" (cons "</body>" (cons "\n"(cons "entrada no valida" txt) ))))))]
  )
 )   
)

;Funcion que recibe la ruta del archivo a leer y el tipo de documento que es en un string
(define input
  (lambda (archivo tipo_archivo)
    (identificar_archivo archivo tipo_archivo)
   )
)

;Funcion para leer el archivo caracter por caracter
(define list
  (lambda (archivo)
    (read-1strings archivo)
   )
)

;Funcion para escribir en un archivo de texto
(define write
  (lambda (destino)
    (lambda (txt)
    (write-file destino (string-join (reverse txt) ""))
  )
 )  
)


;CASO DE PRUEBA
;(input leer_archivo_c++ "c++")