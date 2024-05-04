# Lista 1 - /RE/gex

## A) Olá no Mundo das RegEx 
    
    [oO]l[áa] [mM]undo

## B) Olá no Mundo das RegEx 2
    
    [Oo][Ll][ÁáAa] [Mm][Uu][Nn][Dd][Oo]!?

### C) Números Positivos

    ^[0-9]+ $

### D) Números Positivos ou Não

    ^(\-[1-9][0-9]*|[0-9]+|\-[0][1-9]+)$

### E) Ímpares com RegEx 

    [0-9]*[13579]\>

### F) Pares com RegEx 

    ^[0-9]+$

### G) Validação dos horários 

    (colocar dps quem tiver)

### H) Desmatriculados -

    .*2021.*

### i)  Aracnofobia 

    .*(a|A).*(r|R).*(a|A).*(n|N).*(h|H).*(a|A).*

### J) Fantática máquina de palavras 

    \b\w*[Aa]\w*\b

### K) Problema 101

    ^(0*1*0{2,}1*0*)*$|^0*1*$|^1*0*$

### L) Morse Regex 

    ^([\.-]{5})*(\.{2}-{3}|-{3}\.{2}|\.{4}-{1}|-{1}\.{4}|-{5})$

### M) Palavras Censuradas 

    \b\w*XXX\w*\b

### N) Date

    (0[1-9]|[12][0-9]|[3][0-1])\/((0[13578])|(1[02]))\/(19[0-9]{2}|20[0-2][0-9])|((0[1-9]|[12][0-9]|30)\/((0[469])|11)\/(19[0-9]{2}|20[0-2][0-9]))|(((0[1-9])|(1[0-9])|2[0-8])\/02\/(19[0-9][0-9]|20[0-2][0-9]))|(((0[1-9])|[12][0-9])\/02\/(19(04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)|20(00|04|08|12|16|20|24)))

### O) Frases entre Tags 

    ^\s*([\w\d]+)(?:(?!\1)[\s\S])*?\b\1\s*$

### p) Quebrando senhas com RegEx

    b(r|B|b)*|bC 

