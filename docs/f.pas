program AjudeAparecido;

var
  N, T, i, soma, valor: integer;

begin
  readln(N);
  soma := 0;
  for i := 1 to N do
  begin
    read(valor);
    soma := soma + valor;
  end;
  readln(T);
  if soma = T then
    writeln('Acertou')
  else
    writeln('Errou');
end.

