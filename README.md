scheme-interpreter
-----------------------------------------------------
1.  scheme-interpreter is a program used to interprete  
    scheme. There aren't bytecode generated during the  
    interpreting but relying on the runtime stack in  
    C++

2.  command-line test 
    
    \>\>\>   (+ 1 2) 
    2

    \>\>\>  (define a 1) 

    \>\>\>  (+ a 2) 
    3

    \>\>\>  (define (fac n)  
<p>             (if (= n 1) 1</p>
<p>                 (* n (fac (- n 1)))))</p>  

    \>\>\>  (fac 10)  
    3628800
