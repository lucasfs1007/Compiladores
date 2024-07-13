program Ajude_Aparecido;

var
  Ci1, Ci2, Ci3, T: integer;

begin
  // Lendo os valores da entrada
  readln(Ci1, Ci2, Ci3);
  readln(T);
  
  // Calculando a soma das contas dos colegas
  if (Ci1 + Ci2 + Ci3 = T) then
    writeln('Acertou')
  else
    writeln('Errou');
end.

